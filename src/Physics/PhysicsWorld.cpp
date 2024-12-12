#include "Physics/PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld() {

}

PhysicsWorld::~PhysicsWorld() {
	updateBodies();
	for (RigidBody* body : m_bodies) {
		delete body;
	}
}

void PhysicsWorld::update(float dt) {
	updateBodies();
	const int step = 1;
	dt /= step;
	for (int timeStep = 0; timeStep < step; ++timeStep) {
		for (RigidBody* body : m_bodies) {
			body->update(dt);
		}
		m_tree.update();
		std::vector<Manifold> result;
		resolveCollisions(result);
	}
	for (RigidBody* body : m_bodies) {
		body->afterCollisionTestCallback();
	}
}

void PhysicsWorld::DebugDraw(const RenderWindow& window) const {
	m_tree.render(window);
}

void PhysicsWorld::removeBody(int id) {
	delete m_bodies[id];
	m_tree.remove(id);
	m_bodies.remove(id);
}

void PhysicsWorld::removeBody(RigidBody* body) {
	m_tree.remove(body->m_id);
	m_bodies.remove(body->m_id);
	delete body;
}

std::vector<RigidBody*> PhysicsWorld::getBodies(RigidBody::BodyType bodyType) {
	updateBodies();
	std::vector<RigidBody*> ret;
	
	for (RigidBody* body : m_bodies) {
		if ((body->getType() & bodyType) == bodyType) {
			ret.push_back(body);
		}
	}

	return ret;
}

void PhysicsWorld::resolveCollisions(std::vector<Manifold>& manifolds) {
	std::vector<RigidBody*> collideBodies;
	for (const auto& body : m_bodies) {
		if (!body->alive) {
			continue;
		}
		if (body->getType() & RigidBody::Static) {
			continue;
		}
		m_tree.query(body->getAABB(), collideBodies);
		for (RigidBody* collideBody : collideBodies) {
			if (collideBody == body) {
				continue;
			}

			manifolds.push_back(body->resolveCollision(collideBody));
		}
		collideBodies.clear();
	}

}

void PhysicsWorld::updateBodies() {
	for (auto itr = m_bodies.begin(), end = m_bodies.end(); itr != end; ++itr) {
		if (!itr->alive) {
			RigidBody* ptr = *itr;
			m_tree.remove(itr->m_id);
			m_bodies.remove(itr);
			delete ptr;
		}
	}

}
