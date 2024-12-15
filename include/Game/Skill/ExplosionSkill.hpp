#pragma once

#include "Game/Skill/Skill.hpp"

#include "Game/Player/Player.hpp"
#include "Game/Enemy/Enemy.hpp"

#include "Render/Animation.hpp"

class ExplosionSkill : public Skill {
public:
	ExplosionSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~ExplosionSkill() = default;

	virtual void update(float dt);
	virtual void render(RenderWindow& window) override;

	virtual void renderAnimation(const vec2& position, const vec2& size) override;
private:
	float m_clock;
	bool m_used = false;
	Font m_font{ "assets/Minecraft.ttf" };
	Animation m_explosion;
	vec2 m_explodePosition;
	Audio m_audio{ "assets/Guns/RPG/explodeSound.mp3" };
};