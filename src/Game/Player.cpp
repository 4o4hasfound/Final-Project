#include "Game/Player.hpp"

Player::Player(const AABB& aabb)
	: RigidBody(RigidBody::Character, aabb)
	, m_audio("assets/grassSound.mp3")
	, m_walkset("assets/walk.png", vec2(32))
	, m_walkAnimation({ m_walkset[2][0], m_walkset[2][1], m_walkset[2][2], m_walkset[2][3] }, 1.0 / 8)
	, m_idleAnimation({ m_walkset[1][0], m_walkset[1][1] }, 1.0 / 3) {
}

void Player::draw(RenderWindow& window) {
	Rectangle middle(vec2(96, 96));
	middle.position = position;
	middle.outlineColor = vec4(255, 0, 0, 255);
	middle.outlineThickness = 5.0f;
	if (status.direction == 1) {
		middle.flip.x = 0;
	}
	else {
		middle.flip.x = 1;
	}
	if (status.moving) {
		window.draw(middle, m_walkAnimation.getFrame());
	}
	else {
		window.draw(middle, m_idleAnimation.getFrame());
	}
	//getAABB().DebugDraw(window);
}

void Player::myUpdate(float dt) {
	bool walking = false;

	// Keyboard inputs
	if (Keyboard::get(Keyboard::KEY_W).pressed) {
		velocity.y = -1;
		walking = true;
	}
	else if (Keyboard::get(Keyboard::KEY_S).pressed) {
		velocity.y = 1;
		walking = true;
	}
	else {
		velocity.y = 0;
	}
	if (Keyboard::get(Keyboard::KEY_A).pressed) {
		velocity.x = -1;
		status.direction = -1;
		walking = true;
	}
	else if (Keyboard::get(Keyboard::KEY_D).pressed) {
		velocity.x = 1;
		status.direction = 1;
		walking = true;
	}
	else {
		velocity.x = 0;
	}

	// Normalize velocity vector
	if (velocity.x || velocity.y) {
		velocity = normalize(velocity) * 400;
	}

	// Handle audio
	if (!walking) {
		velocity = vec2(0);
		m_audio.stop();
	}
	else {
		if (!m_audio.playing()) {
			// Speed up a little bit
			m_audio.play(1.3);
		}
	}

	// Handle animation changes
	if (!walking && status.moving) {
		m_walkAnimation.reset();
		m_idleAnimation.reset();
		m_idleAnimation.advance();
	}

	if (walking) {
		m_walkAnimation.update(dt, true);
	}
	else {
		m_idleAnimation.update(dt, true);
	}

	status.moving = walking;
}
