#include "Game/Skill/ExplosiveBulletSkill.hpp"

ExplosiveBulletSkill::ExplosiveBulletSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::OneTimeUse, "IncreaseAttackSpeed",
		Animation{
			{{"assets/Skill/ExplosiveBullet/animation.png"}},
			1.0
		}, player, world, window) {

}

void ExplosiveBulletSkill::use() {
	if (m_player->status.explosiveBullet) {
		m_player->status.explosiveDamage += 0.2;
	}
	else {
		m_player->status.explosiveDamage = 0.25;
	}
	if (m_player->status.explosiveBullet) {
		m_player->status.explosiveRadius += 25.0f;
	}
	else {
		m_player->status.explosiveRadius = 50.0f;
	}
	m_player->status.explosiveBullet = true;
}
