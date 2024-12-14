#include "Game/Player/Adventurer.hpp"

static PlayerConfig playerConfig{
	3000.0,
	20.0,
	400.0,

	3.0,
	vec2{ 50.0f, 37.0f },
	vec2{ 23.0f, 21.0f },
	AABB{
		{13, 6},
		{33, 36}
	} - vec2{ 23.0f, 21.0f }
};

Adventurer::Adventurer(PhysicsWorld* world, RenderWindow* window)
	: Player(playerConfig, world, window) {
	status.health = config.health;
	status.weapon = new Glock(this, world, window);
}

void Adventurer::draw(RenderWindow& window) const {
	Rectangle rect(config.size * config.scale);
	vec2 delta;
	if (status.direction == 1) {
		delta = config.center * config.scale;
	}
	else {
		delta = vec2(config.size.x - config.center.x, config.center.y) * config.scale;
	}
	rect.position = position + rect.size * 0.5 - delta;
	rect.outlineColor = vec4(255, 0, 0, 255);
	rect.outlineThickness = 5.0f;
	if (status.direction == 1) {
		rect.flip.x = 0;
	}
	else {
		rect.flip.x = 1;
	}

	if (status.punching) {
		window.draw(rect, m_punchAnimation.getFrame());
	}
	else if (status.runPunching) {
		window.draw(rect, m_runPunchAnimation.getFrame());
	}
	else if (status.crouching) {
		window.draw(rect, m_crouchAnimation.getFrame());
	}
	else if (status.walking) {
		window.draw(rect, m_walkAnimation.getFrame());
	}
	else if (status.running) {
		window.draw(rect, m_runAnimation.getFrame());
	}
	else {
		window.draw(rect, m_idleAnimation.getFrame());
	}

	if (status.weapon) {
		if (status.weapon->status.holding) {
			status.weapon->draw(window);
		}

		Font font("assets/Minecraft.ttf");
		Text text(&font);

		text.string = std::to_string(status.weapon->status.ammoLeft);
		text.position = vec2(1400, 800);
		text.size = 40;

		if (status.weapon->status.ammoLeft > status.weapon->config.ammo * 0.5) {
			text.color = vec4(255, 255, 255, 255);
		}
		else {
			text.color = vec4(255, 0, 0, 255);
		}

		window.draw(text);

		text.string = " / " + std::to_string(status.weapon->config.ammo);
		text.position = vec2(1500, 800);
		text.color = vec4(255, 255, 255, 255);

		window.draw(text);
	}
	for (Skill* skill : status.skills) {
		skill->render(window);
	}
}

void Adventurer::changeWeapon(const std::string& name) {
	if (status.weapon) {
		delete status.weapon;
	}
	if (name == "Glock") {
		status.weapon = new Glock(this, m_world, m_window);
	}
	else if (name == "Rifle") {
		status.weapon = new Rifle(this, m_world, m_window);
	}
	else if (name == "Shotgun") {
		status.weapon = new Shotgun(this, m_world, m_window);
	}
	else if (name == "RPG") {
		status.weapon = new RPG(this, m_world, m_window);
	}
}

void Adventurer::myUpdate(float dt) {
	PlayerStatus lastStatus = status;

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

	if (Mouse::getScroll() != 0) {
		status.weaponIndex = status.weaponIndex ? 0 : 1;
	}
	status.weapon->status.holding = status.weaponIndex;

	status.crouching = Keyboard::get(Keyboard::KEY_LSHIFT).pressed;
	status.running = walking && status.weaponIndex == 0 && Keyboard::get(Keyboard::KEY_LCTRL).pressed;
	status.walking = walking && !status.crouching && !status.running;

	fistAttack(dt);

	if (status.crouching) {
		status.pivot = vec2(19, 29);
	}
	else {
		status.pivot = vec2(19, 24);
	}

	// Normalize velocity vector
	if (velocity.x || velocity.y) {
		if (status.crouching) {
			velocity = normalize(velocity) * config.speed * 0.25;
		}
		else if (status.walking) {
			velocity = normalize(velocity) * config.speed * 0.5;
		}
		else if (status.running) {
			velocity = normalize(velocity) * config.speed;
		}
	}
	if (!walking) {
		velocity = vec2(0);
	}

	// Handle audio
	if (!walking || status.crouching) {
		m_audio.stop();
	}
	else {
		if (status.walking && !lastStatus.walking) {
			m_audio.stop();
		}
		if (status.running && !lastStatus.running) {
			m_audio.stop();
		}
		if (!m_audio.playing()) {
			// Speed up a little bit
			if (status.walking) {
				m_audio.play(1.3 * 0.75, 10.0);
			}
			else if (status.running) {
				m_audio.play(1.3, 10.0);
			}
		}
	}

	// Handle animation changes
	if (!walking && status.moving) {
		m_walkAnimation.reset();
		m_crouchAnimation.reset();
		m_runAnimation.reset();
		m_idleAnimation.reset();
		m_idleAnimation.advance();
	}

	if (status.running && !lastStatus.running) {
		m_crouchAnimation.reset();
		m_walkAnimation.reset();
	}
	if (status.crouching && !lastStatus.crouching) {
		m_runAnimation.reset();
		m_walkAnimation.reset();
	}
	if (status.walking && !lastStatus.walking) {
		m_crouchAnimation.reset();
		m_runAnimation.reset();
	}

	if (walking && status.running) {
		m_runAnimation.update(dt, true);
	}
	else if (walking && status.crouching) {
		m_crouchAnimation.update(dt, true);
	}
	else if (walking && status.walking) {
		m_walkAnimation.update(dt, true);
	}
	else {
		m_idleAnimation.update(dt, true);
	}

	if (status.weapon && status.weapon->status.holding) {
		status.weapon->update(dt);
	}

	status.moving = walking;
}

void Adventurer::fistAttack(float dt) {
	if (status.weaponIndex != 0) {
		status.punching = 0;
		status.runPunching = 0;
		m_punchAnimation.reset();
		m_runPunchAnimation.reset();
		return;
	}
	if ((status.moving && status.walking) || !status.moving) {
		if (Mouse::get(Mouse::LEFT).pressed) {
			status.punching = 1;
		}
	}
	else if (status.moving && status.running) {
		if (Mouse::get(Mouse::LEFT).pressed) {
			status.runPunching = 1;
		}
	}
	if (m_punchAnimation.update(dt, true)) {
		status.punching = 0;
	}
	if (m_runPunchAnimation.update(dt, true)) {
		status.runPunching = 0;
	}
}