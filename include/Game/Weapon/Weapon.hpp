#pragma once

#include "Physics/PhysicsWorld.hpp"

class Weapon {
public:
	Weapon() = default;
	virtual ~Weapon() = default;

	virtual void draw() = 0;
	virtual void attack(PhysicsWorld* world) = 0;

protected:

};