#include "Render/Texture.hpp"

std::unordered_map<std::string, ALLEGRO_BITMAP*> Texture::s_textureMap;

Texture::Texture()
	: m_size(0), m_texture(nullptr) {
}

Texture::Texture(const vec2& size)
	: m_size(size), m_texture(al_create_bitmap(size.x, size.y)) {

}

Texture::Texture(ALLEGRO_BITMAP* data) 
	: m_size(al_get_bitmap_width(data), al_get_bitmap_height(data)), m_texture(data) {
}

Texture::Texture(const std::string& filename) {
	if (!s_textureMap.count(filename)) {
		s_textureMap[filename] = al_load_bitmap(filename.c_str());
	}
	m_texture = s_textureMap[filename];
	if (m_texture == nullptr) {
		Logger::Log<Error>("Cannot load file: ", filename);
		m_texture = 0;
		m_size = vec2(0);
		return;
	}
	m_size = vec2(
		al_get_bitmap_width(m_texture),
		al_get_bitmap_height(m_texture)
	);
}

Texture::~Texture() {

}

Texture::Texture(const Texture& texture) 
	: m_texture(texture.getBitmap()), m_size(texture.size()) {

}

Texture::Texture(Texture&& texture)
	: m_texture(texture.getBitmap()), m_size(texture.size()) {

}

void Texture::operator=(const Texture& texture) {
	m_texture = texture.getBitmap();
	m_size = texture.size();
}

const vec2& Texture::size() const {
	return m_size;
}

ALLEGRO_BITMAP* Texture::getBitmap() const {
	return m_texture;
}

void Texture::load(const std::string& filename) {
	if (!s_textureMap.count(filename)) {
		s_textureMap[filename] = al_load_bitmap(filename.c_str());
	}
	m_texture = s_textureMap[filename];

	if (m_texture == nullptr) {
		Logger::Log<Error>("Cannot load file: ", filename);
		m_texture = 0;
		m_size = vec2(0);
		return;
	}
	m_size = vec2(
		al_get_bitmap_width(m_texture),
		al_get_bitmap_height(m_texture)
	);
}

bool Texture::empty() const {
	return m_texture == nullptr;
}

void Texture::cleanup() {
	for (auto [name, texture] : s_textureMap) {
		al_destroy_bitmap(texture);
	}
}
