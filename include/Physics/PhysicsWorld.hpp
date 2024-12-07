#pragma once
#include <mutex>
#include <thread>
#include <chrono>
#include <memory>
#include <vector>
#include <functional>
#include <type_traits>

#include "Math/Vector.hpp"

#include "Physics/RigidBody.hpp"
#include "Physics/BoundingVolumeHierarchy.hpp"
#include "Physics/Manifold.hpp"
#include "Physics/BoundingCircle.hpp"
#include "Physics/BoundingLine.hpp"

#include "Render/Shape.hpp"
#include "Render/RenderWindow.hpp"

#include "Container/FreeList.hpp"

#include "Utils/ThreadPool.hpp"
#include "Utils/PoolAllocator.hpp"

#include "Debug/Log.hpp"

// Manages the simulation of physics in the game world, including rigid bodies, collisions, and spatial organization
class PhysicsWorld {
	friend class RigidBody;
private:
	struct pair_hash {
		template<typename T1, typename T2>
		bool operator()(const std::pair<T1, T2>& p) const {
			return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
		}
	};

public:
	PhysicsWorld();
	~PhysicsWorld();

	// Creates and adds a new rigid body to the world
	template<typename BodyT = RigidBody, typename ... T, typename = std::enable_if_t<std::is_base_of_v<RigidBody, BodyT>>>
	BodyT* createBody(const T& ... arguments);

	// Removes a rigid body from the world by its ID
	void removeBody(int id);
	// Removes a rigid body from the world by its pointer
	void removeBody(RigidBody* body);

	std::vector<RigidBody*> getBodies(int bodyType);
	template<typename BodyT, typename = std::enable_if_t<std::is_base_of_v<RigidBody, BodyT>>>
	std::vector<BodyT*> getBodies(int bodyType);

	// Updates the physics simulation for one time step
	void update(float dt);
	
	// Checks if a given rigid body is colliding with any other body
	bool hasCollide(RigidBody* body);

	// Queries the list of rigid bodies that a given body is interacting with
	// ToQuery limit the type of the return bodies
	template<RigidBody::BodyType ToQuery = RigidBody::Any>
	std::vector<RigidBody*> query(RigidBody* body) const;

	template<RigidBody::BodyType ToQuery = RigidBody::Any>
	std::vector<RigidBody*> query(const AABB& aabb) const;

	template<RigidBody::BodyType ToQuery = RigidBody::Any>
	std::vector<RigidBody*> query(const BoundingCircle& circle) const;

	template<RigidBody::BodyType ToQuery = RigidBody::Any>
	std::vector<RigidBody*> query(const BoundingLine& line) const;

	// Draw the physics world
	void DebugDraw(const RenderWindow& window) const;
private:
	FreeList<RigidBody*> m_bodies;

	void resolveCollisions(std::vector<Manifold>& manifolds);
	
	// Remove the unalive bodies
	void updateBodies();

	std::vector<std::thread> m_threads;
	std::mutex m_lock;
	BVH m_tree;
};

#include "Physics/PhysicsWorld.inl"