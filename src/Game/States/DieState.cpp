#include "Game/States/DieState.hpp"

DieState::DieState(StateManager& manager, Player* player, RenderWindow* window)
	: State(manager)
	, m_player(player)
	, m_window(window)
	, m_playButton(vec2(800, 100))
	, m_exitButton(vec2(800, 100))
	, m_font("assets/Minecraft.ttf")
	, m_playText(&m_font)
	, m_exitText(&m_font)
	, m_dieText(&m_font) 
	, m_scoreText(&m_font) 
	, m_enemyCountText(&m_font) {
	m_window->viewport.size *= 0.5;

	m_dieText.string = "You died";
	m_dieText.position = vec2(window->size().x * 0.5, 200);
	m_dieText.color = vec4(255, 30, 30, 200);
	m_dieText.size = 140;

	m_scoreText.string = "You have " + std::to_string(m_player->status.level) + " levels, and " + std::to_string(m_player->status.exp) + " experiences";
	m_scoreText.position = vec2(window->size().x * 0.5, 350);
	m_scoreText.color = vec4(255, 100, 100, 200);
	m_scoreText.size = 80;

	m_enemyCountText.string = "You have killed " + std::to_string(m_player->status.enemyCount) + " enemies";
	m_enemyCountText.position = vec2(window->size().x * 0.5, 500);
	m_enemyCountText.color = vec4(255, 100, 100, 200);
	m_enemyCountText.size = 80;

	m_playButton.position = window->size() * 0.5 + vec2(0, 150);
	m_playButton.color = vec4(50, 50, 50, 100);
	m_playButton.enlargeFactor = 1.1;

	m_playText.string = "Retry";
	m_playText.size = 60;
	m_playText.position = window->size() * 0.5 + vec2(0, 150);
	m_playText.color = vec4(255, 255, 255, 100);

	m_exitButton.position = window->size() * 0.5 + vec2(0, 300);
	m_exitButton.color = vec4(50, 50, 50, 100);
	m_exitButton.enlargeFactor = 1.1;

	m_exitText.string = "Exit game";
	m_exitText.size = 60;
	m_exitText.position = window->size() * 0.5 + vec2(0, 300);
	m_exitText.color = vec4(255, 255, 255, 100);

}

void DieState::onEnter() {

}

void DieState::onDestroy()
{
}

void DieState::onSuspend()
{
}

void DieState::onWakeup()
{
}

void DieState::reset()
{
}

void DieState::update(RenderWindow& window, float dt) {
	m_transparency = std::min(255.0f, m_transparency + dt * 63.75f);

	if (!m_audio.playing()) {
		m_audio.play(1.0);
	}

	m_window->viewport.position += vec2(dt, -dt) * 100.0;

	m_playButton.update(dt);
	m_exitButton.update(dt);

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
		m_manager.popState();
		m_manager.emplaceState<MenuState>(m_window);
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

void DieState::render(RenderWindow& window) {
	window.draw(m_dieText);
	window.draw(m_scoreText);
	window.draw(m_enemyCountText);

	Rectangle rect(window.size());
	rect.position = rect.size * 0.5;
	rect.color = vec4(0, 0, 0, 255 - m_transparency);
	rect.absolutePosition = true;
	window.draw(rect);

	window.draw(m_playButton);
	window.draw(m_exitButton);
	window.draw(m_playText);
	window.draw(m_exitText);

}