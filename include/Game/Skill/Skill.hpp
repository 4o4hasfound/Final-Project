#pragma once

#include "Physics/PhysicsWorld.hpp"

#include "Render/Animation.hpp"
#include "Render/RenderWindow.hpp"

#include "Math/Vector.hpp"

class Player;

class Skill {
public:
	Skill(const Animation& animation, Player* player, PhysicsWorld* world, RenderWindow* window);
	virtual ~Skill() = default;

	virtual void update();
	virtual void render();
	virtual void use();

	void updateAnimation(float dt);
	void renderAnimation(const vec2& position, const vec2& size);
	const Texture* getAnimationFrame() const;
protected:
	PhysicsWorld* m_world;
	Player* m_player;
	RenderWindow* m_window;
	Animation m_animation;
};