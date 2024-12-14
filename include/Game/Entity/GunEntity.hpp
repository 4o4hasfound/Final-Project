#pragma once

#include <string>

#include "Game/Entity/Entity.hpp"
#include "Game/Player/Player.hpp"

class GunEntity : public Entity {
public:
	GunEntity(Player* player, const std::string& name, const Texture& texture, float scale = 1.0f);
	~GunEntity() = default;

	virtual void draw(RenderWindow& window) override;
private:
	Texture m_texture;
	Font m_font;
	Text m_hint;
	Player* m_player;

	float m_rotation = 0;
	float m_scale = 1.0f;

	virtual void update(float dt) override;
};