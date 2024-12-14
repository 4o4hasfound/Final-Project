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
		position.y - al_get_font_ascent(alFont) * 0.5,
		1000,
		height,
		ALLEGRO_ALIGN_LEFT,
		string.c_str()
	);
}

void Text::draw(const RenderWindow* window, const Texture* texture) {
	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	if (window && !absolutePosition) {
		al_translate_transform(
			&trans,
			std::round(-window->viewport.position.x),
			std::round(-window->viewport.position.y)
		);
		al_scale_transform(
			&trans,
			(window->size() / window->viewport.size).x,
			(window->size() / window->viewport.size).y
		);
	}
	al_use_transform(&trans);
	ALLEGRO_FONT* alFont = m_font->getFont(size);

	al_draw_multiline_text(
		alFont,
		al_map_rgba(color.r, color.g, color.b, color.a),
		position.x,
		position.y - al_get_font_ascent(alFont) * 0.5,
		1000,
		height,
		ALLEGRO_ALIGN_CENTER,
		string.c_str()
	);
}
