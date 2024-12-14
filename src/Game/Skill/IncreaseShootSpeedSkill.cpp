#include "Game/Skill/IncreaseShootSpeedSkill.hpp"

IncreaseShootSpeedSkill::IncreaseShootSpeedSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::OneTimeUse, Animation{
		"assets/Skill/IncreaseShootSpeed/SCAR-100ms.png",
		vec2(80, 32),
		{
			vec2(0, 0),
			vec2(0, 1),
		},
		0.1
		}, player, world, window) {

}

void IncreaseShootSpeedSkill::use() {
	m_player->status.shootSpeed += 0.2;
}
