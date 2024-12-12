#pragma once

#include "Game/Skill/Skill.hpp"

#include "Game/Player/Player.hpp"

#include "Render/Animation.hpp"

class HealSkill : public Skill {
public:
	HealSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~HealSkill() = default;

	virtual void use() override;
private:

};