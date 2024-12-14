#include "Game/States/MenuState.hpp"

MenuState::MenuState(StateManager& manager, RenderWindow* window)
	: State(manager)
	, m_map(window->viewport.size * 0.5)
	, m_window(window)
	, m_playButton(vec2(800, 100))
	, m_font("assets/Minecraft.ttf")
	, m_playText(&m_font) {
	m_audio.play(1.0);
	m_window->viewport.size *= 0.5;
	m_playButton.position = window->size() * 0.5;
	m_playButton.color = vec4(100, 100, 100, 100);
	m_playButton.enlargeFactor = 1.2;
	m_playText.string = "Enter game";
	m_playText.size = 60;
	m_playText.position = window->size() * 0.5;
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
	m_window->viewport.position += vec2(dt, -dt) * 100.0;
	m_map.update(m_window->viewport);

	m_playButton.update(dt);

	if (m_playButton.hover) {
		m_playText.size = 80;
	}
	else {
		m_playText.size = 60;
	}
	if (m_playButton.pressedAndReleased) {
		m_manager.emplaceState<TestState>(m_window);
		m_audio.stop();
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
	window.draw(m_playText);
}

bool MenuState::shouldClose() {
	return false;
}
