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
std::vector<BodyT*> PhysicsWorld::getBodies(RigidBody::BodyType bodyType) {
	updateBodies();
	std::vector<BodyT*> ret;

	for (RigidBody* body : m_bodies) {
		if ((body->getType() & bodyType) == bodyType) {
			ret.push_back(dynamic_cast<BodyT*>(body));
		}
	}

	return ret;
}

template<typename BodyT, typename>
std::vector<BodyT*> PhysicsWorld::query(RigidBody* body, RigidBody::BodyType bodyType) const {
	std::vector<RigidBody*> collideBodies;
	std::vector<BodyT*> ret;
	m_tree.query(body->getAABB(), collideBodies);
	for (const auto& body : collideBodies) {
		if ((body->getType() & bodyType) == bodyType) {
			ret.push_back(dynamic_cast<BodyT*>(body));
		}
	}
	return ret;
}
template<typename BodyT, typename>
inline std::vector<BodyT*> PhysicsWorld::query(const AABB& aabb, RigidBody::BodyType bodyType) const {
	std::vector<RigidBody*> collideBodies;
	std::vector<BodyT*> ret;
	m_tree.query(aabb, collideBodies);
	for (const auto& body : collideBodies) {
		if ((body->getType() & bodyType) == bodyType) {
			ret.push_back(dynamic_cast<BodyT*>(body));
		}
	}
	return ret;
}

template<typename BodyT, typename>
inline std::vector<BodyT*> PhysicsWorld::query(const BoundingCircle& circle, RigidBody::BodyType bodyType) const {
	std::vector<RigidBody*> collideBodies;
	std::vector<BodyT*> ret;
	const AABB aabb{
		circle.position - vec2(circle.radius),
		circle.position + vec2(circle.radius),
	};
	m_tree.query(aabb, collideBodies);
	for (const auto& body : collideBodies) {
		if ((body->getType() & bodyType) == bodyType && circle.intersect(body->getAABB())) {
			ret.push_back(dynamic_cast<BodyT*>(body));
		}
	}
	return ret;
}

template<typename BodyT, typename>
inline std::vector<BodyT*> PhysicsWorld::query(const BoundingLine& line, RigidBody::BodyType bodyType) const {
	std::vector<RigidBody*> collideBodies;
	std::vector<BodyT*> ret;
	const AABB aabb = AABB::FromTwoPoints(line.start, line.end);
	m_tree.query(aabb, collideBodies);
	for (const auto& body : collideBodies) {
		if ((body->getType() & bodyType) == bodyType && line.intersect(body->getAABB())) {
			ret.push_back(dynamic_cast<BodyT*>(body));
		}
	}
	return ret;
}
