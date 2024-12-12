#include "Game/Weapon/Glock.hpp"

static WeaponConfig weaponConfig{
	10.0,
	12,
	12,
	0.4,
	0.5,

	1.3,
	vec2{64, 48},
	vec2{32.5, 29.5},

	"assets/Guns/Glock/shoot.png",
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
	},
	0.04,
	"assets/Guns/Glock/shootSound.mp3",

	"assets/Guns/Glock/load.png",
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
		{0, 15},
		{0, 14},
		{0, 13},
		{0, 12},
		{0, 11},
		{0, 10},
		{0, 9},
		{0, 8},
		{0, 7},
		{0, 6},
		{0, 5},
		{0, 4},
		{0, 3},
		{0, 2},
		{0, 1},
		{0, 0},
	},
	0.05,
	"assets/Guns/Glock/loadSound.mp3"
};

Glock::Glock(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Weapon(weaponConfig, player, world, window) {

}

Glock::Glock(Enemy* enemy, PhysicsWorld* world, RenderWindow* window)
	: Weapon(weaponConfig, enemy, world, window) {

}


void Glock::shoot() {
	if (status.ammoLeft <= 0) {
		status.ammoLeft = 0;
		status.load = true;
		return;
	}
	--status.ammoLeft;

	Bullet* bullet = m_world->createBody<Bullet>(40, 1500, 3);
	bullet->player = m_player;

	float rotateOffset;
	if (m_player) {
		if (m_player->status.walking) {
			rotateOffset = Random::getReal<float>(-0.2, 0.2);
		}
		else if (m_player->status.crouching && m_player->status.moving) {
			rotateOffset = Random::getReal<float>(-0.08, 0.08);
		}
		else if (!m_player->status.crouching && !m_player->status.moving) {
			rotateOffset = Random::getReal<float>(-0.075, 0.075);
		}
		else if (m_player->status.crouching && !m_player->status.moving) {
			rotateOffset = Random::getReal<float>(-0.05, 0.05);
		}
		else {
			rotateOffset = Random::getReal<float>(-0.08, 0.08);
		}
	}
	else {
		rotateOffset = Random::getReal<float>(-0.3, 0.3);
	}
	float finalRotation = rotation + rotateOffset;
	bullet->direction = vec2(cos(-finalRotation), sin(-finalRotation));
	bullet->rotation = finalRotation;
	bullet->damage = 200;
	bullet->knockback = 500;

	if (m_player) {
		bullet->type = Projectile::FROM_PLAYER;
	}
	else {
		bullet->type = Projectile::FROM_ENEMY;
	}
	//bullet->color = {
	//	Random::getInt(0, 255),
	//	Random::getInt(0, 255),
	//	Random::getInt(0, 255)
	//};

	bullet->position = getWorldPivotPoint();
	//bullet->position += vec2(sin(rotation), cos(rotation)) * 30;
	//bullet->position += bullet->direction * bullet->speed * 0.25;

	bullet->initialPosition = bullet->position;
}