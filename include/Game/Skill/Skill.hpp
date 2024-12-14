#pragma once

#include "Physics/PhysicsWorld.hpp"

#include "Render/Animation.hpp"
#include "Render/RenderWindow.hpp"

#include "Math/Vector.hpp"

class Player;

class Skill {
public:
	enum SkillType {
		Passive,
		Active,
		OneTimeUse
	};
	Skill(SkillType _type, const Animation& animation, Player* player, PhysicsWorld* world, RenderWindow* window);
	virtual ~Skill() = default;

	virtual void update(float dt);
	virtual void render(RenderWindow& window);
	virtual void active();

	// One time use
	virtual void use();

	void updateAnimation(float dt);
	void renderAnimation(const vec2& position, const vec2& size);
	const Texture* getAnimationFrame() const;

	const SkillType type;
	int level = 1;
protected:
	PhysicsWorld* m_world;
	Player* m_player;
	RenderWindow* m_window;
	Animation m_animation;
};