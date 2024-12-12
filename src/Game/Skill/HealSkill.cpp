#include "Game/Skill/HealSkill.hpp"

HealSkill::HealSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Animation{
		"assets/Skill/Heal/animation.png",
		vec2(32, 32),
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

void HealSkill::use() {
	m_player->status.health = m_player->config.health;
}
