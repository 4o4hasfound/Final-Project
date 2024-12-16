#include "Game/Weapon/Rifle.hpp"

static WeaponConfig weaponConfig{
	300.0,
	500.0,
	30,
	30,
	0.4,
	0.1,

	1.3,
	vec2{96, 48},
	vec2{47.5, 29.5},

	"assets/Guns/AK47/shoot.png",
	std::vector<vec2>{
		{0, 0}, 
		{0, 1}, 
		{0, 2}, 
		{0, 3}
	},
	0.05,
	"assets/Guns/AK47/shootSound.mp3",

	"assets/Guns/AK47/load.png",
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
		{0, 16},
		{0, 17},
		{0, 18},
		{0, 19},
		{0, 20},
		{0, 21},
		{0, 22},
		{0, 23},
		{0, 24},
		{0, 25},
		{0, 26},
		{0, 27},
	},
	0.1,
	"assets/Guns/AK47/loadSound.wav"
};

Rifle::Rifle(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Weapon(weaponConfig, player, world, window) {

}

Rifle::Rifle(Enemy* enemy, PhysicsWorld* world, RenderWindow* window)
	: Weapon(weaponConfig, enemy, world, window) {

}


void Rifle::shoot() {
	if (status.ammoLeft <= 0) {
		status.ammoLeft = 0;
		status.load = true;
		return;
	}
	--status.ammoLeft;

	Bullet* bullet = m_world->createBody<Bullet>(40, 1500, 3, m_world);
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
	bullet->damage = config.attack;
	bullet->knockback = config.knockback;

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