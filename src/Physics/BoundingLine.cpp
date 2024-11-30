#include "Physics/BoundingLine.hpp"

BoundingLine::BoundingLine()
	: start(0.0f, 0.0f), end(0.0f, 0.0f) {
}

BoundingLine::BoundingLine(float x1, float y1, float x2, float y2)
	: start(x1, y1), end(x2, y2) {
}


BoundingLine::BoundingLine(const vec2& p1, float x2, float y2)
	: start(p1), end(x2, y2) {
}


BoundingLine::BoundingLine(float x1, float y1, const vec2& p2)
	: start(x1, y1), end(p2) {
}


BoundingLine::BoundingLine(const vec2& p1, const vec2& p2)
	: start(p1), end(p2) {
}


bool BoundingLine::operator== (const BoundingLine& other) const {
	return start == other.start && end == other.end;
}
bool BoundingLine::operator!= (const BoundingLine& other) const {
	return start != other.start || end != other.end;
}

BoundingLine BoundingLine::operator+(const vec2& delta) const {
	return { start + delta, end + delta };
}
BoundingLine& BoundingLine::operator+=(const vec2& delta) {
	start += delta;
	end += delta;
	return *this;
}
BoundingLine BoundingLine::operator-(const vec2& delta) const {
	return { start - delta, end - delta };
}
BoundingLine& BoundingLine::operator-=(const vec2& delta) {
	start -= delta;
	end -= delta;
	return *this;
}

bool BoundingLine::intersect(const AABB& other) const {
	const float a = end.y - start.y;
	const float b = start.x - end.x;
	const float c = end.x * start.y - start.x * end.y;

	const float tl = other.left() * a + other.top() * b + c;
	const float tr = other.right() * a + other.top() * b + c;
	const float br = other.right() * a + other.bottom() * b + c;
	const float bl = other.left() * a + other.bottom() * b + c;
	if (tl > 0 && tr > 0 && br > 0 && bl > 0
		|| tl < 0 && tr < 0 && br < 0 && bl < 0) {
		return false;
	}

	const vec2 pos{ std::min(start.x, end.x), std::min(start.y, end.y) };
	const vec2 size{ std::abs(start.x - end.x), std::abs(start.y - end.y) };
	return AABB(pos, size).intersect(other);
}

void BoundingLine::draw(RenderWindow& window) const {
	Line line(start, end, 2.0);
	line.color = vec4(0, 0, 0, 255);
	window.draw(line);
}