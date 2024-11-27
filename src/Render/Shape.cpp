#include "Render/Shape.hpp"
//#include "Render/Shape.hpp"
//Shader Circle::s_shader;
//GLuint Circle::s_vao, Circle::s_vbo, Circle::s_ebo;
//int Circle::s_numSides;
//std::vector<vec4> Circle::s_vertices;
//std::vector<unsigned int> Circle::s_indices;
//bool Circle::s_hasInit = false;
//
//Shader Rectangle::s_shader;
//GLuint Rectangle::s_vao, Rectangle::s_vbo, Rectangle::s_ebo;
//float Rectangle::s_vertices[16] = {
//    // positions     // uvs
//    -0.5f,  0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f,  1.0f, 0.0f,
//    -0.5f, -0.5f,  0.0f, 0.0f,
//     0.5f,  0.5f,  1.0f, 1.0f
//};
//unsigned int Rectangle::s_indices[6] = {
//    0, 1, 2, 0, 1, 3
//};
//bool Rectangle::s_hasInit = false;
//
//Rectangle::Rectangle()
//    : size(0.0), position(0.0), color(1.0), transparency(1.0) {
//    if (s_hasInit) {
//        return;
//    }
//    setupBuffer();
//}
//
//Rectangle::Rectangle(float width, float height)
//    : size(width, height), position(0.0), color(1.0), transparency(1.0) {
//    if (s_hasInit) {
//        return;
//    }
//    setupBuffer();
//}
//
//Rectangle::Rectangle(const vec2& _size)
//	: size(_size), position(0.0), color(1.0), transparency(1.0) {
//    if (s_hasInit) {
//        return;
//    }
//    setupBuffer();
//}
//
//Rectangle::~Rectangle() {
//
//}
//
//void Rectangle::draw(RenderWindow* target, Texture* texture) {
//    glDisable(GL_CULL_FACE);
//
//    s_shader.use();
//    s_shader.setVec2("screenSize", target->getSize());
//    s_shader.setVec2("size", size);
//    s_shader.setVec3("color", color / 255.0f);
//    s_shader.setVec2("pos", position);
//    s_shader.setFloat("rotation", rotation);
//    s_shader.setFloat("transparency", transparency);
//    s_shader.setFloat("outlineThickness", outlineThickness);
//    s_shader.setVec3("outlineColor", outlineColor);
//    if (texture != nullptr) {
//        s_shader.setInt("tex", 0);
//        s_shader.setBool("useTexture", true);
//        texture->bindTexture(0);
//    }
//    else {
//        s_shader.setBool("useTexture", false);
//    }
//    if (enableAbsolutePosition) {
//        s_shader.setVec2("viewportPosition", 0.0f, 0.0f);
//    }
//    else {
//        s_shader.setVec2("viewportPosition", target->getViewPortPosition());
//    }
//    s_shader.setVec2("viewportSize", target->getViewPortSize());
//
//    glBindVertexArray(s_vao);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//}
//
//void Rectangle::setupBuffer() {
//    glGenVertexArrays(1, &s_vao);
//    glGenBuffers(1, &s_vbo);
//    glGenBuffers(1, &s_ebo);
//
//    glBindVertexArray(s_vao);
//    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(s_vertices), s_vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_indices), s_indices, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    s_shader.load<Vertex, Fragment>("shaders/Rectangle");
//    s_hasInit = true;
//}
//
//Circle::Circle()
//    : radius(0), position(0.0), color(1.0), transparency(1.0) {
//    if (s_hasInit) {
//        return;
//    }
//    setNumSides(100);
//
//    s_shader.load<Vertex, Fragment>("shaders/Circle");
//    s_hasInit = true;
//}
//Circle::Circle(float _radius)
//	: radius(_radius), position(0.0), color(1.0), transparency(1.0) {
//    if (s_hasInit) {
//        return;
//    }
//    setNumSides(100);
//
//    s_shader.load<Vertex, Fragment>("shaders/Circle");
//    s_hasInit = true;
//}
//
//Circle::~Circle() {
//
//}
//
//void Circle::draw(RenderWindow* target, Texture* texture) {
//    glDisable(GL_CULL_FACE);
//
//    s_shader.use();
//    s_shader.setVec2("screenSize", target->getSize());
//    s_shader.setFloat("radius", radius);
//    s_shader.setVec3("color", color / 255.0f);
//    s_shader.setVec2("pos", position);
//    s_shader.setFloat("rotation", rotation);
//    s_shader.setFloat("transparency", transparency);
//    if (texture != nullptr) {
//        s_shader.setInt("tex", 0);
//        s_shader.setBool("useTexture", true);
//        texture->bindTexture(0);
//    }
//    else {
//        s_shader.setBool("useTexture", false);
//    }
//    if (enableAbsolutePosition) {
//        s_shader.setVec2("viewportPosition", 0.0f, 0.0f);
//    }
//    else {
//        s_shader.setVec2("viewportPosition", target->getViewPortPosition());
//    }
//    s_shader.setVec2("viewportSize", target->getViewPortSize());
//
//    glBindVertexArray(s_vao);
//    glDrawElements(GL_TRIANGLES, s_indices.size(), GL_UNSIGNED_INT, 0);
//}
//void Circle::setNumSides(int num) {
//    if (num == s_numSides) {
//        return;
//    }
//    const float PI = 3.14159265;
//    const float ang = PI * 2.0 / num;
//    s_vertices.clear();
//    s_vertices.resize(num);
//    for (int i = 0; i < num; ++i) {
//        s_vertices[i].x = cos(ang * i);
//        s_vertices[i].y = sin(ang * i);
//        s_vertices[i].z = (s_vertices[i].x + 1.0f) * 0.5f;
//        s_vertices[i].w = (-s_vertices[i].y + 1.0f) * 0.5f;
//    }
//    s_indices.clear();
//    s_indices.resize((num - 2) * 3);
//    for (int i = 0; i < num - 2; ++i) {
//        s_indices[i * 3] = 0;
//        s_indices[i * 3 + 1] = i + 1;
//        s_indices[i * 3 + 2] = static_cast<int>(mod(
//            static_cast<float>(i + 2), 
//            static_cast<float>(num + 1)
//        ));
//    }
//    glGenVertexArrays(1, &s_vao);
//    glGenBuffers(1, &s_vbo);
//    glGenBuffers(1, &s_ebo);
//
//    glBindVertexArray(s_vao);
//    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
//    glBufferData(GL_ARRAY_BUFFER, s_vertices.size() * sizeof(vec4), s_vertices.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_indices.size() * sizeof(unsigned int), s_indices.data(), GL_STATIC_DRAW);
//    
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec4), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec4), (void*)8);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//}

