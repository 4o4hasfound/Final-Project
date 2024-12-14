#pragma once

#include "Game/Entity/Entity.hpp"

#include "Game/Player/Player.hpp"

#include "Render/Animation.hpp"
#include "Render/Shape.hpp"

#include "Utils/Random.hpp"

class ExperienceOrb : public Entity {
public:
	ExperienceOrb(int _amount);
	~ExperienceOrb() = default;

	virtual void draw(RenderWindow& window) override;

	int amount;
	Player* player;
	float speed;
protected:
	Animation m_animation;

	virtual void update(float dt) override;

	// Callback function when two objects collide
	virtual void onCollide(RigidBody* other, const Manifold& detail) override;
};