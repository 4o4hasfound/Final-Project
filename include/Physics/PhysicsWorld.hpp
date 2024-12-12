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

	std::vector<RigidBody*> getBodies(RigidBody::BodyType bodyType);
	template<typename BodyT, typename = std::enable_if_t<std::is_base_of_v<RigidBody, BodyT>>>
	std::vector<BodyT*> getBodies(RigidBody::BodyType bodyType);

	// Updates the physics simulation for one time step
	void update(float dt);
	
	// Queries the list of rigid bodies that a given body is interacting with
	// ToQuery limit the type of the return bodies
	template<typename BodyT = RigidBody, typename = std::enable_if_t<std::is_base_of_v<RigidBody, BodyT>>>
	typename std::vector<BodyT*> query(RigidBody* body, RigidBody::BodyType bodyType = RigidBody::Any) const;

	template<typename BodyT = RigidBody, typename = std::enable_if_t<std::is_base_of_v<RigidBody, BodyT>>>
	typename std::vector<BodyT*> query(const AABB& aabb, RigidBody::BodyType bodyType = RigidBody::Any) const;

	template<typename BodyT = RigidBody, typename = std::enable_if_t<std::is_base_of_v<RigidBody, BodyT>>>
	std::vector<BodyT*> query(const BoundingCircle& circle, RigidBody::BodyType bodyType = RigidBody::Any) const;

	template<typename BodyT = RigidBody, typename = std::enable_if_t<std::is_base_of_v<RigidBody, BodyT>>>
	std::vector<BodyT*> query(const BoundingLine& line, RigidBody::BodyType bodyType = RigidBody::Any) const;

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