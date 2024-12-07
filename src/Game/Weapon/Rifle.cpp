#include "Game/Weapon/Rifle.hpp"
//struct WeaponConfig {
//	float attack;
//	int ammo;
//	float shootInterval;
//
//	float scale = 1.0;
//	vec2 size;
//	vec2 center;
//	vec2 muzzlePosition;
//	vec2 gripPosition;
//
//	std::string shootAnimationFilename;
//	vec2 shootAnimationSize;
//	std::vector<vec2> shootAnimationIndexes;
//	float shootAnimationDuration;
//
//	std::string loadAnimationFilename;
//	vec2 loadAnimationSize;
//	std::vector<vec2> loadAnimationIndexes;
//	float loadAnimationDuration;
//};
static WeaponConfig weaponConfig{
	10.0,
	30.0,
	0.4,
	0.05,

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
	0.0125,
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

void Rifle::shoot() {
	if (status.ammoLeft <= 0) {
		status.ammoLeft = 0;
	}
	--status.ammoLeft;

	Bullet* bullet = m_world->createBody<Bullet>(40, 3);

	float rotateOffset;
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
	float finalRotation = rotation + rotateOffset;
	bullet->direction = vec2(cos(-finalRotation), sin(-finalRotation));
	bullet->rotation = finalRotation;
	bullet->damage = 100;
	bullet->knockback = 250;
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

void Rifle::myUpdate(float dt) {
	if (Mouse::get(Mouse::LEFT).pressed) {
		status.shoot = true;
	}
	else {
		status.shoot = false;
	}

	if (Mouse::get(Mouse::RIGHT).pressed) {
		status.load = true;
	}
}
