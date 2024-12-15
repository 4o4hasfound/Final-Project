#pragma once

#include <string>
#include <unordered_map>

#include <allegro5/allegro_font.h>

#include "Render/Font.hpp"
#include "Render/Drawable.hpp"
#include "Render/RenderWindow.hpp"

#include "Math/Vector.hpp"

class Text : public Drawable {
	friend class RenderWindow;
public:
	enum TextAlign {
		Left = ALLEGRO_ALIGN_LEFT,
		Center = ALLEGRO_ALIGN_CENTER,
		Right = ALLEGRO_ALIGN_RIGHT
	};
	Text(Font* font);
	Text(Font* font, const std::string& _string);

	void setFont(Font* font);
	Font* getFont();

	virtual void draw(const Texture* texture = nullptr) override;

	std::string string;
	vec2 position = vec2(0);
	vec4 color = vec4(255);
	float height = 0;
	int size;
	TextAlign align = Center;
private:
	Font* m_font;

	// Draw to screen while accounting the viewport of the window
	virtual void draw(const RenderWindow* window, const Texture* texture = nullptr) override;
};