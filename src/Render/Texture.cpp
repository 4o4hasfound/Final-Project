#include "Render/Texture.hpp"

Texture::Texture()
	: m_size(0), m_texture(nullptr) {
}

Texture::Texture(const vec2& size)
	: m_size(size), m_texture(al_create_bitmap(size.x, size.y)) {
}

Texture::Texture(ALLEGRO_BITMAP* data) 
	: m_size(al_get_bitmap_width(data), al_get_bitmap_height(data)), m_texture(data) {
}

Texture::Texture(const std::string& filename)
	: m_texture(al_load_bitmap(filename.c_str())) {
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
	if (m_texture != nullptr) {
		al_destroy_bitmap(m_texture);
	}
}

Texture::Texture(const Texture& texture) 
	: m_texture(al_clone_bitmap(texture.getBitmap())), m_size(texture.getSize()) {

}

Texture::Texture(Texture&& texture)
	: m_texture(texture.getBitmap()), m_size(texture.getSize()) {

}

void Texture::operator=(const Texture& texture) {
	if (m_texture != nullptr) {
		al_destroy_bitmap(m_texture);
	}
	m_texture = al_clone_bitmap(texture.getBitmap());
	m_size = texture.getSize();
}

const vec2& Texture::getSize() const {
	return m_size;
}

ALLEGRO_BITMAP* Texture::getBitmap() const {
	return m_texture;
}

void Texture::load(const std::string& filename) {
	if (m_texture != nullptr) {
		al_destroy_bitmap(m_texture);
	}

	m_texture = al_load_bitmap(filename.c_str());
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
