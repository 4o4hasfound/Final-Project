#include "Game/Skill/IncreaseLoadSpeedSkill.hpp"

IncreaseLoadSpeedSkill::IncreaseLoadSpeedSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Animation{
		"assets/Skill/IncreaseLoadSpeed/load.png",
		vec2(512, 512),
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
		},
		0.05
		}, player, world, window) {

}

void IncreaseLoadSpeedSkill::use() {
	m_player->status.loadSpeed += 0.2;
}