Rectangle::Rectangle(const vec2& _size) 
	: size(_size) {

}

void Rectangle::draw(Texture* texture) {
	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	al_translate_transform(&trans, -position.x - size.x * 0.5, -position.y - size.y * 0.5);
	if (rotation) {
		al_rotate_transform(&trans, -rotation);
	}
	al_translate_transform(&trans, position.x, position.y);
	al_use_transform(&trans);
	if (!texture) {
		if (!outlineThickness) {
			al_draw_filled_rectangle(
				position.x, 
				position.y, 
				position.x + size.x, 
				position.y + size.y, 
				al_map_rgba(color.r, color.g, color.b, color.a)
			);
		}
		else {
			al_draw_rectangle(
				position.x,
				position.y, 
				position.x + size.x, 
				position.y + size.y, 
				al_map_rgba(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a), 
				outlineThickness
			);
		}
	}
	else {
		al_draw_bitmap(texture->getBitmap(), position.x, position.y, 0);
	}
	al_identity_transform(&trans);
	al_use_transform(&trans);
}

void Rectangle::draw(const RenderWindow* window, Texture* texture) {
	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	al_translate_transform(&trans, std::round(-position.x - size.x * 0.5), std::round(-position.y - size.y * 0.5));
	if (rotation) {
		al_rotate_transform(&trans, -rotation);
	}
	al_translate_transform(&trans, position.x, position.y);
	if (window && !absolutePosition) {
		al_translate_transform(
			&trans, 
			std::round(-window->viewport.position.x),
			std::round(-window->viewport.position.y)
		);
	}
	al_use_transform(&trans);
	if (!texture) {
		if (!outlineThickness) {
			al_draw_filled_rectangle(
				std::round(position.x),
				std::round(position.y),
				std::round(position.x + size.x),
				std::round(position.y + size.y),
				al_map_rgba(color.r, color.g, color.b, color.a)
			);
		}
		else {
			al_draw_rectangle(
				std::round(position.x),
				std::round(position.y),
				std::round(position.x + size.x),
				std::round(position.y + size.y),
				al_map_rgba(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a),
				std::round(outlineThickness)
			);
		}
	}
	else {
		al_draw_scaled_bitmap(
			texture->getBitmap(), 
			0, 0,
			texture->getSize().x, texture->getSize().y,
			std::round(position.x), std::roundf(position.y),
			size.x, size.y,
			0
		);
	}
	al_identity_transform(&trans);
	al_use_transform(&trans);
}

Circle::Circle(float _radius)
	: radius(_radius) {

}

void Circle::draw(Texture* texture) {
	if (!outlineThickness) {
		al_draw_filled_circle(
			position.x,
			position.y,
			radius,
			al_map_rgba(color.r, color.g, color.b, color.a)
		);
	}
	else {
		al_draw_circle(
			position.x,
			position.y,
			radius,
			al_map_rgba(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a),
			outlineThickness
		);
	}
}

void Circle::draw(const RenderWindow* window, Texture* texture) {
	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);

	if (window && !absolutePosition) {
		al_translate_transform(
			&trans,
			-window->viewport.position.x,
			-window->viewport.position.y
		);
	}
	if (!outlineThickness) {
		al_draw_filled_circle(
			position.x,
			position.y,
			radius,
			al_map_rgba(color.r, color.g, color.b, color.a)
		);
	}
	else {
		al_draw_circle(
			position.x,
			position.y,
			radius,
			al_map_rgba(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a),
			outlineThickness
		);
	}
}
