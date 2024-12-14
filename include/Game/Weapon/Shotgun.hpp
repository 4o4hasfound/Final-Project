#pragma once

#include "Game/Enemy/Enemy.hpp"
#include "Game/Weapon/Weapon.hpp"
#include "Game/Projectile/Bullet.hpp"

class Shotgun : public Weapon {
public:
	Shotgun(Player* player, PhysicsWorld* world, RenderWindow* window);
	Shotgun(Enemy* enemy, PhysicsWorld* world, RenderWindow* window);
	~Shotgun() = default;

private:
	virtual void shoot() override;
};