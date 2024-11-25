#include "Physics/SphereCollider.hpp"

SphereCollider::SphereCollider(float _radius, const Transform& transform)
	: Collider(Collider::Circle, AABB({-_radius, -_radius}, {_radius, _radius}), transform), radius(_radius) {

}

SphereCollider::SphereCollider(float _radius)
	: Collider(Collider::Circle, AABB({ -_radius, -_radius }, { _radius, _radius }), Transform{}), radius(_radius) {

}

SphereCollider::~SphereCollider()
{

}

Collider::CollisionTestResult SphereCollider::testCollision(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) {
	switch (collider->shape) {
	case Circle:
		return testCollisionSphere(collider, myTrans, colliderTrans);
	case Polygon:
		return testCollisionPolygon(collider, myTrans, colliderTrans);
	}
}

std::pair<float, float> SphereCollider::project(const vec2& axis, const Transform& _transform) {
	const vec2 normal = normalize(axis);
	const Transform trans = this->transform + _transform;

	const vec2 center = normal * dot(trans.position, normal);
	const vec2 p1 = center - normal * radius, p2 = center + normal * radius;
	const float proj1 = dot(p1, normal), proj2 = dot(p2, normal);
	return std::make_pair(std::min(proj1, proj2), std::max(proj1, proj2));
}

double SphereCollider::getInertia(double mass) const {
	return 0.5 * mass * radius * radius;
}

Collider::CollisionTestResult SphereCollider::testCollisionSphere(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) {
	CollisionTestResult ret;
	ret.collided = false;

	const Transform myGlobalTrans = myTrans + transform;
	const Transform colliderGlobalTrans = colliderTrans + collider->transform;

	const SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);

	ret.normal = myGlobalTrans.position - colliderGlobalTrans.position;
	ret.depth = radius * myGlobalTrans.scale + sphereCollider->radius * colliderGlobalTrans.scale - length(ret.normal);
	ret.normal = normalize(ret.normal);

	if (ret.depth < 0) {
		return ret;
	}
	ret.collided = true;

	ret.contactCount = 1;
	ret.contact[0] = myGlobalTrans.position - ret.normal * radius * myGlobalTrans.scale;
	return ret;
}

Collider::CollisionTestResult SphereCollider::testCollisionRect(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) {
	//vec2 halfSizeA = vec2()
	return CollisionTestResult();
}

Collider::CollisionTestResult SphereCollider::testCollisionPolygon(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) {
	CollisionTestResult ret;
	ret.collided = false;

	const Transform myGlobalTrans = myTrans + transform;
	const Transform colliderGlobalTrans = colliderTrans + collider->transform;

	std::vector<vec2> vertices;
	collider->getTransformedVertices(vertices, colliderTrans);

	ret.normal = vec2(0);
	ret.depth = std::numeric_limits<float>::max();

	vec2 closestPointOnPolygon = vertices[0];

	for (int i = 0; i < vertices.size(); ++i) {
		if (distance(myGlobalTrans.position, vertices[i]) < distance(myGlobalTrans.position, closestPointOnPolygon)) {
			closestPointOnPolygon = vertices[i];
		}
		const vec2 edge = vertices[(i + 1) % vertices.size()] - vertices[i];
		const vec2 axis = normalize(vec2{ edge.y, -edge.x });

		std::pair<float, float> p1 = project(axis, myGlobalTrans);
		std::pair<float, float> p2 = collider->project(axis, colliderGlobalTrans);

		if (p1.first >= p2.second || p2.first >= p1.second) {
			return ret;
		}

		float intersect = p2.second - p1.first;
		if (ret.depth > intersect) {
			ret.normal = axis;
			ret.depth = intersect;
		}
	}

	const vec2 axis = normalize(closestPointOnPolygon - myGlobalTrans.position);

	std::pair<float, float> p1 = project(axis, myGlobalTrans);
	std::pair<float, float> p2 = collider->project(axis, colliderGlobalTrans);

	if (p1.first >= p2.second || p2.first >= p1.second) {
		return ret;
	}

	float intersect = std::min(p2.second - p1.first, p1.second - p2.first);
	vec2 normal = axis;
	if (dot(axis, myGlobalTrans.position - colliderGlobalTrans.position) < 0.0f) {
		normal = -normal;
	}
	if (ret.depth > intersect) {
		ret.normal = normal;
		ret.depth = intersect;
	}
	ret.collided = true;

	float contactDistanceSquared = std::numeric_limits<float>::max();
	vec2 contactPoint;

	for (int i = 0; i < vertices.size(); ++i) {
		const vec2 pa = vertices[(i + 1) % vertices.size()];
		const vec2 pb = vertices[i];
		
		const vec2 p = closestPointOnLine(myGlobalTrans.position, pa, pb);
		const vec2 vec = myGlobalTrans.position - p;
		float distanceSquared = dot(vec, vec);

		if (distanceSquared < contactDistanceSquared) {
			contactDistanceSquared = distanceSquared;
			contactPoint = p;
		}
	}

	ret.contactCount = 1;
	ret.contact[0] = contactPoint;
	return ret;
}
