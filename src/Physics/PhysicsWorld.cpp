#include "Physics/PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld() {

}

PhysicsWorld::~PhysicsWorld() {
	for (RigidBody* body : m_bodies) {
		free(body);
	}
}

void PhysicsWorld::update(float dt) {
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

bool PhysicsWorld::hasCollide(RigidBody* body) const {
	std::vector<RigidBody*> collideBodies;
	m_tree.query(body->getAABB(), collideBodies);
	return !collideBodies.empty();
}

void PhysicsWorld::DebugDraw(const RenderWindow& window) const {
	m_tree.render(window);
}

void PhysicsWorld::removeBody(int id) {
	m_bodies.remove(id);
}
void PhysicsWorld::removeBody(RigidBody* body) {
	m_bodies.remove(body->m_id);
}

void PhysicsWorld::resolveCollisions(std::vector<Manifold>& manifolds) {
	std::vector<RigidBody*> collideBodies;
	for (const auto& body : m_bodies) {
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