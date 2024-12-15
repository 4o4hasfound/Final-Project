#pragma once

#include "Game/Enemy/Enemy.hpp"

#include "Game/Weapon/Rifle.hpp"
#include "Game/Weapon/Shotgun.hpp"
#include "Game/Weapon/RPG.hpp"
#include "Game/Weapon/Glock.hpp"

class BlueSoldier : public Enemy {
	friend class EnemyManager;
public:
	BlueSoldier() = default;

	BlueSoldier(PhysicsWorld* world, RenderWindow* window);
	~BlueSoldier();

	virtual void draw(RenderWindow& window) override;
	virtual void attack(Player* player) override;

	Weapon* weapon = nullptr;
protected:
	Animation m_runAnimation;
	Animation m_idleAnimation;
	Animation m_dieAnimation;
	Animation m_leaveAnimation;

	virtual void myUpdate(float dt) override;
};