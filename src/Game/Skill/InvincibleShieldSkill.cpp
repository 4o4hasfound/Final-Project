#include "Game/Skill/InvincibleShieldSkill.hpp"

InvincibleShieldSkill::InvincibleShieldSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::OneTimeUse, Animation{
		"assets/Skill/InvincibleShield/animation.png",
		vec2(60, 60),
		{
			vec2(0, 0),
			vec2(0, 1),
			vec2(0, 2),
			vec2(0, 3),
			vec2(0, 4),
			vec2(0, 5),
			vec2(0, 6),
			vec2(0, 7),
		},
		0.05
		}, player, world, window) {

}

void InvincibleShieldSkill::update(float dt) {
	m_clock -= dt;
	if (m_clock <= 0) {
		if (m_player->status.invincible) {
			m_player->status.invincible = false;
			if (level == 1) {
				m_clock = 25;
			}
			else if (level == 2) {
				m_clock = 24;
			}
			else if (level == 3) {
				m_clock = 23;
			}
			else if (level == 4) {
				m_clock = 22;
			}
			else {
				m_clock = 20;
			}
		}
		else {
			m_player->status.invincible = true;
			m_animation.reset();
			if (level == 1) {
				m_clock = 5;
			}
			else if (level == 2) {
				m_clock = 6;
			}
			else if (level == 3) {
				m_clock = 7;
			}
			else if (level == 4) {
				m_clock = 8;
			}
			else {
				m_clock = 10;
			}
		}
	}
	if (m_player->status.invincible) {
		m_animation.update(dt, true);
	}
}

void InvincibleShieldSkill::render(RenderWindow& window) {
	if (m_player->status.invincible) {
		Rectangle rect(vec2(240, 240));
		rect.position = m_player->position;
		window.draw(rect, m_animation.getFrame());
	}
}

void InvincibleShieldSkill::active() {

}

void InvincibleShieldSkill::use() {

}
