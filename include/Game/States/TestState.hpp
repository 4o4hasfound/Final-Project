#pragma once

#include "Engine/Engine.hpp"
#include "Engine/State.hpp"
#include "Engine/configuration.hpp"

#include "Physics/PhysicsWorld.hpp"
#include "Physics/RigidBody.hpp"

#include "Game/Map/Map.hpp"
#include "Game/Map/GrassMap.hpp"

#include "Game/Player/Player.hpp"
#include "Game/Player/Mushroom.hpp"
#include "Game/Player/Adventurer.hpp"

#include "Game/Enemy/Enemy.hpp"
#include "Game/Enemy/EnemyManager.hpp"
#include "Game/Enemy/DroidZapper.hpp"

#include "Game/States/ChooseSkillState.hpp"
#include "Game/States/DieState.hpp"
#include "Game/States/PauseState.hpp"

#include "Game/Weapon/Weapon.hpp"
#include "Game/Weapon/Rifle.hpp"

#include "Game/Entity/Entity.hpp"

#include "Render/Font.hpp"
#include "Render/Text.hpp"

#include "Engine/Mouse.hpp"

class TestState : public State {
public:
	TestState(StateManager& manager, RenderWindow* window);

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
	PhysicsWorld m_world;
	GrassMap m_map;
	EnemyManager m_enemies;
	Player* m_player;
	Font m_font;
	Text m_waveText;
	Texture m_uiBar{ "assets/UIBar.png" };
	Audio m_audio{ "assets/music.ogg" };

	// Only generate the enemy every few ticks(a constant duration)
	Clock m_tickClock;
	// How long is a tick in milliseconds
	float m_tick = 0.01;

	// Average fps
	float m_totalFps = 0;
	int m_frameCount = 0;

	bool m_mapHasUpdateOnce = false;

	void drawProjectile();
	void drawUI();
	void drawWave();
};