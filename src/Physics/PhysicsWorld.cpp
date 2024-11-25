#include "Physics/PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld()
	: m_allocator(sizeof(RigidBody) + alignof(RigidBody), 5000) {
}

PhysicsWorld::~PhysicsWorld()
{

}

RigidBody* PhysicsWorld::createBody(RigidBody::BodyType type, const RigidBodySetting& setting) {
	int id = m_bodies.emplace(nullptr);
	m_bodies[id] = (RigidBody*)m_allocator.allocate();
	new(m_bodies[id]) RigidBody(type, id, this);
	
	//RigidBody* ptr = new RigidBody(type, id, this);;
	//m_bodies[id] = ptr;
	
	m_tree.insert(m_bodies[id]);

	return m_bodies[id];
}

void PhysicsWorld::update(float dt) {
	const int step = 12;
	dt /= step;
	for (int timeStep = 0; timeStep < step; ++timeStep) {
		contactPoints.clear();

		std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();

		for (RigidBody* body: m_bodies) {
			if (body->type == RigidBody::Static) {
				continue;
			}
			body->addForce(0, body->getMass() * 1176.0f * 10.0f * dt);
			body->update(dt, timeStep == step-1);
		}

		m_tree.update(); 
		std::vector<Manifold> result;
		getContactManifoldsThreaded(result);

		//Logger::Log<Debug>(result.size());
		resolveManifolds(result);
		//resolveManifoldsThreaded(result);
		//if (result.size() < 48) {
		//	//resolveManifolds(result);
		//}
		//else {
		//	//resolveManifoldsThreaded(result);
		//}
	}
}

bool PhysicsWorld::hasCollide(RigidBody* body) const {
	std::vector<RigidBody*> potentialCollideBodies;
	m_tree.query(body->getTransformedAABB(), potentialCollideBodies);
	std::vector<Manifold> result;
	for (RigidBody* collideBody : potentialCollideBodies) {
		if (collideBody == body) {
			continue;
		}
		body->testCollision(collideBody, result);
	}
	return !result.empty();
}

void PhysicsWorld::DebugDraw() const {
	m_tree.render();
}

void PhysicsWorld::removeBody(int id) {
	m_bodies.remove(id);
}
void PhysicsWorld::removeBody(RigidBody* body) {
	if (body->m_world != nullptr) {
		return;
	}
	m_bodies.remove(body->m_id);
}

void PhysicsWorld::resolveCollision(const Manifold& manifold) {
	RigidBody* body1 = manifold.body1;
	RigidBody* body2 = manifold.body2;

	if (body1->type == RigidBody::Dynamic && body2->type == RigidBody::Dynamic) {
		body1->move(manifold.normal * manifold.depth * 0.5f);
		body2->move(-manifold.normal * manifold.depth * 0.5f);
	}
	else if (body1->type == RigidBody::Dynamic) {
		body1->move(manifold.normal * manifold.depth);
	}
	else if (body2->type == RigidBody::Dynamic) {
		body2->move(-manifold.normal * manifold.depth);
	}

	std::array<ResolveCollisionInfo, 2> collisionInfo;
	getLinearAndRotationCollisionInfo(manifold, collisionInfo);
	getFrictionCollisionInfo(manifold, collisionInfo);
	for (int i = 0; i < manifold.contactCount; ++i) {
		const vec2 impulse = (collisionInfo[i].impulse - collisionInfo[i].frictionImpulse);
		body1->accelerate(impulse * body1->m_invMass);
		body2->accelerate(-impulse * body2->m_invMass);

		const float raImpulseCross = collisionInfo[i].ra.x * impulse.y - collisionInfo[i].ra.y * impulse.x;
		const float rbImpulseCross = collisionInfo[i].rb.x * impulse.y - collisionInfo[i].rb.y * impulse.x;

		body1->accelerateAngularVelocity(-raImpulseCross * body1->m_invInertia);
		body2->accelerateAngularVelocity(rbImpulseCross * body2->m_invInertia);
	}
}

