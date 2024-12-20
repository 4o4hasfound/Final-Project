#include "Game/Entity/ChestEntity.hpp"

static vec2 chestSize{ 48, 32 };
static float scale = 2.0f;

ChestEntity::ChestEntity(PhysicsWorld* world, RenderWindow* window)
	: Entity(RigidBody::ChestType, AABB{chestSize * scale * -0.5, chestSize * scale * 0.5} * 0.9)
	, m_world(world)
	, m_window(window)
	, m_tileset("assets/Entity/chest.png", chestSize)
	, m_openAnimation(
		{
			m_tileset[1][0],
			m_tileset[1][1],
			m_tileset[1][2],
			m_tileset[1][3],
			m_tileset[1][4],
		},
		0.2)
	, m_idleAnimation(
		{
			m_tileset[0][0],
			m_tileset[0][1],
			m_tileset[0][2],
			m_tileset[0][3],
			m_tileset[0][4],
		},
		0.1)
	, m_font("assets/Minecraft.ttf")
	, m_hint(&m_font) {
	m_hint.string = "Press F to open chest";
	m_hint.size = 40;
	m_hint.absolutePosition = false;

	float value = Random::getReal<float>(0, 1);
	if (value <= 0.01) {
		m_weaponID = ChestEntityRPG;
	}
	else if (value <= 0.5) {
		m_weaponID = ChestEntityShotgun;
	}
	else if (value <= 1.0) {
		m_weaponID = ChestEntityRifle;
	}
	else {
		m_weaponID = ChestEntityGlock;
	}
}

ChestEntity::ChestEntity(PhysicsWorld* world, RenderWindow* window, GunEntityType weaponID)
	: Entity(RigidBody::ChestType, AABB{ chestSize * scale * -0.5, chestSize * scale * 0.5 } *0.9)
	, m_world(world)
	, m_window(window)
	, m_tileset("assets/Entity/chest.png", chestSize)
	, m_openAnimation(
		{
			m_tileset[1][0],
			m_tileset[1][1],
			m_tileset[1][2],
			m_tileset[1][3],
			m_tileset[1][4],
		},
		0.2)
		, m_idleAnimation(
			{
				m_tileset[0][0],
				m_tileset[0][1],
				m_tileset[0][2],
				m_tileset[0][3],
				m_tileset[0][4],
			},
			0.1)
			, m_font("assets/Minecraft.ttf")
	, m_hint(&m_font)
	, m_weaponID(weaponID) {
	m_hint.string = "Press F to open chest";
	m_hint.size = 40;
	m_hint.absolutePosition = false;
}

void ChestEntity::draw(RenderWindow& window) {
	Rectangle rect(aabb.size());
	rect.position = position;
	m_hint.position = position - vec2(0, chestSize.y * scale * 0.65);
	
	bool inOpenDistance = distance(player->position, position) < 100.0f;

	if (inOpenDistance) {
		window.draw(m_hint);
	}

	if (m_openAnimation.playing()) {
		window.draw(rect, m_openAnimation.getFrame());
	}
	else {
		window.draw(rect, m_idleAnimation.getFrame());
	}
}

void ChestEntity::update(float dt) {
	bool inOpenDistance = distance(player->position, position) < 100.0f;

	if (m_openAnimation.playing() || (inOpenDistance && Keyboard::get(Keyboard::KEY_F).keydown)) {
		if (m_openAnimation.update(dt, false)) {
			alive = 0;
			float value = Random::getReal<float>(0, 1);

			GunEntity* gun;
			if (m_weaponID == ChestEntityRPG) {
				gun = m_world->createBody<GunEntity>(player, "RPG", Texture("assets/Guns/RPG/texture.png"), 1.0, m_world, m_window);
			}
			else if (m_weaponID == ChestEntityShotgun) {
				gun = m_world->createBody<GunEntity>(player, "Shotgun", Texture("assets/Guns/Shotgun/texture.png"), 1.0, m_world, m_window);
			}
			else if (m_weaponID == ChestEntityRifle) {
				gun = m_world->createBody<GunEntity>(player, "Rifle", Texture("assets/Guns/AK47/texture.png"), 1.0, m_world, m_window);
			}
			else {
				gun = m_world->createBody<GunEntity>(player, "Glock", Texture("assets/Guns/Glock/texture.png"), 1.0, m_world, m_window);
			}
			gun->player = player;
			gun->position = position;
		}
	}
	else {
		m_idleAnimation.update(dt, false);
	}
}

void ChestEntity::onCollide(RigidBody* other, const Manifold& detail)  {
	if ((other->getType() & RigidBody::CharacterType) != RigidBody::CharacterType) {
		return;
	}
	//m_open = true;
}
