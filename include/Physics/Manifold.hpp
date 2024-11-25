#pragma once
#include <memory>

#include "Math/Vector.hpp"

class RigidBody;

struct Manifold {
	RigidBody* body1;
	RigidBody* body2;
	vec2 normal;
	float depth;

	int contactCount;
	vec2 contact[2];
};