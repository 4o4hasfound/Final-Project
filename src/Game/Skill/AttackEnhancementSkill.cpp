#include "Game/Skill/AttackEnhancementSkill.hpp"

AttackEnhancementSkill::AttackEnhancementSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::Passive, "AttackEnhancementSkill",
		Animation{
			{{"assets/Skill/AttackEnhancement/animation.png"}},
			1.0
		}, player, world, window) {

}

void AttackEnhancementSkill::update(float dt) {
	m_clock -= dt;
	if (m_clock <= 0) {
		if (m_used) {
			m_player->status.damageScale = 1.0;
			m_clock = 30;
			m_used = 0;
		}
		else {
			m_used = 1;
			m_clock = 10 + level - 1;

			if (level == 1) {
				m_player->status.damageScale = 1.3;
			}
			else if (level == 2) {
				m_player->status.damageScale = 1.7;
			}
			else if (level == 3) {
				m_player->status.damageScale = 2.2;
			}
			else if (level == 4) {
				m_player->status.damageScale = 2.9;
			}
			else {
				m_player->status.damageScale = 3.5;
			}
		}
	}
}

void AttackEnhancementSkill::renderAnimation(const vec2& position, const vec2& size) {
	const Texture* texture = m_animation.getFrame();

	const vec2 textureSize = texture->size();

	float scale = std::min(size.x / textureSize.y, size.y / textureSize.
		y);

	Rectangle rect(texture->size() * scale);
	rect.position = position;
	rect.absolutePosition = true;
	m_window->draw(rect, texture);

	if (!m_used) {
		rect.color = vec4(58, 58, 58, 100);
		m_window->draw(rect);
	}

	Text text(&m_font);
	text.string = std::to_string(static_cast<int>(m_clock));
	text.position = position;
	text.size = 40;
	m_window->draw(text);
}
