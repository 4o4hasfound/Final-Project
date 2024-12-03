#include "Physics/BoundingLine.hpp"

BoundingLine::BoundingLine()
	: start(0.0f, 0.0f), end(0.0f, 0.0f) {
}

BoundingLine::BoundingLine(float x1, float y1, float x2, float y2)
	: start(x1, y1), end(x2, y2) {
	if (start > end) {
		std::swap(start, end);
	}
}


BoundingLine::BoundingLine(const vec2& p1, float x2, float y2)
	: start(p1), end(x2, y2) {
	if (start > end) {
		std::swap(start, end);
	}
}


BoundingLine::BoundingLine(float x1, float y1, const vec2& p2)
	: start(x1, y1), end(p2) {
	if (start > end) {
		std::swap(start, end);
	}
}


BoundingLine::BoundingLine(const vec2& p1, const vec2& p2)
	: start(p1), end(p2) {
	if (start > end) {
		std::swap(start, end);
	}
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

	const float sa = sign(other.left() * a + other.top() * b + c);
	const float sb = sign(other.right() * a + other.top() * b + c);
	const float sc = sign(other.right() * a + other.bottom() * b + c);
	const float sd = sign(other.left() * a + other.bottom() * b + c);

	//Logger::Log<Debug>(sa, sb, sc, sd);

	if (sa == sb && sb == sc && sc == sd && sd == sa) {
		return false;
	}

	if (start.x > other.right() && end.x > other.right()) {
		return false;
	}
	if (start.x < other.left() && end.x < other.left()) {
		return false;
	}
	if (start.y > other.bottom() && end.y > other.bottom()) {
		return false;
	}
	if (start.y < other.top() && end.y < other.top()) {
		return false;
	}

	return true;
}

void BoundingLine::draw(RenderWindow& window) const {
	Line line(start, end, 2.0);
	line.color = vec4(0, 0, 0, 255);
	window.draw(line);
}