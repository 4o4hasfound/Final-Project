#include "PhysicsWorld.hpp"
template<typename BodyT, typename ... T, typename>
BodyT* PhysicsWorld::createBody(const T& ... arguments) {
	BodyT* body = new BodyT(arguments...);
	int id = m_bodies.push(body);
	body->m_id = id;

	m_tree.insert(body);

	return body;
}

template<typename BodyT, typename>
std::vector<BodyT*> PhysicsWorld::getBodies(int bodyType) {
	updateBodies();
	std::vector<BodyT*> ret;

	for (RigidBody* body : m_bodies) {
		if (body->getType() == bodyType) {
			ret.push_back(dynamic_cast<BodyT*>(body));
		}
	}

	return ret;
}

template<RigidBody::BodyType ToQuery>
std::vector<RigidBody*> PhysicsWorld::query(RigidBody* body) const {
	std::vector<RigidBody*> collideBodies;
	std::vector<RigidBody*> ret;
	m_tree.query(body->getAABB(), collideBodies);
	for (const auto& body : collideBodies) {
		if (body->getType() & ToQuery) {
			ret.push_back(body);
		}
	}
	return ret;
}
template<RigidBody::BodyType ToQuery>
inline std::vector<RigidBody*> PhysicsWorld::query(const AABB& aabb) const {
	std::vector<RigidBody*> collideBodies;
	std::vector<RigidBody*> ret;
	m_tree.query(aabb, collideBodies);
	for (const auto& body : collideBodies) {
		if (body->getType() & ToQuery) {
			ret.push_back(body);
		}
	}
	return ret;
}

template<RigidBody::BodyType ToQuery>
inline std::vector<RigidBody*> PhysicsWorld::query(const BoundingCircle& circle) const {
	std::vector<RigidBody*> collideBodies;
	std::vector<RigidBody*> ret;
	const AABB aabb{
		circle.position - vec2(circle.radius),
		circle.position + vec2(circle.radius),
	};
	m_tree.query(aabb, collideBodies);
	for (const auto& body : collideBodies) {
		if (body->getType() & ToQuery && circle.intersect(body->getAABB())) {
			ret.push_back(body);
		}
	}
	return ret;
}

template<RigidBody::BodyType ToQuery>
inline std::vector<RigidBody*> PhysicsWorld::query(const BoundingLine& line) const {
	std::vector<RigidBody*> collideBodies;
	std::vector<RigidBody*> ret;
	const AABB aabb = AABB::FromTwoPoints(line.start, line.end);
	m_tree.query(aabb, collideBodies);
	for (const auto& body : collideBodies) {
		if (body->getType() & ToQuery && line.intersect(body->getAABB())) {
			ret.push_back(body);
		}
	}
	return ret;
}
