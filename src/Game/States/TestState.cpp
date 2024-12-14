#include "Game/States/TestState.hpp"

TestState::TestState(StateManager& manager, RenderWindow* window)
	: State(manager)
	, m_window(window)
	, m_map(window->viewport.size * 0.75 / 0.5)
	, m_enemies(&m_world)
	, m_font("assets/Minecraft.ttf") {
	m_window->viewport.size *= 0.75 / 0.5;
	m_window->viewport.position = vec2(0);
	m_player = m_world.createBody<Adventurer>(&m_world, window);
}

void TestState::onEnter() {
	//m_audio.play(1.0, true);
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

		if (m_mapHasUpdateOnce) {
			m_enemies.update(m_tick, m_world, m_map, window);
		}
	}

	m_enemies.attack(m_player);

	// Update world
	m_world.update(dt);

	if (m_player->status.levelUp) {
		m_player->status.levelUp = 0;
		Audio::stopAll();
		m_manager.emplaceState<ChooseSkillState>(m_player, &m_world, m_window);
	}

	if (m_mapHasUpdateOnce) {
		m_enemies.pathFind(&m_map, m_player, window);
	}
		
	//// Add additional trails
	//if (Mouse::get(Mouse::LEFT).pressed) {
	//	vec2 position = Mouse::getPosition();
	//	position *= window.viewport.size / window.size();
	//	m_map.setTile(position + window.viewport.position, true);
	//}
	//if (Mouse::get(Mouse::RIGHT).pressed) {
	//	vec2 position = Mouse::getPosition();
	//	position *= window.viewport.size / window.size();
	//	m_map.setTile(position + window.viewport.position, false);
	//}

	// Update map and handle collision
	m_map.resolveCollision(m_player);

	m_enemies.resolveCollision(&m_map);

	// Update viewport position
	window.viewport.position = m_player->position - window.viewport.size * 0.5;

	m_map.update(window.viewport);
	m_mapHasUpdateOnce = true;

	m_frameCount = 1;
	m_totalFps = dt;
}

void TestState::render(RenderWindow& window) {
	m_map.draw(window);

	m_enemies.draw(window);

	// Draw character
	m_player->draw(window);

	drawProjectile();

	drawUI();

	//m_world.DebugDraw(window);

	// Fps
	window.setTitle(std::to_string(m_frameCount / m_totalFps).c_str());
}

bool TestState::shouldClose() {
	return false;
}

void TestState::drawProjectile() {
	auto bullets = m_world.getBodies<Projectile>(RigidBody::Projectile);

	for (Projectile* projectile : bullets) {
		projectile->draw(*m_window);
	}
}

void TestState::drawUI() {
	Rectangle rect(m_uiBar.size() * 1.5);
	rect.position = vec2(960, 990);
	rect.absolutePosition = true;
	rect.color = vec4(255);
	m_window->draw(rect); // Draw this first

	const float healthBarWidth = rect.size.x * 0.371;
	Rectangle healthBarRed(vec2(m_player->status.health / m_player->config.health * healthBarWidth, rect.size.y * 0.4));

	healthBarRed.position = vec2(rect.position.x - rect.size.x * 0.227 - healthBarWidth * 0.5 + healthBarRed.size.x * 0.5, rect.position.y - rect.size.y * 0.18);
	healthBarRed.color = vec4(136, 8, 8, 255);
	healthBarRed.absolutePosition = true;

	const float expBarWidth = rect.size.x * 0.371;
	Rectangle expBarRed(vec2((m_player->status.exp) / 10.0 * expBarWidth, rect.size.y * 0.34));

	expBarRed.position = vec2(rect.position.x - rect.size.x * 0.227 - expBarWidth * 0.5 + expBarRed.size.x * 0.5, rect.position.y + rect.size.y * 0.18);
	expBarRed.color = vec4(93, 151, 231, 255);
	expBarRed.absolutePosition = true;

	m_window->draw(healthBarRed);
	m_window->draw(expBarRed);


	m_window->draw(rect, &m_uiBar);

	Text text(&m_font);
	text.string = std::to_string(m_player->status.level);
	text.position = vec2(rect.position.x - rect.size.x * 0.5 + rect.size.x * 0.275, rect.position.y - rect.size.y * 0.16);
	text.size = 80;
	text.absolutePosition = true;
	m_window->draw(text);
}
