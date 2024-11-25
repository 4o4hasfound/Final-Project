#pragma once
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include "Math/Vector.hpp"

#include "Render/Texture.hpp"
#include "Render/Drawable.hpp"
#include "Render/RenderWindow.hpp"

#include "Math/Vector.hpp"

class Rectangle : public Drawable {
public:
	Rectangle(const vec2& _size = vec2(0));
	
	virtual void draw(Texture* texture = nullptr) override;

	vec2 size = vec2(0);
	vec2 position = vec2(0);
	float rotation = 0.0f;
	vec4 color = vec4(0, 0, 0, 255);

	float outlineThickness = 0.0f;
	vec4 outlineColor = vec4(0, 0, 0, 255);
};

class Circle : public Drawable {
public:
	Circle(float _radius = 0.0f);

	virtual void draw(Texture* texture = nullptr) override;

	float radius = 0.0f;
	vec2 position = vec2(0);
	vec4 color = vec4(0, 0, 0, 255);

	float outlineThickness = 0.0f;
	vec4 outlineColor = vec4(0, 0, 0, 255);
};