#include "Physics/RigidBody.hpp"

RigidBody::RigidBody(BodyType _type, int id, PhysicsWorld* world)
	: type(_type), m_world(world), m_id(id) {

}

RigidBody::RigidBody(BodyType _type, const RigidBodySetting& setting, int id, PhysicsWorld* world)
	: type(_type), 
	m_world(world), 
	m_angularVelocity(setting.angularVelocity),
	m_velocity(setting.velocity),
	m_mass(setting.mass), 
	m_inertia(setting.inertia), 
	m_density(setting.density), 
	m_restitution(setting.restitution),
	m_staticFriction(setting.staticFriction),
	m_dynamicFriction(setting.dynamicFriction),
	m_torque(setting.torque),
	m_force(setting.force),
	m_transform(setting.transform),
	m_invMass(1.0 / setting.mass),
	m_invInertia(1.0 / setting.inertia),
	m_id(id) {

}

RigidBody::~RigidBody() {

}

void RigidBody::update(float dt, bool clearForces) {
	if (type == Static) {
		return;
	}
	updatePositionRK4(dt);
	updateRotationRK4(dt);
	//updatePosition(dt);
	//updateRotation(dt);
	m_transform.rotation = std::fmod(m_transform.rotation, PI_TWO);
	
	if (clearForces) {
		m_force = vec2(0.0f);
		m_torque = 0.0f;
	}

	if (m_collider) {
		m_collider->m_needUpdateVertices = 1;
	}
}

void RigidBody::updatePositionRK4(float dt) {
	const vec2 k1 = m_force * m_invMass * dt;

	vec2 tmpForce = m_force + k1 * 0.5f;
	const vec2 k2 = tmpForce * m_invMass * dt;

	tmpForce = m_force + k2 * 0.5f;
	const vec2 k3 = tmpForce * m_invMass * dt;

	tmpForce = m_force + k3 * 0.5f;
	const vec2 k4 = tmpForce * m_invMass * dt;

	const vec2 deltaV = (k1 + k2 * 2.0f + k3 * 2.0f + k4) / 6.0f;
	m_velocity += deltaV;
	m_transform.position += m_velocity * dt;
}

void RigidBody::updateRotationRK4(float dt) {
	const float k1 = m_torque * m_invInertia * dt;

	float tmpTorque = m_torque + k1 * 0.5f;
	const float k2 = tmpTorque * m_invInertia * dt;

	tmpTorque = m_torque + k2 * 0.5f;
	const float k3 = tmpTorque * m_invInertia * dt;

	tmpTorque = m_torque + k3 * 0.5f;
	const float k4 = tmpTorque * m_invInertia * dt;

	const float deltaOmega = (k1 + k2 * 2.0f + k3 * 2.0f + k4) / 6.0f;

	m_angularVelocity += deltaOmega;
	m_transform.rotation += m_angularVelocity * dt;
}

void RigidBody::updatePosition(float dt) {
	vec2 a = m_force * m_invMass;
	m_transform.position += m_velocity * dt + 0.5f * m_lastAcceleration * dt * dt;

	m_velocity += 0.5f * (m_lastAcceleration + a) * dt;
	m_velocity *= 0.9999f;

	m_lastAcceleration = a;
	m_force = vec2(0.0f);
}

void RigidBody::updateRotation(float dt) {
	float a = m_torque * m_invInertia;
	m_transform.rotation += m_angularVelocity * dt + 0.5f * m_lastAngularAcceleration * dt * dt;

	m_angularVelocity += 0.5f * (a + m_lastAngularAcceleration) * dt;
	m_angularVelocity *= 0.9999f;

	m_lastAngularAcceleration = a;
	m_torque = 0.0f;
}

void RigidBody::testCollision(RigidBody* other, std::vector<Manifold>& result) {
	Transform myTransform = getTransform();
	Transform colliderTransform = other->getTransform();
	Collider::CollisionTestResult testResult = m_collider->testCollision(
		other->m_collider.get(), myTransform, colliderTransform
	);
	if (testResult.collided) {
		result.push_back(Manifold{ 
			this, 
			other, 
			testResult.normal, 
			testResult.depth,
			testResult.contactCount,
			testResult.contact[0],
			testResult.contact[1]
		});
	}
}


