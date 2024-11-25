#include "Physics/Transform.hpp"

Transform Transform::operator+(const Transform& other) const {
	Transform ret = *this;
	ret.position += other.position;
	ret.rotation += other.rotation;
	ret.rotation = std::fmod(ret.rotation, PI_TWO);
	ret.scale *= other.scale;
	return ret;
}
Transform& Transform::operator+=(const Transform& other) {
	position += other.position;
	rotation += other.rotation;
	rotation = std::fmod(rotation, PI_TWO);
	scale *= other.scale;
	return *this;
}