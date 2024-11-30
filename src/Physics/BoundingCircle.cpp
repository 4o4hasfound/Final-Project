#include "Physics/BoundingCircle.hpp"

BoundingCircle::BoundingCircle()
	: position(0.0f, 0.0f), radius(0.0f) {
}

BoundingCircle::BoundingCircle(float x, float y, float _radius)
	: position(x, y), radius(_radius) {

}

BoundingCircle::BoundingCircle(const vec2& position, float _radius)
	: position(position), radius(_radius) {

}

bool BoundingCircle::operator== (const BoundingCircle& other) const {
	return position == other.position && radius == other.radius;
}
bool BoundingCircle::operator!= (const BoundingCircle& other) const {
	return position != other.position || radius != other.radius;
}

BoundingCircle BoundingCircle::operator+(const vec2& delta) const {
	return { position + delta, radius };
}
BoundingCircle& BoundingCircle::operator+=(const vec2& delta) {
	position += delta;
	return *this;
}
BoundingCircle BoundingCircle::operator-(const vec2& delta) const {
	return { position - delta, radius };
}
BoundingCircle& BoundingCircle::operator-=(const vec2& delta) {
	position -= delta;
	return *this;
}

bool BoundingCircle::intersect(const AABB& other) const {
	float testX = position.x;
	float testY = position.y;

	if (position.x < other.left())			testX = other.left();
	else if (position.x > other.right())		testX = other.right();
	if (position.y < other.top())				testY = other.top();
	else if (position.y > other.bottom())		testY = other.bottom();

	float distX = position.x - testX;
	float distY = position.y - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	return distance <= radius;
}

void BoundingCircle::draw(RenderWindow& window) const {
	Circle circle(radius);
	circle.position = position;
	circle.outlineThickness = 5;
	circle.outlineColor = vec4(0, 0, 0, 255);
	window.draw(circle);
}