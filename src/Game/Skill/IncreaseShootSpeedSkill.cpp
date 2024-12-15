#include "Game/Skill/IncreaseShootSpeedSkill.hpp"

IncreaseShootSpeedSkill::IncreaseShootSpeedSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::OneTimeUse, "IncreaseAttackSpeed",
		Animation{
			{{"assets/Skill/IncreaseShootSpeed/animation.png"}},
			1.0
		}, player, world, window) {

}

void IncreaseShootSpeedSkill::use() {
	m_player->status.shootSpeed += 0.1;
}
