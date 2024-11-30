#include "Physics/AABB.hpp"

AABB::AABB()
	: lowerBound(0.0f, 0.0f), upperBound(0.0f, 0.0f) {
}

AABB::AABB(const vec2& lower, const vec2& upper)
	: lowerBound(lower), upperBound(upper) {
}

AABB::AABB(const vec2& size)
	: lowerBound(0.0f, 0.0f), upperBound(size) {
}

AABB AABB::FromTwoPoints(const vec2& p1, const vec2& p2) {
	return AABB(
		vec2{ std::min(p1.x, p2.x), std::min(p1.y, p2.y) },
		vec2{ std::max(p1.x, p2.x), std::max(p1.y, p2.y) }
	);
}

vec2 AABB::size() const {
	return upperBound - lowerBound;
}

bool AABB::intersect(const AABB& other) const {
	return upperBound.x > other.lowerBound.x
		&& other.upperBound.x > lowerBound.x
		&& upperBound.y > other.lowerBound.y
		&& other.upperBound.y > lowerBound.y;
}

bool AABB::intersect(const vec2& point) const {
	return point.x <= upperBound.x 
		&& point.x >= lowerBound.x 
		&& point.y <= upperBound.y
		&& point.y >= lowerBound.y;
}

bool AABB::contain(const AABB& other) const {
	return upperBound.x >= other.upperBound.x
		&& lowerBound.x <= other.lowerBound.x
		&& upperBound.y >= other.upperBound.y
		&& lowerBound.y <= other.lowerBound.y;
}

float AABB::area() const {
	const vec2 d = upperBound - lowerBound;
	return d.x * d.y;
}

vec2 AABB::center() const {
	return lowerBound + size() * 0.5f;
}

float AABB::bottom() const {
	return upperBound.y;
}

float AABB::top() const {
	return lowerBound.y;
}

float AABB::right() const {
	return upperBound.x;
}

float AABB::left() const {
	return lowerBound.x;
}


void AABB::setCenter(const vec2& _center) {
	const vec2 delta = _center - center();
	lowerBound += delta;
	upperBound += delta;
}

void AABB::enlarge(const vec2& newSize) {
	const vec2 delta = (newSize - size()) * 0.5f;

	lowerBound -= delta;
	upperBound += delta;
}

AABB AABB::operator+(const vec2& position) const {
	AABB ret(*this);

	ret.lowerBound += position;
	ret.upperBound += position;

	return ret;
}
AABB& AABB::operator+=(const vec2& position) {
	lowerBound += position;
	upperBound += position;

	return *this;
}
AABB AABB::operator-(const vec2& position) const {
	AABB ret(*this);

	ret.lowerBound -= position;
	ret.upperBound -= position;

	return ret;
}
AABB& AABB::operator-=(const vec2& position) {
	lowerBound -= position;
	upperBound -= position;

	return *this;
}

AABB AABB::operator*(float factor) const {
	AABB ret(*this);

	ret.lowerBound *= factor;
	ret.upperBound *= factor;

	return ret;
}

AABB& AABB::operator*=(float factor) {
	lowerBound *= factor;
	upperBound *= factor;

	return *this;
}

AABB AABB::operator|(const AABB& other) const {
	AABB ret;
	ret.lowerBound.x = std::min(lowerBound.x, other.lowerBound.x);
	ret.lowerBound.y = std::min(lowerBound.y, other.lowerBound.y);
	ret.upperBound.x = std::max(upperBound.x, other.upperBound.x);
	ret.upperBound.y = std::max(upperBound.y, other.upperBound.y);
	return ret;
}
AABB& AABB::operator|=(const AABB& other) {
	lowerBound.x = std::min(lowerBound.x, other.lowerBound.x);
	lowerBound.y = std::min(lowerBound.y, other.lowerBound.y);
	upperBound.x = std::max(upperBound.x, other.upperBound.x);
	upperBound.y = std::max(upperBound.y, other.upperBound.y);
	return *this;
}

bool AABB::operator==(const AABB& other) const {
	return lowerBound == other.lowerBound && upperBound == other.upperBound;
}
bool AABB::operator!=(const AABB& other) const {
	return lowerBound != other.lowerBound || upperBound != other.upperBound;
}

void AABB::DebugDraw(const RenderWindow& window) const {
	Rectangle rect(size());
	rect.position = lowerBound + size() * 0.5f;
	rect.outlineThickness = 1.0f;
	rect.outlineColor = vec4(255, 255, 255, 255);
	window.draw(rect);
}
