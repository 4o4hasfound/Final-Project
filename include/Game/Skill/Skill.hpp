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
	Skill(SkillType _type, const std::string& _name, const Animation& animation, Player* player, PhysicsWorld* world, RenderWindow* window);
	virtual ~Skill() = default;

	virtual void update(float dt);
	virtual void render(RenderWindow& window);
	virtual void active();

	// One time use
	virtual void use();

	virtual void updateAnimation(float dt);
	virtual void renderAnimation(const vec2& position, const vec2& size);
	vec2 getAnimationSize() const;
	const Texture* getAnimationFrame() const;

	const SkillType type;
	int level = 1;
	const std::string name;
protected:
	PhysicsWorld* m_world;
	Player* m_player;
	RenderWindow* m_window;
	Animation m_animation;
};