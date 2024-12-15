#pragma once

#include "Game/Skill/Skill.hpp"

#include "Game/Player/Player.hpp"

#include "Render/Animation.hpp"

class ExplosiveBulletSkill : public Skill {
public:
	ExplosiveBulletSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~ExplosiveBulletSkill() = default;

	virtual void use() override;
private:
};