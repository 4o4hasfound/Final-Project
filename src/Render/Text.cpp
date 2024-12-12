#include "Render/Text.hpp"

Text::Text(Font* font)
	: m_font(font) {
	absolutePosition = true;
}

Text::Text(Font* font, const std::string& _string)
	: m_font(font)
	, string(_string) {
	absolutePosition = true;
}


void Text::setFont(Font* font) {
	m_font = font;
}

Font* Text::getFont() {
	return m_font;
}

void Text::draw(const Texture* texture) {
	ALLEGRO_FONT* alFont = m_font->getFont(size);

	al_draw_multiline_text(
		alFont,
		al_map_rgba(color.r, color.g, color.b, color.a),
		position.x,
		position.y,
		1000,
		height,
		ALLEGRO_ALIGN_LEFT,
		string.c_str()
	);
}

void Text::draw(const RenderWindow* window, const Texture* texture) {
	ALLEGRO_FONT* alFont = m_font->getFont(size);

	al_draw_multiline_text(
		alFont,
		al_map_rgba(color.r, color.g, color.b, color.a),
		position.x,
		position.y,
		1000,
		height,
		ALLEGRO_ALIGN_CENTER,
		string.c_str()
	);
}
