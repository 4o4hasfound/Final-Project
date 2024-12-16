#include "Game/States/MenuState.hpp"

MenuState::MenuState(StateManager& manager, RenderWindow* window)
	: State(manager)
	, m_map(window->size() * 0.5)
	, m_window(window)
	, m_playButton(vec2(800, 100))
	, m_exitButton(vec2(800, 100))
	, m_settingButton(vec2(800, 100))
	, m_font("assets/Minecraft.ttf")
	, m_playText(&m_font)
	, m_exitText(&m_font)
	, m_settingText(&m_font) {
	m_window->viewport.size = m_window->size() * 0.5;

	m_settingButton.position = window->size() * 0.5 - vec2(0, 150);
	m_settingButton.color = vec4(50, 50, 50, 100);
	m_settingButton.enlargeFactor = 1.1;

	m_settingText.string = "Settings";
	m_settingText.size = 60;
	m_settingText.position = window->size() * 0.5 - vec2(0, 150);
	m_settingText.color = vec4(255, 255, 255, 100);

	m_playButton.position = window->size() * 0.5;
	m_playButton.color = vec4(50, 50, 50, 100);
	m_playButton.enlargeFactor = 1.1;

	m_playText.string = "Enter game";
	m_playText.size = 60;
	m_playText.position = window->size() * 0.5;
	m_playText.color = vec4(255, 255, 255, 100);

	m_exitButton.position = window->size() * 0.5 + vec2(0, 150);
	m_exitButton.color = vec4(50, 50, 50, 100);
	m_exitButton.enlargeFactor = 1.1;

	m_exitText.string = "Exit game";
	m_exitText.size = 60;
	m_exitText.position = window->size() * 0.5 + vec2(0, 150);
	m_exitText.color = vec4(255, 255, 255, 100);

}

void MenuState::onEnter() {

}

void MenuState::onDestroy()
{
}

void MenuState::onSuspend()
{
}

void MenuState::onWakeup()
{
}

void MenuState::reset()
{
}

void MenuState::update(RenderWindow& window, float dt) {
	if (!m_audio.playing()) {
		m_audio.play(1.0);
	}

	m_window->viewport.position += vec2(dt, -dt) * 100.0;

	m_map.update(m_window->viewport);

	m_playButton.update(dt);
	m_exitButton.update(dt);
	m_settingButton.update(dt);

	if (m_settingButton.hover) {
		m_settingText.size = 60 * m_settingButton.enlargeFactor;
		m_settingButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_settingText.size = 60;
		m_settingButton.color = vec4(50, 50, 50, 100);
	}
	if (m_settingButton.buttondown) {
		m_clickSound.play(1.0, 2.0);
	}
	if (m_settingButton.pressedAndReleased) {
		m_manager.emplaceState<SettingState>(&m_map, &m_audio, m_window);
	}

	if (m_playButton.hover) {
		m_playText.size = 60 * m_playButton.enlargeFactor;
		m_playButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_playText.size = 60;
		m_playButton.color = vec4(50, 50, 50, 100);
	}
	if (m_playButton.buttondown) {
		m_clickSound.play(1.0, 2.0);
	}
	if (m_playButton.pressedAndReleased) {
		m_manager.emplaceSwitchState<GameState>(m_window);
		m_audio.stop(1.0);
	}

	if (m_exitButton.hover) {
		m_exitText.size = 60 * m_exitButton.enlargeFactor;
		m_exitButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_exitText.size = 60;
		m_exitButton.color = vec4(50, 50, 50, 100);
	}
	if (m_exitButton.buttondown) {
		m_clickSound.play(1.0, 2.0);
	}
	if (m_exitButton.pressedAndReleased) {
		m_shouldClose = true;
	}
}

void MenuState::render(RenderWindow& window) {
	m_map.draw(window);
	Rectangle rect(window.size());
	rect.position = rect.size * 0.5;
	rect.color = vec4(0, 0, 0, 100);
	rect.absolutePosition = true;
	window.draw(rect);
	window.draw(m_playButton);
	window.draw(m_exitButton);
	window.draw(m_settingButton);
	window.draw(m_playText);
	window.draw(m_exitText);
	window.draw(m_settingText);
}