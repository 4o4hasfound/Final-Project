#include "Game/Skill/IncreaseMovementSpeedSkill.hpp"

IncreaseMovementSpeedSkill::IncreaseMovementSpeedSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::OneTimeUse, "IncreaseMovementSpeed",
		Animation{
		"assets/Skill/IncreaseMovementSpeed/animation.png",
		vec2(64, 64),
		{
			vec2(0, 0),
			vec2(0, 1),
			vec2(0, 2),
			vec2(0, 3),
			vec2(0, 4),
			vec2(0, 5),
		},
		0.1
		}, player, world, window) {

}

void IncreaseMovementSpeedSkill::use() {
	m_player->config.speed += 5;
}
