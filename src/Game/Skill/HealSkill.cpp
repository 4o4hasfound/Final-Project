#include "Game/Skill/HealSkill.hpp"

HealSkill::HealSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::Passive, "Heal",
		Animation{
			{{"assets/Skill/Heal/animation.png"}},
			1.0
		}, player, world, window) {

}

void HealSkill::update(float dt) {
	m_clock -= dt;
	if (m_clock <= 0) {
		m_clock = 0;
		if (m_used) {
			m_used = false;
			m_player->status.healing = false;
			m_clock = 15;
		}
		else if (Keyboard::get(Keyboard::KEY_0).keydown || Keyboard::get(Keyboard::KEY_PAD_0).keydown) {
			m_player->status.healing = true;
			m_used = true;
			m_clock = 3;

		}
	}
	if (m_used) {
		m_animation.update(dt, true);

		float percentage;
		if (level == 1) {
			percentage = 0.2;
		}
		else if (level == 2) {
			percentage = 0.3;
		}
		else if (level == 3) {
			percentage = 0.4;
		}
		else if (level == 4) {
			percentage = 0.5;
		}
		else {
			percentage = 0.6;
		}

		m_player->status.health = std::fmin(m_player->config.health, m_player->status.health + dt / 3.0 * percentage * m_player->config.health);
	}
}

void HealSkill::renderAnimation(const vec2& position, const vec2& size) {
	const Texture* texture = m_animation.getFrame();

	const vec2 textureSize = texture->size();

	float scale = std::min(size.x / textureSize.y, size.y / textureSize.
		y);

	Rectangle rect(texture->size() * scale);
	rect.position = position;
	rect.absolutePosition = true;
	m_window->draw(rect, texture);

	if (!m_used) {
		if (m_clock != 0) {
			rect.color = vec4(58, 58, 58, 100);
			m_window->draw(rect);
		}
		else {
			return;
		}
	}

	Text text(&m_font);
	text.string = std::to_string(static_cast<int>(m_clock));
	text.position = position;
	text.size = 40;
	m_window->draw(text);
}
