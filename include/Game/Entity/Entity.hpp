#pragma once

#include "Physics/RigidBody.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Physics/AABB.hpp"

#include "Render/RenderWindow.hpp"

class Player;

class Entity : public RigidBody {
public:
	Entity(BodyType type, AABB aabb = { {0.0f, 0.0f}, {0.0f, 0.0f} });
	virtual ~Entity() = default;

	virtual void draw(RenderWindow& window) = 0;

	Player* player;
protected:
};