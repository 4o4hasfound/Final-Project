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
	RenderWindow();
	RenderWindow(int width, int height, const std::string& windowName);
	RenderWindow(const vec2& size, const std::string& windowName);
	RenderWindow(const std::string& windowName);
	~RenderWindow();

	// Clears the screen display
	void clear(const vec3& color);
	void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f);

	// Draw a drawable object
	void draw(Drawable& target, const Texture* texture = nullptr) const;

	// Returns the size of the screen
	const vec2& size() const;
	
	void setTitle(const std::string& title);

	// poll events
	void pollEvents();
	void pollEvents(std::vector<ALLEGRO_EVENT>& events);

	ALLEGRO_DISPLAY* getDisplay() const;

	// Called at the very end of the rendering loop
	void flipDisplay() const;

	// Returns true if the window is still running
	bool running() const;

	ViewPort viewport;
private:
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_EVENT_QUEUE* m_eventQueue;
	vec2 m_size;
	bool m_running = true;

	void setupWindow();
};