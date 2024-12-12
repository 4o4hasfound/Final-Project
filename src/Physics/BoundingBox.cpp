#include "Physics/BoundingBox.hpp"

BoundingBox::BoundingBox() {

}

BoundingBox::BoundingBox(const AABB& _aabb, float _rotation)
	: aabb(_aabb), rotation(_rotation) {

}

bool BoundingBox::operator==(const BoundingBox& other) const {
	return aabb == other.aabb && rotation == other.rotation;
}

bool BoundingBox::operator!=(const BoundingBox& other) const {
	return aabb != other.aabb || rotation != other.rotation;
}

BoundingBox BoundingBox::operator+(const vec2& delta) const {
	return BoundingBox{ aabb + delta, rotation };
}

BoundingBox& BoundingBox::operator+=(const vec2& delta) {
	aabb += delta;
	return *this;
}

BoundingBox BoundingBox::operator-(const vec2& delta) const {
	return BoundingBox{ aabb - delta, rotation };
}

BoundingBox& BoundingBox::operator-=(const vec2& delta) {
	aabb += delta;
	return *this;
}

bool BoundingBox::intersect(const AABB& other) const {
    return intersect(BoundingBox(other, 0));
}

bool BoundingBox::intersect(const BoundingBox& other) const{
    vec2 a1(cos(rotation), sin(rotation));
    vec2 a2(-sin(rotation), cos(rotation));
    vec2 a3(cos(other.rotation), sin(other.rotation));
    vec2 a4(-sin(other.rotation), cos(other.rotation));

    // edge length
    vec2 l1 = aabb.size() * 0.5f;
    vec2 l2 = other.aabb.size() * 0.5f;

    // vector between pivots
    vec2 l = aabb.center() - other.aabb.center();

    float r1, r2, r3, r4;

    // project to a1
    r1 = l1.x * fabs(dot(a1, a1));
    r2 = l1.y * fabs(dot(a2, a1));
    r3 = l2.x * fabs(dot(a3, a1));
    r4 = l2.y * fabs(dot(a4, a1));
    if (r1 + r2 + r3 + r4 <= fabs(dot(l, a1))) {
        return false;
    }

    // project to a2
    r1 = l1.x * fabs(dot(a1, a2));
    r2 = l1.y * fabs(dot(a2, a2));
    r3 = l2.x * fabs(dot(a3, a2));
    r4 = l2.y * fabs(dot(a4, a2));
    if (r1 + r2 + r3 + r4 <= fabs(dot(l, a2))) {
        return false;
    }

    // project to a3
    r1 = l1.x * fabs(dot(a1, a3));
    r2 = l1.y * fabs(dot(a2, a3));
    r3 = l2.x * fabs(dot(a3, a3));
    r4 = l2.y * fabs(dot(a4, a3));
    if (r1 + r2 + r3 + r4 <= fabs(dot(l, a3))) {
        return false;
    }

    // project to a4
    r1 = l1.x * fabs(dot(a1, a4));
    r2 = l1.y * fabs(dot(a2, a4));
    r3 = l2.x * fabs(dot(a3, a4));
    r4 = l2.y * fabs(dot(a4, a4));
    if (r1 + r2 + r3 + r4 <= fabs(dot(l, a4))) {
        return false;
    }

    return true;
}

void BoundingBox::draw(RenderWindow& window) const {
	Rectangle rect(aabb.size());
	rect.rotation = rotation;
	rect.position = aabb.lowerBound + rect.size * 0.5f;
	rect.outlineThickness = 1.0f;
	rect.outlineColor = vec4(255, 255, 255, 255);
	window.draw(rect);
}

AABB BoundingBox::getTransformedAABB() const {
	const mat2 rotationMatrix(rotation);

	const vec2 tl = rotationMatrix * vec2{ aabb.left(), aabb.top() };
	const vec2 tr = rotationMatrix * vec2{ aabb.right(), aabb.top() };
	const vec2 bl = rotationMatrix * vec2{ aabb.left(), aabb.bottom() };
	const vec2 br = rotationMatrix * vec2{ aabb.right(), aabb.bottom() };


	AABB ret;
	ret.lowerBound = { std::min({tl.x, tr.x, bl.x, br.x}), std::min({tl.y, tr.y, bl.y, br.y}) };
	ret.upperBound = { std::max({tl.x, tr.x, bl.x, br.x}), std::max({tl.y, tr.y, bl.y, br.y}) };

	return ret;
}