void PhysicsWorld::resolveCollisionThreaded(const Manifold& manifold) {
	RigidBody* body1 = manifold.body1;
	RigidBody* body2 = manifold.body2;

	m_lock.lock();

	if (body1->type == RigidBody::Dynamic && body2->type == RigidBody::Dynamic) {
		body1->move(manifold.normal * manifold.depth * 0.5f);
		body2->move(manifold.normal * manifold.depth * 0.5f);
	}
	else if (body1->type == RigidBody::Dynamic) {
		body1->move(manifold.normal * manifold.depth);
	}
	else if (body2->type == RigidBody::Dynamic) {
		body2->move(manifold.normal * manifold.depth);
	}
	else {
		m_lock.unlock();
		return;
	}

	std::array<ResolveCollisionInfo, 2> collisionInfo;
	getLinearAndRotationCollisionInfo(manifold, collisionInfo);
	getFrictionCollisionInfo(manifold, collisionInfo);

	for (int i = 0; i < manifold.contactCount; ++i) {
		const vec2 impulse = (collisionInfo[i].impulse - collisionInfo[i].frictionImpulse);
		body1->accelerate(impulse * body1->m_invMass);
		body2->accelerate(-impulse * body2->m_invMass);

		const float raImpulseCross = collisionInfo[i].ra.x * impulse.y - collisionInfo[i].ra.y * impulse.x;
		const float rbImpulseCross = collisionInfo[i].rb.x * impulse.y - collisionInfo[i].rb.y * impulse.x;

		body1->accelerateAngularVelocity(-raImpulseCross * body1->m_invInertia);
		body2->accelerateAngularVelocity(rbImpulseCross * body2->m_invInertia);
	}
	m_lock.unlock();
}

void PhysicsWorld::getLinearAndRotationCollisionInfo(const Manifold& manifold, std::array<ResolveCollisionInfo, 2>& result) {
	RigidBody* body1 = manifold.body1;
	RigidBody* body2 = manifold.body2;

	const float e = std::min(body1->getRestitution(), body2->getRestitution());

	for (int i = 0; i < manifold.contactCount; ++i) {
		const vec2 ra = manifold.contact[i] - body1->getPosition();
		const vec2 rb = manifold.contact[i] - body2->getPosition();

		result[i].ra = ra;
		result[i].rb = rb;

		const vec2 raPerp{ ra.y, -ra.x };
		const vec2 rbPerp{ rb.y, -rb.x };

		result[i].raPerp = raPerp;
		result[i].rbPerp = rbPerp;

		const vec2 angularVelocityA = raPerp * body1->getAngularVelocity();
		const vec2 angularVelocityB = rbPerp * body2->getAngularVelocity();

		vec2 relativeVelocity(
			(body1->getVelocity() + angularVelocityA) -
			(body2->getVelocity() + angularVelocityB)
		);
		//if ((length(relativeVelocity) - 200.0f) <= 0) {
		//	relativeVelocity = vec2(0.0f);
		//}
		result[i].relativeVelocity = relativeVelocity;

		const float contactVelocityMag = dot(relativeVelocity, manifold.normal);

		if (contactVelocityMag > 0.0f) {
			result[i].impulse = vec2(0.0f);
			result[i].j = 0.0f;
			continue;
		}

		float j = -(1.0f + e) * contactVelocityMag;
		j /= body1->m_invMass
			+ body2->m_invMass
			+ (pow(dot(raPerp, manifold.normal), 2) * body1->m_invInertia)
			+ (pow(dot(rbPerp, manifold.normal), 2) * body2->m_invInertia);
		j /= static_cast<float>(manifold.contactCount);

		const vec2 impulse = manifold.normal * j;

		result[i].impulse = impulse;
		result[i].j = j;
	}
}

void PhysicsWorld::getFrictionCollisionInfo(const Manifold& manifold, std::array<ResolveCollisionInfo, 2>& result) {
	RigidBody* body1 = manifold.body1;
	RigidBody* body2 = manifold.body2;

	const float e = std::min(body1->getRestitution(), body2->getRestitution());
	const float sf = (body1->getStaticFriction() + body2->getStaticFriction()) * 0.5f;
	const float df = (body1->getDynamicFriction() + body2->getDynamicFriction()) * 0.5f;

	for (int i = 0; i < manifold.contactCount; ++i) {
		vec2 tangent = result[i].relativeVelocity - dot(result[i].relativeVelocity, manifold.normal) * manifold.normal;

		if (dot(tangent, tangent) < 0.0005f) {
			result[i].frictionImpulse = vec2(0.0f);
			continue;
		}
		tangent = -normalize(tangent);
		
		float jt = dot(result[i].relativeVelocity, tangent);
		jt /= body1->m_invMass
			+ body2->m_invMass
			+ (pow(dot(result[i].raPerp, tangent), 2) * body1->m_invInertia)
			+ (pow(dot(result[i].rbPerp, tangent), 2) * body2->m_invInertia);
		jt /= static_cast<float>(manifold.contactCount);

		vec2 frictionImpulse;

		if (abs(jt) <= result[i].j * sf) {
			frictionImpulse = tangent * jt;
		}
		else {
			frictionImpulse = -result[i].j * tangent * df;
		}

		result[i].frictionImpulse = frictionImpulse;
	}
}

