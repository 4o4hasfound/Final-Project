#include "Game/Skill/IncreaseHealthSkill.hpp"

IncreaseHealthSkill::IncreaseHealthSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::OneTimeUse, "IncreaseHealth",
		Animation{
		"assets/Skill/IncreaseHealth/animation.png",
		vec2(64, 64),
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
		0.1
		}, player, world, window) {

}

void IncreaseHealthSkill::use() {
	m_player->status.health += 1000;
	m_player->config.health += 1000;
}
