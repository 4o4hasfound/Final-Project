#pragma once

#include "Engine/Keyboard.hpp"

#include "Game/Player/Player.hpp"
#include "Game/Skill/Skill.hpp"

class HealSkill : public Skill {
public:
	HealSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~HealSkill() = default;

	virtual void update(float dt) override;

	virtual void renderAnimation(const vec2& position, const vec2& size) override;
private:
	float m_clock;
	bool m_used;
	Font m_font{ "assets/Minecraft.ttf" };
};