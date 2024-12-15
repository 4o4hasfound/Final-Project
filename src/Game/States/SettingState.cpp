#include "Game/States/SettingState.hpp"

SettingState::SettingState(StateManager& manager, GrassMap* map, Audio* audio, RenderWindow* window)
	: State(manager)
	, m_map(map)
	, m_window(window)
	, m_audio(audio)
	, m_backButton(vec2(500, 80))
	, m_debugCheckBoxButton(vec2(64, 64))
	, m_debugCheckboxText(&m_font)
	, m_debugDrawAABBCheckBoxButton(vec2(64, 64))
	, m_debugDrawAABBCheckboxText(&m_font)
	, m_debugDrawBVHCheckBoxButton(vec2(64, 64))
	, m_debugDrawBVHCheckboxText(&m_font)
	, m_debugDrawMapAABBCheckBoxButton(vec2(64, 64))
	, m_debugDrawMapAABBCheckboxText(&m_font)
	, m_backText(&m_font) {
	m_backButton.position = vec2(800, 1000);
	m_backButton.color = vec4(50, 50, 50, 100);
	m_backButton.enlargeFactor = 1.2;
	
	m_backText.string = "Back";
	m_backText.position = m_backButton.position;

	m_debugCheckBoxButton.position = vec2(400, 400);
	m_debugCheckBoxButton.color = vec4(50, 50, 50, 100);
	m_debugCheckBoxButton.enlargeFactor = 1.0;
	
	m_debugCheckboxText.string = "Debug mode";
	m_debugCheckboxText.position = vec2(500, 400);
	m_debugCheckboxText.size = 40;
	m_debugCheckboxText.align = Text::Left;

	m_debugDrawAABBCheckBoxButton.position = vec2(400, 600);
	m_debugDrawAABBCheckBoxButton.color = vec4(50, 50, 50, 100);
	m_debugDrawAABBCheckBoxButton.enlargeFactor = 1.0;

	m_debugDrawAABBCheckboxText.string = "Draw AABB";
	m_debugDrawAABBCheckboxText.position = vec2(500, 600);
	m_debugDrawAABBCheckboxText.size = 40;
	m_debugDrawAABBCheckboxText.align = Text::Left;

	m_debugDrawBVHCheckBoxButton.position = vec2(400, 700);
	m_debugDrawBVHCheckBoxButton.color = vec4(50, 50, 50, 100);
	m_debugDrawBVHCheckBoxButton.enlargeFactor = 1.0;

	m_debugDrawBVHCheckboxText.string = "Draw Bounding Volume Hierarchy(Dynamic AABB Tree)";
	m_debugDrawBVHCheckboxText.position = vec2(500, 700);
	m_debugDrawBVHCheckboxText.size = 40;
	m_debugDrawBVHCheckboxText.align = Text::Left;

	m_debugDrawMapAABBCheckBoxButton.position = vec2(400, 800);
	m_debugDrawMapAABBCheckBoxButton.color = vec4(50, 50, 50, 100);
	m_debugDrawMapAABBCheckBoxButton.enlargeFactor = 1.0;

	m_debugDrawMapAABBCheckboxText.string = "Draw map AABB";
	m_debugDrawMapAABBCheckboxText.position = vec2(500, 800);
	m_debugDrawMapAABBCheckboxText.size = 40;
	m_debugDrawMapAABBCheckboxText.align = Text::Left;
}

void SettingState::onEnter() {

}

void SettingState::onDestroy() {

}

void SettingState::onSuspend() {

}

void SettingState::onWakeup() {

}

void SettingState::reset() {

}

void SettingState::update(RenderWindow& window, float dt) {
	if (!m_audio->playing()) {
		m_audio->play(1.0);
	}

	m_window->viewport.position += vec2(dt, -dt) * 100.0;
	m_map->update(window.viewport);

	m_backButton.update(dt);
	m_debugCheckBoxButton.update(dt);

	if (m_backButton.hover) {
		m_backText.size = 60 * m_backButton.enlargeFactor;
		m_backButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_backText.size = 60;
		m_backButton.color = vec4(50, 50, 50, 100);
	}
	if (m_backButton.buttondown) {
		m_clickSound.play(1.0, 2.0);
	}
	if (m_backButton.pressedAndReleased) {
		m_manager.popState(1);
	}

	if (m_debugCheckBoxButton.hover) {
		m_debugCheckBoxButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_debugCheckBoxButton.color = vec4(50, 50, 50, 100);
	}
	if (m_debugCheckBoxButton.pressedAndReleased) {
		Config::debug = !Config::debug;
	}

	if (!Config::debug) {
		Config::debugDrawAABB = Config::debugDrawBVH = Config::debugDrawMapAABB = false;
		return;
	}

	m_debugDrawAABBCheckBoxButton.update(dt);
	m_debugDrawBVHCheckBoxButton.update(dt);
	m_debugDrawMapAABBCheckBoxButton.update(dt);

	if (m_debugDrawAABBCheckBoxButton.hover) {
		m_debugDrawAABBCheckBoxButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_debugDrawAABBCheckBoxButton.color = vec4(50, 50, 50, 100);
	}
	if (m_debugDrawAABBCheckBoxButton.pressedAndReleased) {
		Config::debugDrawAABB = !Config::debugDrawAABB;
	}

	if (m_debugDrawBVHCheckBoxButton.hover) {
		m_debugDrawBVHCheckBoxButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_debugDrawBVHCheckBoxButton.color = vec4(50, 50, 50, 100);
	}
	if (m_debugDrawBVHCheckBoxButton.pressedAndReleased) {
		Config::debugDrawBVH = !Config::debugDrawBVH;
	}

	if (m_debugDrawMapAABBCheckBoxButton.hover) {
		m_debugDrawMapAABBCheckBoxButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_debugDrawMapAABBCheckBoxButton.color = vec4(50, 50, 50, 100);
	}
	if (m_debugDrawMapAABBCheckBoxButton.pressedAndReleased) {
		Config::debugDrawMapAABB = !Config::debugDrawMapAABB;
	}
}

void SettingState::render(RenderWindow& window) {
	m_map->draw(*m_window);

	Rectangle rect(window.size());
	rect.position = rect.size * 0.5;
	rect.color = vec4(0, 0, 0, 100);
	rect.absolutePosition = true;
	window.draw(rect);

	Text title(&m_font);
	title.string = "Setting";
	title.size = 140;
	title.position = vec2(960, 200);

	window.draw(title);
	window.draw(m_backButton);
	window.draw(m_backText);

	window.draw(m_debugCheckBoxButton);
	window.draw(m_debugCheckBoxButton, Config::debug ? &m_check : &m_unCheck);
	window.draw(m_debugCheckboxText);

	if (!Config::debug) {
		return;
	}

	window.draw(m_debugDrawAABBCheckBoxButton);
	window.draw(m_debugDrawAABBCheckBoxButton, Config::debugDrawAABB ? &m_check : &m_unCheck);
	window.draw(m_debugDrawAABBCheckboxText);

	window.draw(m_debugDrawBVHCheckBoxButton);
	window.draw(m_debugDrawBVHCheckBoxButton, Config::debugDrawBVH ? &m_check : &m_unCheck);
	window.draw(m_debugDrawBVHCheckboxText);

	window.draw(m_debugDrawMapAABBCheckBoxButton);
	window.draw(m_debugDrawMapAABBCheckBoxButton, Config::debugDrawMapAABB ? &m_check : &m_unCheck);
	window.draw(m_debugDrawMapAABBCheckboxText);
}