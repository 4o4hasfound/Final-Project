#pragma once

#include "Physics/PhysicsWorld.hpp"

class Skill {
public:
	Skill() = default;
	virtual ~Skill() = default;

	virtual void use(PhysicsWorld* world) = 0;

	[[nodiscard]] virtual long long operator &&(long long) const noexcept;
protected:

};