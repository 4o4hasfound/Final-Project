#pragma once

#include "Math/Vector.hpp"

#include "Physics/AABB.hpp"
#include "Physics/Collider.hpp"
#include "Physics/Manifold.hpp"

class PhysicsWorld;

struct RigidBodySetting {
	float angularVelocity = 0.0f;
	vec2 velocity = vec2(0.0f);

	float mass = 0.0f;
	float inertia = 0.0f;
	float density = 0.0f;
	float restitution = 0.0f;

	float staticFriction = 0.0f;
	float dynamicFriction = 0.0f;

	float torque = 0.0f;
	vec2 force = vec2(0.0f);

	Transform transform{};
};

class RigidBody {
	friend class PhysicsWorld;
public:
	enum BodyType {
		Static,
		Dynamic
	};
public:
	~RigidBody();

	void update(float dt, bool clearForces);

	template<typename ColliderType, typename ... Ts, typename = std::enable_if_t<std::is_base_of_v<Collider, ColliderType>>>
	ColliderType* addCollider(Ts&&... params);

	int getID() const;
	PhysicsWorld* getWorld() const;

	void move(const vec2& delta);
	void move(float x, float y);
	void accelerate(const vec2& speed);
	void accelerate(float x, float y);
	void rotate(float delta);
	void accelerateAngularVelocity(float speed);
	void addForce(const vec2& force);
	void addForce(float x, float y);

	float getAngularVelocity() const;
	void setAngularVelocity(float angularVelocity);
	const vec2& getVelocity() const;
	void setVelocity(const vec2& velocity);
	void setVelocity(float x, float y);
	float getMass() const;
	void setMass(float mass);
	float getInertia() const;
	void setInertia(float inertia);
	float getDensity() const;
	void setDensity(float density);
	float getRestitution() const;
	void setRestitution(float restitution);
	float getTorque() const;
	void setTorque(float torque);
	const vec2& getForce() const;
	void setForce(const vec2& force);
	void setForce(float x, float y);
	float getStaticFriction() const;
	void setStaticFriction(float staticFriction);
	float getDynamicFriction() const;
	void setDynamicFriction(float dynamicFriction);
	const vec2& getPosition() const;
	void setPosition(const vec2& position);
	void setPosition(float x, float y);
	float getRotation() const;
	void setRotation(float rotation);
	const Transform& getTransform() const;
	void setTransform(const Transform& transform);

	const AABB& getAABB() const;
	AABB getTransformedAABB() const;

	const BodyType type;
protected:
	RigidBody(BodyType type, int id, PhysicsWorld* world);
	RigidBody(BodyType type, const RigidBodySetting& setting, int id, PhysicsWorld* world);

	// Basic information
	float m_angularVelocity = 0.0f;
	vec2 m_velocity = vec2(0.0f);

	float m_mass = 0.0f;
	float m_inertia = 0.0f;
	float m_density = 0.0f;
	float m_restitution = 0.0f;

	float m_staticFriction = 0.0f;
	float m_dynamicFriction = 0.0f;

	float m_torque = 0.0f;
	vec2 m_force = vec2(0.0f);

	float m_invMass = 0.0f;
	float m_invInertia = 0.0f;

	// Verlet
	vec2 m_lastAcceleration = vec2(0.0f);
	float m_lastAngularAcceleration = 0.0f;

	// Physics World
	const int m_id;

	PhysicsWorld* m_world;

	Transform m_transform;
	AABB m_aabb;

	std::unique_ptr<Collider> m_collider;

	void updatePositionRK4(float dt);
	void updateRotationRK4(float dt);
	void updatePosition(float dt);
	void updateRotation(float dt); 

	void testCollision(RigidBody* other, std::vector<Manifold>& result);
};

#include "Physics/RigidBody.inl"