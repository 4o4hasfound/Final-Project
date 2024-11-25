#pragma once
#include <string>
#include <functional>

#include <allegro5/display.h>
#include <allegro5/allegro_color.h>

#include "Render/Drawable.hpp"
#include "Render/ViewPort.hpp"

#include "Debug/Log.hpp"

class RenderWindow {
public:
	RenderWindow(int width, int height, const std::string& windowName);
	RenderWindow(const vec2& size, const std::string& windowName);
	RenderWindow(const std::string& windowName);
	~RenderWindow();

	void clear(const vec3& color);
	void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f);

	ALLEGRO_DISPLAY* getDisplay() const;

	void flipDisplay() const;

	bool running() const;

	ViewPort viewport;
private:
	ALLEGRO_DISPLAY* m_display;
	vec2 m_size;
	bool m_running = true;
};