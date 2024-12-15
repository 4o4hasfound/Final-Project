#include "Game/Skill/FreezingBulletSkill.hpp"

FreezingBulletSkill::FreezingBulletSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::OneTimeUse, "IncreaseAttackSpeed",
		Animation{
			{{"assets/Skill/FreezingBullet/animation.png"}},
			1.0
		}, player, world, window) {

}

void FreezingBulletSkill::use() {
	m_player->status.freezingBullet = true;
	m_player->status.freezingDuration += 1.0;
}
