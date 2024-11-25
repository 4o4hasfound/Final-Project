#include "Physics/Collider.hpp"

Collider::Collider(Shape _shape, const AABB& aabb)
	: shape(_shape), transform(), m_aabb(aabb) {
}

Collider::Collider(Shape _shape, const AABB& aabb, const Transform& trans)
	: shape(_shape), transform(trans), m_aabb(aabb) {

}
Collider::~Collider() {

}

void Collider::getTransformedVertices(std::vector<vec2>& output, const Transform& _transform) {

}

double Collider::getInertia(double mass) const {
	return 0.0;
}

const AABB& Collider::getAABB() const {
	return m_aabb;
}

AABB Collider::getTransformedAABB() const {
	return m_aabb.transform(transform);
}
AABB Collider::getTransformedAABB(const Transform& _transform) const {
	return m_aabb.transform(transform + _transform);
}
