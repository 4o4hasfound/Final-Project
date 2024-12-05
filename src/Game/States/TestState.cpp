#include "Game/States/TestState.hpp"

TestState::TestState(StateManager& manager, RenderWindow& window)
	: State(manager)
	, m_window(window)
	, m_map(window.viewport.size) {
	m_window.viewport.size *= 0.75;
	m_player = m_world.createBody<Adventurer>(&window);
}

void TestState::onEnter() {

}

void TestState::onDestroy() {

}

void TestState::onSuspend() {

}

void TestState::onWakeup() {

}

void TestState::reset() {

}

void TestState::update(RenderWindow& window, float dt) {
	if (m_tickClock.duration() > m_tick) {
		m_tickClock.reset();
		
		m_enemies.update(m_tick, m_world, m_map, window);
	}

	m_enemies.attack(m_player);

	// Update world
	m_world.update(dt);

	if (m_mapHasUpdateOnce) {
		m_enemies.pathFind(&m_map, m_player, window);
	}
		
	// Add additional trails
	if (Mouse::get(Mouse::LEFT).pressed) {
		vec2 position = Mouse::getPosition();
		position *= window.viewport.size / window.size();
		m_map.setTile(position + window.viewport.position, true);
	}
	if (Mouse::get(Mouse::RIGHT).pressed) {
		vec2 position = Mouse::getPosition();
		position *= window.viewport.size / window.size();
		m_map.setTile(position + window.viewport.position, false);
	}

	// Update map and handle collision
	m_map.resolveCollision(m_player);

	m_enemies.resolveCollision(&m_map);

	// Update viewport position
	window.viewport.position = m_player->position - window.viewport.size * 0.5;

	m_map.update(window.viewport);
	m_mapHasUpdateOnce = true;

	m_totalFps += dt;
	m_frameCount += 1;
}

void TestState::render(RenderWindow& window) {
	m_map.draw(window);

	m_enemies.draw(window);

	// Draw character
	m_player->draw(window);

	// Fps
	window.setTitle(std::to_string(m_frameCount / m_totalFps).c_str());
}

bool TestState::shouldClose() {
	return false;
}
