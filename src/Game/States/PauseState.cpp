#include "Game/States/PauseState.hpp"

PauseState::PauseState(StateManager& manager, Player* player, EnemyManager* enemies, RenderWindow* window)
	: State(manager)
	, m_window(window)
	, m_player(player)
	, m_enemies(enemies)
	, m_backButton(vec2(400, 80))
	, m_backText(&m_font)
	, m_dieButton(vec2(400, 80))
	, m_dieText(&m_font)
	, m_menuButton(vec2(400, 80))
	, m_menuText(&m_font)
	, m_nextWaveButton(vec2(400, 80))
	, m_nextWaveText(&m_font)
	, m_debugCheckBoxButton(vec2(64, 64))
	, m_debugCheckboxText(&m_font)
	, m_debugDrawAABBCheckBoxButton(vec2(64, 64))
	, m_debugDrawAABBCheckboxText(&m_font)
	, m_debugDrawBVHCheckBoxButton(vec2(64, 64))
	, m_debugDrawBVHCheckboxText(&m_font)
	, m_debugDrawMapAABBCheckBoxButton(vec2(64, 64))
	, m_debugDrawMapAABBCheckboxText(&m_font) {
	// 400 - 32 = 368
	// 368 + 200 = 568
	m_backButton.position = vec2(568, 1000);
	m_backButton.color = vec4(50, 50, 50, 100);
	m_backButton.enlargeFactor = 1.2;

	m_menuButton.position = vec2(1018, 1000);
	m_menuButton.color = vec4(50, 50, 50, 100);
	m_menuButton.enlargeFactor = 1.2;

	m_dieButton.position = vec2(1468, 1000);
	m_dieButton.color = vec4(50, 50, 50, 100);
	m_dieButton.enlargeFactor = 1.2;

	m_nextWaveButton.position = vec2(568, 800);
	m_nextWaveButton.color = vec4(50, 50, 50, 100);
	m_nextWaveButton.enlargeFactor = 1.2;

	m_backText.string = "Back";
	m_backText.position = m_backButton.position;

	m_dieText.string = "Die";
	m_dieText.position = m_dieButton.position;

	m_menuText.string = "Menu";
	m_menuText.position = m_menuButton.position;

	m_nextWaveText.string = "Next wave";
	m_nextWaveText.position = m_nextWaveButton.position;

	m_debugCheckBoxButton.position = vec2(400, 250);
	m_debugCheckBoxButton.color = vec4(50, 50, 50, 100);
	m_debugCheckBoxButton.enlargeFactor = 1.0;

	m_debugCheckboxText.string = "Debug mode";
	m_debugCheckboxText.position = vec2(500, 250);
	m_debugCheckboxText.size = 40;
	m_debugCheckboxText.align = Text::Left;

	m_debugDrawAABBCheckBoxButton.position = vec2(400, 400);
	m_debugDrawAABBCheckBoxButton.color = vec4(50, 50, 50, 100);
	m_debugDrawAABBCheckBoxButton.enlargeFactor = 1.0;

	m_debugDrawAABBCheckboxText.string = "Draw AABB";
	m_debugDrawAABBCheckboxText.position = vec2(500, 400);
	m_debugDrawAABBCheckboxText.size = 40;
	m_debugDrawAABBCheckboxText.align = Text::Left;

	m_debugDrawBVHCheckBoxButton.position = vec2(400, 500);
	m_debugDrawBVHCheckBoxButton.color = vec4(50, 50, 50, 100);
	m_debugDrawBVHCheckBoxButton.enlargeFactor = 1.0;

	m_debugDrawBVHCheckboxText.string = "Draw Bounding Volume Hierarchy(Dynamic AABB Tree)";
	m_debugDrawBVHCheckboxText.position = vec2(500, 500);
	m_debugDrawBVHCheckboxText.size = 40;
	m_debugDrawBVHCheckboxText.align = Text::Left;

	m_debugDrawMapAABBCheckBoxButton.position = vec2(400, 600);
	m_debugDrawMapAABBCheckBoxButton.color = vec4(50, 50, 50, 100);
	m_debugDrawMapAABBCheckBoxButton.enlargeFactor = 1.0;

	m_debugDrawMapAABBCheckboxText.string = "Draw map AABB";
	m_debugDrawMapAABBCheckboxText.position = vec2(500, 600);
	m_debugDrawMapAABBCheckboxText.size = 40;
	m_debugDrawMapAABBCheckboxText.align = Text::Left;
}

void PauseState::onEnter() {

}

void PauseState::onDestroy() {

}

void PauseState::onSuspend() {

}

void PauseState::onWakeup() {

}

void PauseState::reset() {

}

void PauseState::update(RenderWindow& window, float dt) {
	if (Keyboard::get(Keyboard::KEY_ESCAPE).keydown) {
		m_manager.popState();
	}

	m_backButton.update(dt);
	m_dieButton.update(dt);
	m_menuButton.update(dt);
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
		m_manager.popState();
		Audio::stopAll();
	}

	if (m_menuButton.hover) {
		m_menuText.size = 60 * m_menuButton.enlargeFactor;
		m_menuButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_menuText.size = 60;
		m_menuButton.color = vec4(50, 50, 50, 100);
	}
	if (m_menuButton.buttondown) {
		m_clickSound.play(1.0, 2.0);
	}
	if (m_menuButton.pressedAndReleased) {
		m_manager.emplaceSwitchState<MenuState>(m_window);
		Audio::stopAll();
	}

	if (m_dieButton.hover) {
		m_dieText.size = 60 * m_dieButton.enlargeFactor;
		m_dieButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_dieText.size = 60;
		m_dieButton.color = vec4(50, 50, 50, 100);
	}
	if (m_dieButton.buttondown) {
		m_clickSound.play(1.0, 2.0);
	}
	if (m_dieButton.pressedAndReleased) {
		m_manager.emplaceSwitchState<DieState>(m_player, m_window);
		Audio::stopAll();
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

	if (Config::debug) {
		m_nextWaveButton.position = vec2(568, 800);
	}
	else {
		m_nextWaveButton.position = vec2(568, 450);
	}
	m_nextWaveButton.update(dt);
	m_nextWaveText.position = m_nextWaveButton.position;

	if (m_nextWaveButton.hover) {
		m_nextWaveText.size = 60 * m_nextWaveButton.enlargeFactor;
		m_nextWaveButton.color = vec4(100, 100, 100, 100);
	}
	else {
		m_nextWaveText.size = 60;
		m_nextWaveButton.color = vec4(50, 50, 50, 100);
	}
	if (m_nextWaveButton.buttondown) {
		m_clickSound.play(1.0, 2.0);
	}
	if (m_nextWaveButton.pressedAndReleased) {
		m_enemies->clock = 0;
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

void PauseState::render(RenderWindow& window) {
	if (m_removed) {
		m_manager.topState()->render(window);
		return;
	}
	m_manager.topState(1)->render(window);

	Rectangle rect(window.size());
	rect.position = rect.size * 0.5;
	rect.color = vec4(0, 0, 0, 100);
	rect.absolutePosition = true;
	window.draw(rect);

	Text title(&m_font);
	title.string = "Pause";
	title.size = 140;
	title.position = vec2(960, 100);

	window.draw(title);
	window.draw(m_backButton);
	window.draw(m_backText);
	window.draw(m_menuButton);
	window.draw(m_menuText);
	window.draw(m_dieButton);
	window.draw(m_dieText);
	window.draw(m_nextWaveButton);
	window.draw(m_nextWaveText);

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