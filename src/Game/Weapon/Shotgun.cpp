#include "Game/Weapon/Shotgun.hpp"

static WeaponConfig weaponConfig{
	100.0,
	1000.0,
	5,
	1,
	0.4,
	1.0,

	2.0,
	vec2{160, 32},
	vec2{51.0, 21.0},

	"assets/Guns/Shotgun/shoot.png",
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
	},
	0.05,
	"assets/Guns/Shotgun/shootSound.mp3",

	"assets/Guns/Shotgun/load.png",
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
	},
	0.075,
	"assets/Guns/Shotgun/loadSound.mp3"
};

Shotgun::Shotgun(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Weapon(weaponConfig, player, world, window) {

}

Shotgun::Shotgun(Enemy* enemy, PhysicsWorld* world, RenderWindow* window)
	: Weapon(weaponConfig, enemy, world, window) {

}
void Shotgun::shoot() {
	if (status.ammoLeft <= 0) {
		status.ammoLeft = 0;
		if (!m_shootAnimation.playing()) {
			status.load = true;
		}
		return;
	}
	--status.ammoLeft;
	for (int i = 0; i < 20; ++i) {
		Bullet* bullet = m_world->createBody<Bullet>(40, Random::getInt<int>(500, 700), 4, m_world);
		bullet->player = m_player;

		float rotateOffset = Random::getReal<float>(-0.4, 0.4);
		float finalRotation = rotation + rotateOffset;
		bullet->direction = vec2(cos(-finalRotation), sin(-finalRotation));
		bullet->rotation = finalRotation;
		bullet->damage = config.attack;
		bullet->knockback = config.knockback;
		//bullet->color = {
		//	Random::getInt(0, 255),
		//	Random::getInt(0, 255),
		//	Random::getInt(0, 255)
		//};

		bullet->position = getWorldPivotPoint();
		//bullet->position += vec2(sin(rotation), cos(rotation)) * 30;
		//bullet->position += bullet->direction * bullet->speed * 0.25;

		bullet->initialPosition = bullet->position;

		if (m_player) {
			bullet->type = Projectile::FROM_PLAYER;
		}
		else {
			bullet->type = Projectile::FROM_ENEMY;
		}
	}

}