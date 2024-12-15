#include "Render/Font.hpp"

Font::Font() {

}

Font::Font(const std::string& file)
	: m_fontfile(file) {

}

Font::~Font() {
	for (auto& [size, font] : m_fonts) {
		al_destroy_font(font);
	}
}

void Font::load(const std::string& file) {
	m_fontfile = file;
}

ALLEGRO_FONT* Font::getFont(int size) {
	if (!m_fonts.count(size)) {
		ALLEGRO_FONT* font = al_load_font(m_fontfile.c_str(), size, 0);
		if (!font) {
			Logger::Log<Debug>("Failed to load font file", m_fontfile, "with size", size);
			return nullptr;
		}
		m_fonts[size] = font;
	}
	return m_fonts[size];
}
