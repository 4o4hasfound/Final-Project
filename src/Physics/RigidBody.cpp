#include "Physics/RigidBody.hpp"

RigidBody::RigidBody(BodyType type, AABB aabb)
	: m_type(type), aabb(aabb) {
	
}

AABB RigidBody::getAABB() const {
	return aabb + position;
}

RigidBody::BodyType RigidBody::getType() const {
	return m_type;
}

void RigidBody::move(const vec2 delta) {
	position += delta;
}

void RigidBody::move(float x, float y) {
	position.x += x;
	position.y += y;
}

Manifold RigidBody::resolveCollision(RigidBody* other){
	Manifold manifold{ this, other };

	const vec2 ha = this->aabb.size() * 0.5;
	const vec2 hb = other->aabb.size() * 0.5;
	const vec2 d = other->getAABB().center() - this->getAABB().center();
	const vec2 overlap = ha + hb - abs(d);

	if (overlap.x <= 0 || overlap.y <= 0) {
		return manifold;
	}

	// Collision along the x axis
	if (overlap.x < overlap.y) {
		manifold.depth = overlap.x;
		if (d.x > 0) {
			manifold.normal = vec2(1, 0);
		}
		else {
			manifold.normal = vec2(-1, 0);
		}
	}
	else {
		manifold.depth = overlap.y;
		if (d.y > 0) {
			manifold.normal = vec2(0, 1);
		}
		else {
			manifold.normal = vec2(0, -1);
		}
	}

	if (this->getType() & RigidBody::Uncollidable || other->getType() & RigidBody::Uncollidable) {
		this->onCollide(other, manifold);
		other->onCollide(this, manifold);

		return manifold;
	}

	if (!(this->getType() & RigidBody::Static) && !(other->getType() & RigidBody::Static)) {
		this->move(-manifold.normal * manifold.depth * 0.5f);
		other->move(manifold.normal * manifold.depth * 0.5f);
	}
	else if (!(this->getType() & RigidBody::Static)) {
		this->move(-manifold.normal * manifold.depth);
	}
	else if (!(other->getType() & RigidBody::Static)) {
		other->move(manifold.normal * manifold.depth);
	}

	this->onCollide(other, manifold);
	other->onCollide(this, manifold);

	if (!(this->getType() & RigidBody::Static)) {
		if (manifold.normal.x) {
			this->velocity.x = other->velocity.x = 0;
		}
		if (manifold.normal.y) {
			this->velocity.y = other->velocity.y = 0;
		}
	}
	if (!(other->getType() & RigidBody::Static)) {
		if (manifold.normal.x) {
			other->velocity.x = other->velocity.x = 0;
		}
		if (manifold.normal.y) {
			other->velocity.y = other->velocity.y = 0;
		}
	}
	return manifold;
}

Manifold RigidBody::resolveCollision(const AABB& aabb) {
	Manifold manifold{ this, nullptr };

	const vec2 ha = this->aabb.size() * 0.5;
	const vec2 hb = aabb.size() * 0.5;
	const vec2 d = aabb.center() - this->getAABB().center();
	const vec2 overlap = ha + hb - abs(d);

	if (overlap.x <= 0 || overlap.y <= 0) {
		return manifold;
	}

	// Collision along the x axis
	if (overlap.x < overlap.y) {
		manifold.depth = overlap.x;
		if (d.x > 0) {
			manifold.normal = vec2(1, 0);
		}
		else {
			manifold.normal = vec2(-1, 0);
		}
	}
	else {
		manifold.depth = overlap.y;
		if (d.y > 0) {
			manifold.normal = vec2(0, 1);
		}
		else {
			manifold.normal = vec2(0, -1);
		}
	}

	if (!(getType() & RigidBody::Static) && !(getType() & RigidBody::Uncollidable)) {
		move(-manifold.normal * manifold.depth);

		if (manifold.normal.x) {
			this->velocity.x = 0;
		}
		if (manifold.normal.y) {
			this->velocity.y = 0;
		}
	}

	onCollide(nullptr, manifold);

	return manifold;
}

void RigidBody::update(float dt) {
	position += velocity * dt;
}