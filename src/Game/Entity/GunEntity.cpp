#include "Game/Entity/GunEntity.hpp"

GunEntity::GunEntity(Player* player, const std::string& name, const Texture& texture, float scale)
	: Entity(RigidBody::GunEntityType, AABB{texture.size() * scale * -0.5, texture.size() * scale * 0.5 })
	, m_font("assets/Minecraft.ttf")
	, m_hint(&m_font)
	, m_scale(scale)
	, m_player(player)
	, m_texture(texture) {
	m_hint.string = "Press G to obtain " + name;
	m_hint.size = 40;
	m_hint.absolutePosition = false;
}

void GunEntity::draw(RenderWindow& window) {
	float y = std::sinf(m_rotation) * 25.0f * m_scale;
	m_hint.position = position - vec2(0, y + m_texture.size().y * 0.65);

	bool inOpenDistance = distance(player->position, position) < 100.0f;

	if (inOpenDistance) {
		window.draw(m_hint);
	}

	Rectangle rect(aabb.size());
	rect.position = position - vec2(0, y);
	
	window.draw(rect, &m_texture);
}

void GunEntity::update(float dt) {
	m_rotation += dt * 2.5;
	m_rotation = std::fmodf(m_rotation, PI_TWO);

	bool inOpenDistance = distance(player->position, position) < 100.0f;

	if (inOpenDistance && Keyboard::get(Keyboard::KEY_G).keydown) {
		alive = 0;
	}

}
