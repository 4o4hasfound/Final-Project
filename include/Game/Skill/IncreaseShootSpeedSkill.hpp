#pragma once

#include "Game/Player/Player.hpp"
#include "Game/Skill/Skill.hpp"

class IncreaseShootSpeedSkill : public Skill {
public:
	IncreaseShootSpeedSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~IncreaseShootSpeedSkill() = default;

	virtual void use() override;
private:

};