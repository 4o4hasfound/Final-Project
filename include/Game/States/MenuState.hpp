#pragma once

#include "Engine/State.hpp"
#include "Engine/Audio.hpp"

#include "Game/Map/Map.hpp"
#include "Game/Map/GrassMap.hpp"

#include "Game/States/TestState.hpp"

#include "Physics/PhysicsWorld.hpp"

#include "Render/RenderWindow.hpp"
#include "Render/Button.hpp"

class MenuState : public State {
public:
	MenuState(StateManager& manager, RenderWindow* window);

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
	GrassMap m_map;
	Font m_font;
	Audio m_audio{ "assets/Music/menu.ogg" };
	Audio m_clickSound{ "assets/minecraft_click.mp3" };
	Button m_playButton;
	Button m_exitButton;
	Button m_settingButton;
	Text m_playText;
	Text m_exitText;
	Text m_settingText;

	// Average fps
	float m_totalFps = 0;
	int m_frameCount = 0;

	void drawUI();
};