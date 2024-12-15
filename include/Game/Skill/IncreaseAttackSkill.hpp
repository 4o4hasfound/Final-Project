#pragma once

#include "Game/Skill/Skill.hpp"

#include "Game/Player/Player.hpp"

#include "Render/Animation.hpp"

class IncreaseAttackSkill : public Skill {
public:
	IncreaseAttackSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~IncreaseAttackSkill() = default;

	virtual void use() override;
private:
};