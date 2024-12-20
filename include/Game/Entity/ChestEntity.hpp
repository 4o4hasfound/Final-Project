#pragma once

#include "Game/Entity/Entity.hpp"
#include "Game/Entity/GunEntity.hpp"
#include "Game/Player/Player.hpp"

#include "Render/Animation.hpp"
#include "Render/Shape.hpp"
#include "Render/Tileset.hpp"
#include "Render/Font.hpp"
#include "Render/Text.hpp"

#include "Utils/Random.hpp"

class ChestEntity : public Entity {
public:
	enum GunEntityType {
		ChestEntityGlock,
		ChestEntityRifle,
		ChestEntityShotgun,
		ChestEntityRPG
	};
	ChestEntity(PhysicsWorld* world, RenderWindow* window);
	ChestEntity(PhysicsWorld* world, RenderWindow* window, GunEntityType weaponID);
	~ChestEntity() = default;

	virtual void draw(RenderWindow& window) override;

	Player* player;
protected:
	Tileset m_tileset;
	Animation m_idleAnimation;
	Animation m_openAnimation;
	PhysicsWorld* m_world;
	RenderWindow* m_window;
	GunEntityType m_weaponID;

	Font m_font;
	Text m_hint;

	bool m_open = false;

	virtual void update(float dt) override;

	// Callback function when two objects collide
	virtual void onCollide(RigidBody* other, const Manifold& detail) override;
};