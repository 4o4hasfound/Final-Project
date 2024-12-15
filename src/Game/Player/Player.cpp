#include "Game/Player/Player.hpp"

Player::Player(const PlayerConfig& _config, PhysicsWorld* world, RenderWindow* window)
	: RigidBody(RigidBody::CharacterType, {_config.aabb * _config.scale})
	, config(_config)
	, m_world(world)
	, m_window(window) {

}

void Player::update(float dt) {
	myUpdate(dt);
	
	float scale = 1.0f;
	if (status.healing) {
		scale *= 0.5f;
	}
	if (status.premiumHealing) {
		scale *= 0.3f;
	}
	position += velocity * dt * scale;
	status.maxExp = 5 * status.level;

	for (Skill* skill : status.skills) {
		skill->update(dt);
	}
}

void Player::draw(RenderWindow& window) const {
	for (Skill* skill : status.skills) {
		skill->render(window);
	}
}

void Player::myUpdate(float dt) {

}

bool Player::hit(float damage, const vec2& knockback) {
	if (status.invincible) {
		return false;
	}
	status.health -= damage;
	status.knockbackCD = 0.1;
	velocity = knockback;
	if (status.health <= 0) {
		status.health = 0;
		return true;
	}

	return false;
}

void Player::addExp(int amount) {
	status.exp += amount;
	if (status.exp > (status.level + 1) * 10) {
		status.exp = 0;
		++status.level;
		status.levelUp = 1;
	}
}

void Player::changeWeapon(const std::string& name) {

}
