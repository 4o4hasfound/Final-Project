#pragma once

#include "Engine/Keyboard.hpp"
#include "Engine/Mouse.hpp"

#include "Game/Weapon/Weapon.hpp"
#include "Game/Player/Player.hpp"
#include "Game/Projectile/Bullet.hpp"

#include "Render/Shape.hpp"
#include "Render/Texture.hpp"
#include "Render/Animation.hpp"
#include "Render/Tileset.hpp"

#include "Math/Vector.hpp"
#include "Math/Functions.hpp"

class Rifle : public Weapon {
public:
	Rifle(Player* player, PhysicsWorld* world, RenderWindow* window);
	~Rifle() = default;

private:
	Audio m_audio{ "assets/Scar/sound.mp3" };

	virtual void shoot() override;
	virtual void myUpdate(float dt) override;
};