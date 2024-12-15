#pragma once

#include "Game/Skill/Skill.hpp"

#include "Game/Player/Player.hpp"

#include "Render/Animation.hpp"

class IncreaseHealthSkill : public Skill {
public:
	IncreaseHealthSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~IncreaseHealthSkill() = default;

	virtual void use() override;
private:
};