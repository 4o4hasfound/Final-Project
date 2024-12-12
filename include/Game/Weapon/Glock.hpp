#pragma once

#include "Engine/Keyboard.hpp"
#include "Engine/Mouse.hpp"

#include "Game/Weapon/Weapon.hpp"
#include "Game/Player/Player.hpp"
#include "Game/Projectile/Bullet.hpp"
#include "Game/Projectile/Rocket.hpp"

#include "Render/Shape.hpp"
#include "Render/Texture.hpp"
#include "Render/Animation.hpp"
#include "Render/Tileset.hpp"

#include "Math/Vector.hpp"
#include "Math/Functions.hpp"

class Glock : public Weapon {
public:
	Glock(Player* player, PhysicsWorld* world, RenderWindow* window);
	Glock(Enemy* enemy, PhysicsWorld* world, RenderWindow* window);
	~Glock() = default;

private:
	virtual void shoot() override;
	//virtual void myUpdate(float dt) override;
};