const vec2& RigidBody::getVelocity() const {
	return m_velocity;
}
void RigidBody::setVelocity(const vec2& velocity) {
	m_velocity = velocity;
}
void RigidBody::setVelocity(float x, float y) {
	m_velocity = vec2(x, y);
}
float RigidBody::getAngularVelocity() const {
	return m_angularVelocity;
}
void RigidBody::setAngularVelocity(float angularVelocity) {
	m_angularVelocity = std::fmod(angularVelocity, PI_TWO);
}
float RigidBody::getMass() const {
	return m_mass;
}
void RigidBody::setMass(float mass) {
	assert(mass > 0, "the mass of a rigidbody needs to be greater than 0");
	m_mass = mass;
	if (type == RigidBody::Dynamic) {
		m_invMass = 1.0 / mass;
	}
}
float RigidBody::getInertia() const {
	return m_mass;
}
void RigidBody::setInertia(float inertia) {
	assert(inertia > 0, "the inertia of a rigidbody needs to be greater than 0");
	m_inertia = inertia;
	if (type == RigidBody::Dynamic) {
		m_invInertia = 1.0f / inertia;
	}
}
float RigidBody::getDensity() const {
	return m_density;
}
void RigidBody::setDensity(float density) {
	assert(density > 0, "the density of a rigidbody needs to be greater than 0");
	m_density = density;
}
float RigidBody::getRestitution() const {
	return m_restitution;
}
void RigidBody::setRestitution(float restitution) {
	m_restitution = restitution;
}
float RigidBody::getTorque() const {
	return m_torque;
}
void RigidBody::setTorque(float torque) {
	m_torque += torque;
}
const vec2& RigidBody::getForce() const {
	return m_force;
}
void RigidBody::setForce(const vec2& force) {
	m_force += force;
}
void RigidBody::setForce(float x, float y) {
	m_force += vec2(x, y);
}
float RigidBody::getStaticFriction() const {
	return m_staticFriction;
}
void RigidBody::setStaticFriction(float staticFriction) {
	m_staticFriction = staticFriction;
}
float RigidBody::getDynamicFriction() const {
	return m_dynamicFriction;
}
void RigidBody::setDynamicFriction(float dynamicFriction) {
	m_dynamicFriction = dynamicFriction;
}
const vec2& RigidBody::getPosition() const {
	return m_transform.position;
}
void RigidBody::setPosition(const vec2& position) {
	m_transform.position = position;
	if (m_collider) {
		m_collider->m_needUpdateVertices = 1;
	}
}
void RigidBody::setPosition(float x, float y) {
	m_transform.position = vec2(x, y);
	if (m_collider) {
		m_collider->m_needUpdateVertices = 1;
	}
}
float RigidBody::getRotation() const {
	return m_transform.rotation;
}
void RigidBody::setRotation(float rotation) {
	m_transform.rotation = std::fmod(rotation, PI_TWO);
	if (m_collider) {
		m_collider->m_needUpdateVertices = 1;
	}
}
const Transform& RigidBody::getTransform() const {
	return m_transform;
}
void RigidBody::setTransform(const Transform& transform) {
	m_transform = transform;
	if (m_collider) {
		m_collider->m_needUpdateVertices = 1;
	}
}

const AABB& RigidBody::getAABB() const {
	return m_aabb;
}

AABB RigidBody::getTransformedAABB() const {
	return m_aabb.transform(m_transform);
}

int RigidBody::getID() const {
	return m_id;
}

PhysicsWorld* RigidBody::getWorld() const {
	return m_world;
}

void RigidBody::move(const vec2& delta) {
	m_transform.position += delta;
	if (m_collider) {
		m_collider->m_needUpdateVertices = 1;
	}
}
void RigidBody::move(float x, float y) {
	m_transform.position += vec2(x, y);
	if (m_collider) {
		m_collider->m_needUpdateVertices = 1;
	}
}
void RigidBody::accelerate(const vec2& speed) {
	m_velocity += speed;
}
void RigidBody::accelerate(float x, float y) {
	m_velocity += vec2(x, y);
}
void RigidBody::rotate(float delta) {
	m_transform.rotation += delta;
	if (m_collider) {
		m_collider->m_needUpdateVertices = 1;
	}
}
void RigidBody::accelerateAngularVelocity(float speed) {
	m_angularVelocity += speed;
}
void RigidBody::addForce(const vec2& force) {
	m_force += force;
}
void RigidBody::addForce(float x, float y) {
	m_force += vec2(x, y);;
}
