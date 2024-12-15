#pragma once

#include "Game/Player/Player.hpp"
#include "Game/Skill/Skill.hpp"

class InvincibleShieldSkill : public Skill {
public:
	InvincibleShieldSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~InvincibleShieldSkill() = default;

	virtual void update(float dt) override;
	virtual void render(RenderWindow& window) override;

	virtual void renderAnimation(const vec2& position, const vec2& size) override;
private:
	float m_clock;
	Font m_font{ "assets/Minecraft.ttf" };
};