#pragma once

#include "Game/Enemy/Enemy.hpp"

class DroidZapperEnemy : public Enemy {
	friend class EnemyManager;
public:
	DroidZapperEnemy();
	~DroidZapperEnemy() = default;

	virtual void draw(RenderWindow& window) const override;
	virtual void attack(Player* player) override;

protected:
	Animation m_runAnimation;
	Animation m_idleAnimation;
	Animation m_atkAnimation;

	virtual void myUpdate(float dt) override;
};