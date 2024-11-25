#include <vector>

#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"

#include "Debug/Log.hpp"

#include "Render/RenderWindow.hpp"
#include "Render/Shape.hpp"

#include "Physics/AABB.hpp"
#include "Physics/RigidBody.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Physics/RectCollider.hpp"
#include "Physics/SphereCollider.hpp"

#include "Engine/Engine.hpp"
#include "Utils/Clock.hpp"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>


class CircleBody {
public:
    CircleBody(RigidBody* _body, float _radius, const vec4 _color = vec4(255))
        : body(_body), radius(_radius), color(_color) {
        body->setMass(15.0f);
        body->setRotation(3.14159 * 0.00f);
        body->setTorque(0.0f);
        body->setRestitution(0.3f);
        body->setForce(vec2(0.0f, 0.0f));
        body->setVelocity(vec2(0.0f, 0.0f));
        body->setAngularVelocity(0.0f);
        body->setStaticFriction(0.6f);
        body->setDynamicFriction(0.4f);
        body->setInertia(0.5f * body->getMass() * radius * radius);
        body->addCollider<SphereCollider>(_radius);
    }

    void draw(RenderWindow& window) {
        m_shape.color = color;
        m_shape.position = body->getPosition() * 1000.0f;
        m_shape.radius = radius * 1000.0f;
        m_shape.draw();
    }

    vec4 color;
    RigidBody* body;
private:
    Circle m_shape;
    float radius;
};

class RectBody {
public:
    RectBody(RigidBody* _body, float _width, float _height, const vec4 _color = vec4(255))
        : body(_body), width(_width), height(_height), color(_color) {
        body->setMass(15.0f);
        body->setRotation(3.14159 * 0.00f);
        body->setTorque(0.0f);
        body->setRestitution(0.3f);
        body->setForce(vec2(0.0f, 0.0f));
        body->setVelocity(vec2(0.0f, 0.0f));
        body->setAngularVelocity(0.0f);
        body->setStaticFriction(0.6f);
        body->setDynamicFriction(0.4f);
        body->setInertia((1.0 / 12.0) * body->getMass() * (width * width + height * height));
        body->addCollider<RectCollider>(width, height);
    }

    void draw() {
        m_shape.color = color;
        m_shape.position = body->getPosition();
        m_shape.size.x = width;
        m_shape.size.y = height;
        m_shape.rotation = body->getRotation();
        m_shape.draw();
    }

    vec4 color;
    RigidBody* body;
private:
    Rectangle m_shape;
    float width, height;
};


int main() {
	Engine::Init();

	RenderWindow window(1960, 1080, "Game!");

    PhysicsWorld world;
    std::vector<RectBody> rectBodies;
    std::vector<CircleBody> circleBodies;

    for (int i = 0; i < 100; ++i) {
        RigidBody* b123 = world.createBody(RigidBody::Dynamic);
        RectBody tmp(b123, 64.0f, 32.0f, vec4(100, 100, 100, 255));
        b123->setPosition(rand() % 1960, rand() % 1080);
        while (world.hasCollide(b123)) {
            b123->move(rand() % 100 - 50, 0);
            b123->move(0, rand() % 100 - 50);
        }
        rectBodies.emplace_back(std::move(tmp));
    }
    Clock clock;
	while (1) {
		window.clear();
        world.update(clock.reset());
        for (auto& body : rectBodies) {
            body.draw();
        }
        world.DebugDraw();
		window.flipDisplay();
	}
}