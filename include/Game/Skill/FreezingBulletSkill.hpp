#pragma once

#include "Game/Skill/Skill.hpp"

#include "Game/Player/Player.hpp"

#include "Render/Animation.hpp"

class FreezingBulletSkill : public Skill {
public:
	FreezingBulletSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~FreezingBulletSkill() = default;

	virtual void use() override;
private:
};