void PhysicsWorld::getContactManifolds(std::vector<Manifold>& manifolds) {
	std::vector<RigidBody*> potentialCollideBodies;
	for (const auto& body : m_bodies) {
		if (body->type == RigidBody::Static) {
			continue;
		}
		m_tree.query(body->getTransformedAABB(), potentialCollideBodies);
		for (RigidBody* collideBody : potentialCollideBodies) {
			if (collideBody == body) {
				continue;
			}
			body->testCollision(collideBody, manifolds);
		}
		potentialCollideBodies.clear();
	}
}

void PhysicsWorld::getContactManifoldsThreaded(std::vector<Manifold>& manifolds) {
	const int numThreads = ThreadPool::ThreadCount();
	const int minWorkingItem = 5;

	if (m_bodies.size() < numThreads * minWorkingItem) {
		getContactManifolds(manifolds);
		return;
	}
	int workgroupSize = m_bodies.size() / numThreads;
	auto itr = m_bodies.begin();

	for (int i = 0; i < numThreads; ++i) {
		const int start = i * workgroupSize;
		const int end = (i != numThreads - 1) ? (i + 1) * workgroupSize : m_bodies.size();
		auto endItr = itr + (end - start);

		ThreadPool::EnqueueJob(std::bind(
			&PhysicsWorld::getContactManifoldsWorkgroup,
			this,
			itr,
			endItr,
			std::ref(manifolds)
		));
		itr = endItr;
	}
	ThreadPool::WaitUntilComplete();
}

void PhysicsWorld::getContactManifoldsWorkgroup(FreeList<RigidBody*>::iterator start, FreeList<RigidBody*>::iterator end, std::vector<Manifold>& manifolds) {
	std::vector<Manifold> result;
	for (; start != end; ++start) {
		RigidBody* body = *start;
		if (body->type == RigidBody::Static) {
			continue;
		}
		std::vector<RigidBody*> potentialCollideBodies;
		m_tree.query(body->getTransformedAABB(), potentialCollideBodies);
		for (RigidBody* collideBody : potentialCollideBodies) {
			if (collideBody == body) {
				continue;
			}
			body->testCollision(collideBody, result);
		}
	}
	m_lock.lock();
	manifolds.insert(manifolds.end(), result.begin(), result.end());
	m_lock.unlock();
}

void PhysicsWorld::resolveManifolds(std::vector<Manifold>& manifolds) {
	std::unordered_map<std::pair<RigidBody*, RigidBody*>, bool, pair_hash> resolved;
	for (const Manifold& manifold : manifolds) {
		if (resolved[{manifold.body1, manifold.body2}]) {
			continue;
		}
		resolved[{manifold.body1, manifold.body2}] = resolved[{manifold.body2, manifold.body1}] = 1;
		contactPoints.push_back(manifold.contact[0]);
		if (manifold.contactCount == 2) {
			contactPoints.push_back(manifold.contact[1]);
		}
		resolveCollision(manifold);
	}
}

void PhysicsWorld::resolveManifoldsThreaded(std::vector<Manifold>& manifolds) {
	const int numThreads = ThreadPool::ThreadCount();

	int workgroupSize = manifolds.size() / numThreads;
	std::unordered_map<std::pair<RigidBody*, RigidBody*>, bool, pair_hash> resolved;

	for (int i = 0; i < numThreads; ++i) {
		const int end = (i != numThreads - 1) ? (i + 1) * workgroupSize : manifolds.size();
		ThreadPool::EnqueueJob(std::bind(
			&PhysicsWorld::resolveManifoldsWorkgroup,
			this,
			i * workgroupSize,
			end,
			std::ref(manifolds),
			std::ref(resolved)
		));
	}
	ThreadPool::WaitUntilComplete();
}

void PhysicsWorld::resolveManifoldsWorkgroup(int start, int end, std::vector<Manifold>& manifolds, std::unordered_map<std::pair<RigidBody*, RigidBody*>, bool, pair_hash>& resolved) {
	for (; start < end; ++start) {
		const Manifold& manifold = manifolds[start];
		m_lock.lock();
		if (resolved[{manifold.body1, manifold.body2}]) {
			m_lock.unlock();
			continue;
		}
		resolved[{manifold.body1, manifold.body2}] = resolved[{manifold.body2, manifold.body1}] = 1;
		contactPoints.push_back(manifold.contact[0]);
		if (manifold.contactCount == 2) {
			contactPoints.push_back(manifold.contact[1]);
		}
		m_lock.unlock();
		resolveCollisionThreaded(manifold);
	}
}
