#pragma once

#include <memory>

#include "Engine/State.hpp"

#include "Render/Font.hpp"
#include "Render/Text.hpp"

#include "Physics/PhysicsWorld.hpp"

#include "Game/Player/Player.hpp"

#include "Game/Skill/Skill.hpp"
#include "Game/Skill/HealSkill.hpp"

#include "Engine/Mouse.hpp"

class ChooseSkillState : public State {
public:
	ChooseSkillState(StateManager& manager, Player* player, PhysicsWorld* world, RenderWindow* window);

	// Called when the state is entered
	virtual void onEnter() override;

	// Called when the state is destroyed
	virtual void onDestroy() override;

	// Called when the state is suspended(another state is pushed on top of it)
	virtual void onSuspend() override;

	// Called when the state is resumed after suspension
	virtual void onWakeup() override;

	virtual void reset() override;
	virtual void update(RenderWindow& window, float dt) override;
	virtual void render(RenderWindow& window) override;
	virtual bool shouldClose() override;
private:
	RenderWindow* m_window;
	PhysicsWorld* m_world;
	Player* m_player;
	Font m_font{ "assets/Minecraft.ttf" };
	std::vector<std::unique_ptr<Skill>> m_skills;

	// Average fps
	float m_totalFps = 0;
	int m_frameCount = 0;
};