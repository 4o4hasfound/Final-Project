#pragma once

#include "Engine/Engine.hpp"
#include "Engine/State.hpp"
#include "Engine/Audio.hpp"
#include "Engine/configuration.hpp"

#include "Game/Map/Map.hpp"
#include "Game/Map/GrassMap.hpp"

#include "Game/States/GameState.hpp"

#include "Physics/PhysicsWorld.hpp"

#include "Render/RenderWindow.hpp"
#include "Render/Button.hpp"

class SettingState : public State {
public:
	SettingState(StateManager& manager, GrassMap* map, Audio* audio, RenderWindow* window);
	~SettingState() = default;

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
	GrassMap* m_map;
	Audio* m_audio;
	Font m_font{ "assets/Minecraft.ttf" };
	Audio m_clickSound{ "assets/minecraft_click.mp3" };

	Button m_backButton;
	Text m_backText;

	Texture m_check{ "assets/Checked.png" };
	Texture m_unCheck{ "assets/UnChecked.png" };

	Button m_debugCheckBoxButton;
	Text m_debugCheckboxText;

	Button m_debugDrawAABBCheckBoxButton;
	Text m_debugDrawAABBCheckboxText;

	Button m_debugDrawBVHCheckBoxButton;
	Text m_debugDrawBVHCheckboxText;

	Button m_debugDrawMapAABBCheckBoxButton;
	Text m_debugDrawMapAABBCheckboxText;

	// Average fps
	float m_totalFps = 0;
	int m_frameCount = 0;

	void drawUI();
};