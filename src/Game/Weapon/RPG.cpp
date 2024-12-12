#include "Game/Weapon/RPG.hpp"

static WeaponConfig weaponConfig{
	10.0,
	2,
	1,
	0.4,
	2.0,

	2.0,
	vec2{192, 32},
	vec2{90.5, 18.5},

	"assets/Guns/RPG/shoot.png",
	std::vector<vec2>{
		{0, 0},
		{0, 1},
		{0, 2},
		{0, 3},
		{0, 4},
		{0, 5},
		{0, 6},
		{0, 7},
	},
	0.1,
	"assets/Guns/RPG/shootSound.mp3",

	"assets/Guns/RPG/load.png",
	std::vector<vec2>{
		{0, 0},
		{0, 1},
		{0, 2},
		{0, 3},
		{0, 4},
		{0, 5},
		{0, 6},
		{0, 7},
		{0, 8},
		{0, 9},
		{0, 10},
		{0, 11},
		{0, 12},
		{0, 13},
		{0, 14},
		{0, 15},
	},
	0.1,
	"assets/Guns/RPG/loadSound.mp3"
};

RPG::RPG(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Weapon(weaponConfig, player, world, window) {
}

RPG::RPG(Enemy* enemy, PhysicsWorld* world, RenderWindow* window)
	: Weapon(weaponConfig, enemy, world, window) {
}

void RPG::shoot() {
	if (status.ammoLeft <= 0) {
		status.ammoLeft = 0;
		status.load = true;
		return;
	}
	--status.ammoLeft;

	Rocket* bullet = m_world->createBody<Rocket>(5, 1000, m_world);
	bullet->player = m_player;

	float finalRotation = Random::getReal<float>(-0.1, 0.1) + rotation;
	bullet->direction = vec2(cos(-finalRotation), sin(-finalRotation));

	bullet->rotation = finalRotation;
	bullet->damage = 1000;
	bullet->knockback = 1000;
	bullet->blastRadius = 500;

	bullet->position = getWorldPivotPoint();
	bullet->initialPosition = bullet->position;

	if (m_player) {
		bullet->type = Projectile::FROM_PLAYER;
	}
	else {
		bullet->type = Projectile::FROM_ENEMY;
	}
}