#pragma once

#include "Game/Player/Player.hpp"
#include "Game/Skill/Skill.hpp"

class InvincibleShieldSkill : public Skill {
public:
	InvincibleShieldSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~InvincibleShieldSkill() = default;

	virtual void update(float dt);
	virtual void render(RenderWindow& window);
	virtual void active();

	virtual void use();
private:
	float m_clock;
};