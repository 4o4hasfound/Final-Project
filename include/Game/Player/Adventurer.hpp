#pragma once

#include "Game/Player/Player.hpp"

#include "Game/Weapon/Rifle.hpp"
#include "Game/Weapon/Shotgun.hpp"
#include "Game/Weapon/RPG.hpp"
#include "Game/Weapon/Glock.hpp"

class Adventurer : public Player {
public:
	Adventurer(PhysicsWorld* world, RenderWindow* window);
	~Adventurer() = default;

	virtual void draw(RenderWindow& window) const override;

protected:
	virtual void myUpdate(float dt) override;
	void fistAttack(float dt);

	void drawUI(RenderWindow& window) const;

	std::vector<std::unique_ptr<Weapon>> m_weapons;
	Audio m_audio{ "assets/grassSound.mp3" };

	Animation m_crouchAnimation{ {
		Texture{"assets/Adventurer/adventurer-crouch-walk-00.png"},
		Texture{"assets/Adventurer/adventurer-crouch-walk-01.png"},
		Texture{"assets/Adventurer/adventurer-crouch-walk-02.png"},
		Texture{"assets/Adventurer/adventurer-crouch-walk-03.png"},
		Texture{"assets/Adventurer/adventurer-crouch-walk-04.png"},
		Texture{"assets/Adventurer/adventurer-crouch-walk-05.png"},
	},  1.0 / 6 };
	Animation m_walkAnimation{ {
		Texture{"assets/Adventurer/adventurer-walk-00.png"},
		Texture{"assets/Adventurer/adventurer-walk-01.png"},
		Texture{"assets/Adventurer/adventurer-walk-02.png"},
		Texture{"assets/Adventurer/adventurer-walk-03.png"},
		Texture{"assets/Adventurer/adventurer-walk-04.png"},
		Texture{"assets/Adventurer/adventurer-walk-05.png"},
	},  1.0 / 7.5 };
	Animation m_runAnimation{ {
		Texture{"assets/Adventurer/adventurer-run2-00.png"},
		Texture{"assets/Adventurer/adventurer-run2-01.png"},
		Texture{"assets/Adventurer/adventurer-run2-02.png"},
		Texture{"assets/Adventurer/adventurer-run2-03.png"},
		Texture{"assets/Adventurer/adventurer-run2-04.png"},
		Texture{"assets/Adventurer/adventurer-run2-05.png"},
	},  1.0 / 10 };
	Animation m_idleAnimation{ {
		Texture{"assets/Adventurer/adventurer-idle-00.png"},
		Texture{"assets/Adventurer/adventurer-idle-01.png"},
		Texture{"assets/Adventurer/adventurer-idle-02.png"},
	},  1.0 / 5 };
	Animation m_knockDownAnimation{ {
		Texture{"assets/Adventurer/adventurer-knock-dwn-00.png"},
		Texture{"assets/Adventurer/adventurer-knock-dwn-01.png"},
		Texture{"assets/Adventurer/adventurer-knock-dwn-02.png"},
		Texture{"assets/Adventurer/adventurer-knock-dwn-03.png"},
		Texture{"assets/Adventurer/adventurer-knock-dwn-04.png"},
		Texture{"assets/Adventurer/adventurer-knock-dwn-05.png"},
		Texture{"assets/Adventurer/adventurer-knock-dwn-06.png"},
	},  1.0 / 10 };
	Animation m_getUpAnimation{ {
		Texture{"assets/Adventurer/adventurer-get-up-00.png"},
		Texture{"assets/Adventurer/adventurer-get-up-01.png"},
		Texture{"assets/Adventurer/adventurer-get-up-02.png"},
		Texture{"assets/Adventurer/adventurer-get-up-03.png"},
		Texture{"assets/Adventurer/adventurer-get-up-04.png"},
		Texture{"assets/Adventurer/adventurer-get-up-05.png"},
		Texture{"assets/Adventurer/adventurer-get-up-06.png"},
	},  1.0 / 10 };
	Animation m_punchAnimation{ {
			Texture{"assets/Adventurer/adventurer-punch-00.png"},
			Texture{"assets/Adventurer/adventurer-punch-01.png"},
			Texture{"assets/Adventurer/adventurer-punch-02.png"},
			Texture{"assets/Adventurer/adventurer-punch-03.png"},
			Texture{"assets/Adventurer/adventurer-punch-04.png"},
			Texture{"assets/Adventurer/adventurer-punch-05.png"},
			Texture{"assets/Adventurer/adventurer-punch-06.png"},
			Texture{"assets/Adventurer/adventurer-punch-07.png"},
			Texture{"assets/Adventurer/adventurer-punch-08.png"},
			Texture{"assets/Adventurer/adventurer-punch-09.png"},
			Texture{"assets/Adventurer/adventurer-punch-10.png"},
			Texture{"assets/Adventurer/adventurer-punch-11.png"},
			Texture{"assets/Adventurer/adventurer-punch-12.png"},
	}, 1.0 / 10 };
	Animation m_runPunchAnimation{ {
		Texture{"assets/Adventurer/adventurer-run-punch-00.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-01.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-02.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-03.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-04.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-05.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-06.png"},
	},  1.0 / 10 };
	Animation m_kickAnimation{ {
		Texture{"assets/Adventurer/adventurer-run-punch-00.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-01.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-02.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-03.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-04.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-05.png"},
		Texture{"assets/Adventurer/adventurer-run-punch-06.png"},
	},  1.0 / 10 };
};