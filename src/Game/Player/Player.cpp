#include "Game/Player/Player.hpp"

Player::Player(const PlayerConfig& _config)
	: RigidBody(RigidBody::CharacterType, {_config.aabb * _config.scale})
	, config(_config){

}

void Player::update(float dt) {
	myUpdate(dt);
	position += velocity * dt;
	status.maxExp = 5 * status.level;

	for (Skill* skill : status.skills) {
		skill->update();
	}
}

void Player::draw(RenderWindow& window) const {
	for (Skill* skill : status.skills) {
		skill->render();
	}
}

void Player::myUpdate(float dt) {

}

bool Player::hit(float damage, const vec2& knockback) {
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
	if (status.exp > 10) {
		status.exp = 0;
		++status.level;
		status.levelUp = 1;
	}
}
