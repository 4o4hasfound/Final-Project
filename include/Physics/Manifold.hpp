#pragma once
#include <memory>

#include "Math/Vector.hpp"

class RigidBody;

// A structure to hold the result of a collision detection between two rigid bodies 
struct Manifold {
	RigidBody* body1;
	RigidBody* body2;
	vec2 normal = vec2(0);
	float depth = 0;
};