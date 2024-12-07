#include "Game/Player/Player.hpp"

Player::Player(const PlayerConfig& _config)
	: RigidBody(RigidBody::CharacterType, {_config.aabb * _config.scale})
	, config(_config){

}

void Player::update(float dt) {
	myUpdate(dt);
	position += velocity * dt;
}

void Player::myUpdate(float dt) {

}
