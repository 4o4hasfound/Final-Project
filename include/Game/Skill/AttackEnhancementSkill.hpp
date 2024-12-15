#pragma once

#include "Game/Skill/Skill.hpp"

#include "Game/Player/Player.hpp"

#include "Render/Animation.hpp"

class AttackEnhancementSkill : public Skill {
public:
	AttackEnhancementSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~AttackEnhancementSkill() = default;

	virtual void update(float dt);

	virtual void renderAnimation(const vec2& position, const vec2& size) override;
private:
	float m_clock;
	bool m_used = false;
	Font m_font{ "assets/Minecraft.ttf" };
};