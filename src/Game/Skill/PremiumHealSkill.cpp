#include "Game/Skill/PremiumHealSkill.hpp"

PremiumHealSkill::PremiumHealSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::Passive, "PremiumHeal",
		Animation{
			"assets/Skill/PremiumHeal/animation.png",
			vec2(64),
			{
				vec2(0, 0),
				vec2(0, 1),
				vec2(0, 2),
				vec2(0, 3),
				vec2(0, 4),
				vec2(0, 5),
				vec2(0, 6),
				vec2(0, 7),
				vec2(0, 8),
				vec2(0, 9),
				vec2(0, 10),
				vec2(0, 11),
				vec2(0, 12),
				vec2(0, 13),
				vec2(0, 14),
				vec2(0, 15),
				vec2(0, 16),
				vec2(0, 17),
				vec2(0, 18),
				vec2(0, 19),
				vec2(0, 20),
				vec2(0, 21),
				vec2(0, 22),
				vec2(0, 23),
				vec2(0, 24),
				vec2(0, 25),
				vec2(0, 26),
				vec2(0, 27),
				vec2(0, 28),
				vec2(0, 29),
				vec2(0, 30),
				vec2(0, 31),
				vec2(0, 32),
				vec2(0, 33),
				vec2(0, 34),
				vec2(0, 35),
				vec2(0, 36),
				vec2(0, 37),
				vec2(0, 38),
				vec2(0, 39),
				vec2(0, 40),
				vec2(0, 41),
				vec2(0, 42),
				vec2(0, 43),
				vec2(0, 44),
				vec2(0, 45),
				vec2(0, 46),
				vec2(0, 47),
				vec2(0, 48),
				vec2(0, 49),
				vec2(0, 50),
				vec2(0, 51),
				vec2(0, 52),
				vec2(0, 53),
				vec2(0, 54),
				vec2(0, 55),
				vec2(0, 56),
				vec2(0, 57),
				vec2(0, 58),
				vec2(0, 59),
				vec2(0, 60),
				vec2(0, 61),
				vec2(0, 62),
				vec2(0, 63),
				vec2(0, 64),
				vec2(0, 65),
				vec2(0, 66),
				vec2(0, 67),
				vec2(0, 68),
				vec2(0, 69),
				vec2(0, 70),
				vec2(0, 71),
				vec2(0, 72),
				vec2(0, 73),
				vec2(0, 74),
				vec2(0, 75),
				vec2(0, 76),
				vec2(0, 77),
				vec2(0, 78),
				vec2(0, 79),
				vec2(0, 80),
			},
			0.02
		}, player, world, window) {

}

void PremiumHealSkill::update(float dt) {
	m_clock -= dt;
	if (m_clock <= 0) {
		m_clock = 0;
		if (m_used) {
			m_used = false;
			m_player->status.premiumHealing = false;
			m_clock = 60;
		}
		else if (Keyboard::get(Keyboard::KEY_1).keydown || Keyboard::get(Keyboard::KEY_PAD_1).keydown) {
			m_player->status.premiumHealing = true;
			m_used = true;
			m_clock = 9;

		}
	}

	m_animation.update(dt, true);

	if (m_used) {
		m_player->status.health = std::fmin(m_player->config.health, m_player->status.health + dt / 9.0 * m_player->config.health);
	}
}

void PremiumHealSkill::renderAnimation(const vec2& position, const vec2& size) {
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
