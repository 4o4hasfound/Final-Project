#pragma once

#include "Game/Player/Player.hpp"
#include "Game/Skill/Skill.hpp"

class IncreaseMovementSpeedSkill : public Skill {
public:
	IncreaseMovementSpeedSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~IncreaseMovementSpeedSkill() = default;

	virtual void use() override;
private:

};