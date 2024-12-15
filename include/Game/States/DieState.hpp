#pragma once

#include "Engine/State.hpp"
#include "Engine/Audio.hpp"

#include "Game/Map/Map.hpp"
#include "Game/Map/GrassMap.hpp"

#include "Game/States/MenuState.hpp"
#include "Game/States/TestState.hpp"

#include "Physics/PhysicsWorld.hpp"

#include "Render/RenderWindow.hpp"
#include "Render/Button.hpp"

class DieState : public State {
public:
	DieState(StateManager& manager, Player* player, RenderWindow* window);

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
private:
	RenderWindow* m_window;
	Player* m_player;
	Font m_font;
	Audio m_audio{ "assets/Music/Die.ogg" };
	Audio m_clickSound{ "assets/minecraft_click.mp3" };
	Button m_playButton;
	Button m_exitButton;
	Text m_playText;
	Text m_exitText;
	Text m_dieText;
	Text m_scoreText;
	Text m_enemyCountText;

	float m_transparency = 0.0f;

	// Average fps
	float m_totalFps = 0;
	int m_frameCount = 0;

	void drawUI();
};