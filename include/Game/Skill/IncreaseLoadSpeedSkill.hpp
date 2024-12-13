#pragma once

#include "Game/Player/Player.hpp"
#include "Game/Skill/Skill.hpp"

class IncreaseLoadSpeedSkill : public Skill {
public:
	IncreaseLoadSpeedSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~IncreaseLoadSpeedSkill() = default;

	virtual void use() override;
private:

};