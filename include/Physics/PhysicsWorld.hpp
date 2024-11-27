#pragma once
#include <mutex>
#include <thread>
#include <chrono>
#include <memory>
#include <vector>
#include <functional>
#include <type_traits>

#include "Math/Vector.hpp"

#include "Physics/Collider.hpp"
#include "Physics/RigidBody.hpp"
#include "Physics/SphereCollider.hpp"
#include "Physics/BoundingVolumeHierarchy.hpp"

#include "Render/Shape.hpp"
#include "Render/RenderWindow.hpp"

#include "Container/FreeList.hpp"

#include "Utils/ThreadPool.hpp"
#include "Utils/PoolAllocator.hpp"

#include "Debug/Log.hpp"

class PhysicsWorld {
	friend class RigidBody;
public:
	PhysicsWorld();
	~PhysicsWorld();

	template<typename BodyT = RigidBody, typename = std::enable_if_t<std::is_base_of_v<RigidBody, BodyT>>>
	BodyT* createBody(RigidBody::BodyType type, const RigidBodySetting& setting = RigidBodySetting{});

	void removeBody(int id);
	void removeBody(RigidBody* body);

	void update(float dt);

	bool hasCollide(RigidBody* body) const;

	void DebugDraw() const;

	std::vector<vec2> contactPoints;
private:
	PoolAllocator m_allocator;
	FreeList<RigidBody*> m_bodies;

	struct ResolveCollisionInfo {
		vec2 impulse;
		vec2 ra;
		vec2 raPerp;
		vec2 rb;
		vec2 rbPerp;
		float j;
		vec2 frictionImpulse;

		vec2 relativeVelocity;
	};
	struct pair_hash {
		template <class T1, class T2>
		std::size_t operator () (const std::pair<T1, T2>& p) const {
			auto h1 = std::hash<T1>{}(p.first);
			auto h2 = std::hash<T2>{}(p.second);

			// Mainly for demonstration purposes, i.e. works but is overly simple
			// In the real world, use sth. like boost.hash_combine
			return h1 ^ h2;
		}
	};

	void resolveCollision(const Manifold& manifold);
	void resolveCollisionThreaded(const Manifold& manifold);
	void getLinearAndRotationCollisionInfo(const Manifold& manifold, std::array<ResolveCollisionInfo, 2>& result);
	void getFrictionCollisionInfo(const Manifold& manifold, std::array<ResolveCollisionInfo, 2>& result);

	void getContactManifolds(std::vector<Manifold>& manifolds);
	void getContactManifoldsThreaded(std::vector<Manifold>& manifolds);
	void getContactManifoldsWorkgroup(FreeList<RigidBody*>::iterator start, FreeList<RigidBody*>::iterator end, std::vector<Manifold>& manifolds);

	void resolveManifolds(std::vector<Manifold>& manifolds);
	void resolveManifoldsThreaded(std::vector<Manifold>& manifolds);
	void resolveManifoldsWorkgroup(int start, int end, std::vector<Manifold>& manifolds, std::unordered_map<std::pair<RigidBody*, RigidBody*>, bool, pair_hash>& resovled);

	std::vector<std::thread> m_threads;
	std::mutex m_lock;
	BVH m_tree;
};

#include "Physics/PhysicsWorld.inl"