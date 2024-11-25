#include "Physics/RectCollider.hpp"

RectCollider::RectCollider(float _width, float _height, const Transform& transform)
	: Collider(Collider::Polygon, AABB({ _width * -0.5f, _height * -0.5f }, { _width * 0.5f, _height * 0.5f }), transform), width(_width), height(_height) {

}

RectCollider::RectCollider(float _width, float _height)
	: Collider(Collider::Polygon, AABB({ _width * -0.5f, _height * -0.5f }, { _width * 0.5f, _height * 0.5f }), Transform{}), width(_width), height(_height) {

}

RectCollider::RectCollider(const vec2& size, const Transform& transform)
	: Collider(Collider::Polygon, AABB(size * -0.5f, size * 0.5f), transform), width(size.x), height(size.y) {

}

RectCollider::RectCollider(const vec2& size)
	: Collider(Collider::Polygon, AABB(size * -0.5f, size*0.5f), Transform{}), width(size.x), height(size.y) {

}

void RectCollider::getTransformedVertices(std::vector<vec2>& output, const Transform& _transform) {
	if (m_needUpdateVertices) {
		m_needUpdateVertices = 0;

		const Transform trans = this->transform + _transform;

		float cosTheta = cos(trans.rotation);
		float sinTheta = sin(trans.rotation);
		mat2 rotationMatrix = mat2(cosTheta, sinTheta, -sinTheta, cosTheta) * trans.scale;

		m_vertices.resize(4);

		m_vertices[0] = vec2{ width * 0.5f, height * 0.5f } * rotationMatrix + trans.position;
		m_vertices[1] = vec2{ -width * 0.5f, height * 0.5f } * rotationMatrix + trans.position;
		m_vertices[2] = vec2{ -width * 0.5f, -height * 0.5f } * rotationMatrix + trans.position;
		m_vertices[3] = vec2{ width * 0.5f, -height * 0.5f } * rotationMatrix + trans.position;
	}
	output.insert(output.begin(), m_vertices.begin(), m_vertices.end());
	return;
}

Collider::CollisionTestResult RectCollider::testCollision(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) {
	switch (collider->shape) {
	case Circle:
		return testCollisionSphere(collider, myTrans, colliderTrans);
	case Rectangle:
		return testCollisionRect(collider, myTrans, colliderTrans);
	case Polygon:
		return testCollisionPolygon(collider, myTrans, colliderTrans);
	}
}

std::pair<float, float> RectCollider::project(const vec2& axis, const Transform& _transform) {
	const vec2 normal = normalize(axis);

	std::vector<vec2> result;
	getTransformedVertices(result, _transform);

	std::pair<float, float> ret = {
		std::numeric_limits<float>::max(), 
		-std::numeric_limits<float>::max()
	};
	for (int i = 0; i < 4; ++i) {
		float proj = dot(result[i], normal);
		ret.first =	std::min(ret.first, proj);
		ret.second = std::max(ret.second, proj);
	}
	return ret;
}

double RectCollider::getInertia(double mass) const {
	return (width * width + height * height) * mass / 12.0;
}

Collider::CollisionTestResult RectCollider::testCollisionSphere(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) {
	CollisionTestResult ret;
	ret.collided = false;

	const Transform myGlobalTrans = myTrans + transform;
	const Transform colliderGlobalTrans = colliderTrans + collider->transform;

	std::vector<vec2> vertices;
	getTransformedVertices(vertices, myGlobalTrans);

	ret.normal = vec2(0);
	ret.depth = std::numeric_limits<float>::max();

	vec2 closestPointOnPolygon = vertices[0];

	for (int i = 0; i < vertices.size(); ++i) {
		if (distance(colliderGlobalTrans.position, vertices[i]) < distance(colliderGlobalTrans.position, closestPointOnPolygon)) {
			closestPointOnPolygon = vertices[i];
		}
		const vec2 edge = vertices[(i + 1) % vertices.size()] - vertices[i];
		const vec2 axis = normalize(vec2{ edge.y, -edge.x });

		std::pair<float, float> p1 = project(axis, myGlobalTrans);
		std::pair<float, float> p2 = collider->project(axis, colliderGlobalTrans);

		if (p1.first >= p2.second || p2.first >= p1.second) {
			return ret;
		}

		float intersect = p2.second - p1.first;
		if (ret.depth > intersect) {
			ret.normal = axis;
			ret.depth = intersect;
		}
	}

	const vec2 axis = normalize(closestPointOnPolygon - colliderGlobalTrans.position);

	std::pair<float, float> p1 = project(axis, myGlobalTrans);
	std::pair<float, float> p2 = collider->project(axis, colliderGlobalTrans);

	if (p1.first >= p2.second || p2.first >= p1.second) {
		return ret;
	}

	float intersect = std::min(p2.second - p1.first, p1.second - p2.first);
	vec2 normal = axis;
	if (dot(axis, colliderGlobalTrans.position - myGlobalTrans.position) > 0.0f) {
		normal = -normal;
	}
	if (ret.depth > intersect) {
		ret.normal = normal;
		ret.depth = intersect;
	}
	ret.collided = true;

	float contactDistanceSquared = std::numeric_limits<float>::max();
	vec2 contactPoint;

	for (int i = 0; i < vertices.size(); ++i) {
		const vec2 pa = vertices[(i + 1) % vertices.size()];
		const vec2 pb = vertices[i];

		const vec2 p = closestPointOnLine(colliderGlobalTrans.position, pa, pb);
		const vec2 vec = colliderGlobalTrans.position - p;
		float distanceSquared = dot(vec, vec);

		if (distanceSquared < contactDistanceSquared) {
			contactDistanceSquared = distanceSquared;
			contactPoint = p;
		}
	}

	ret.contactCount = 1;
	ret.contact[0] = contactPoint;
	return ret;
}

Collider:: CollisionTestResult RectCollider::testCollisionRect(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) {
	// https://github.com/erincatto/box2d-lite/blob/master/src/Collide.cpp

	enum Face {
		FACE_A_X,
		FACE_A_Y,
		FACE_B_X,
		FACE_B_Y
	};

	CollisionTestResult ret;
	ret.collided = false;

	const Transform myGlobalTrans = myTrans + transform;
	const Transform colliderGlobalTrans = colliderTrans + collider->transform;

	RectCollider* rectCollider = dynamic_cast<RectCollider*>(collider);

	std::vector<vec2> vertices;
	getTransformedVertices(vertices, myGlobalTrans);
	std::vector<vec2> vertices2;
	collider->getTransformedVertices(vertices2, colliderGlobalTrans);

	const vec2 ha{
		0.5f * width,
		0.5f * height
	};
	const vec2 hb{
		0.5f * rectCollider->width,
		0.5f * rectCollider->height
	};

	const float cosThetaA = cos(myGlobalTrans.rotation);
	const float sinThetaA = sin(myGlobalTrans.rotation);
	const float cosThetaB = cos(colliderGlobalTrans.rotation);
	const float sinThetaB = sin(colliderGlobalTrans.rotation); 
	
	const mat2 RotA = mat2(cosThetaA, sinThetaA, -sinThetaA, cosThetaA) * myGlobalTrans.scale;
	const mat2 RotAT = transpose(RotA);

	const mat2 RotB = mat2(cosThetaB, sinThetaB, -sinThetaB, cosThetaB) * colliderGlobalTrans.scale;
	const mat2 RotBT = transpose(RotB);

	const vec2 dp = colliderGlobalTrans.position - colliderGlobalTrans.position;
	const vec2 dA = RotAT * dp;
	const vec2 dB = RotBT * dp;

	const mat2 C = RotAT * RotB;
	const mat2 absC = abs(C);
	const mat2 absCT = transpose(absC);

	const vec2 faceA = abs(dA) - ha - absC * hb;
	if (faceA.x > 0.0f || faceA.y > 0.0f) {
		return ret;
	}
	const vec2 faceB = abs(dB) - absCT * ha - hb;
	if (faceB.x > 0.0f || faceB.y > 0.0f) {
		return ret;
	}

	// Find best axis
	Face axis;

	// Box A faces
	axis = FACE_A_X;
	ret.depth = -faceA.x;
	ret.normal = dA.x > 0.0f ? RotA[0] : -RotA[0];

	if (faceA.y < ret.depth) {
		axis = FACE_A_Y;
		ret.depth = -faceA.y;
		ret.normal = dA.y > 0.0f ? RotA[1] : -RotA[1];
	}

	// Box B faces
	if (faceB.x < ret.depth) {
		axis = FACE_B_X;
		ret.depth = -faceB.x;
		ret.normal = dB.x > 0.0f ? RotB[0] : -RotB[0];
	}

	if (faceB.y < ret.depth) {
		axis = FACE_B_Y;
		ret.depth = -faceB.y;
		ret.normal = dB.y > 0.0f ? RotB[1] : -RotB[1];
	}

	float contactDistanceSquared = std::numeric_limits<float>::max();
	int contactPointIndex = 0;

	vec2 contactPoint[2];
	for (int i = 0; i < vertices.size(); ++i) {
		const vec2 originPoint = vertices[i];
		for (int j = 0; j < vertices2.size(); ++j) {
			const vec2 pa = vertices2[(j + 1) % vertices2.size()];
			const vec2 pb = vertices2[j];

			const vec2 p = closestPointOnLine(originPoint, pa, pb);
			const vec2 vec = originPoint - p;
			float distanceSquared = dot(vec, vec);

			if (abs(distanceSquared - contactDistanceSquared) < 0.001f) {
				contactPointIndex = 1;
				contactDistanceSquared = distanceSquared;
				contactPoint[contactPointIndex] = p;
			}
			else if (distanceSquared < contactDistanceSquared) {
				contactPointIndex = 0;
				contactDistanceSquared = distanceSquared;
				contactPoint[0] = p;
			}
		}
	}

	for (int i = 0; i < vertices2.size(); ++i) {
		const vec2 originPoint = vertices2[i];
		for (int j = 0; j < vertices.size(); ++j) {
			const vec2 pa = vertices[(j + 1) % vertices.size()];
			const vec2 pb = vertices[j];

			const vec2 p = closestPointOnLine(originPoint, pa, pb);
			const vec2 vec = originPoint - p;
			float distanceSquared = dot(vec, vec);

			if (abs(distanceSquared - contactDistanceSquared) < 0.001f) {
				contactPointIndex = 1;
				contactDistanceSquared = distanceSquared;
				contactPoint[contactPointIndex] = p;
			}
			else if (distanceSquared < contactDistanceSquared) {
				contactPointIndex = 0;
				contactDistanceSquared = distanceSquared;
				contactPoint[contactPointIndex] = p;
			}
		}
	}
	ret.contactCount = contactPointIndex + 1;
	ret.contact[0] = contactPoint[0];
	ret.contact[1] = contactPoint[1];

	ret.collided = true;
	return ret;
}

Collider::CollisionTestResult RectCollider::testCollisionPolygon(Collider* collider, const Transform& myTrans, const Transform& colliderTrans) {
	CollisionTestResult ret;
	ret.collided = false;

	const Transform myGlobalTrans = myTrans + transform;
	const Transform colliderGlobalTrans = colliderTrans + collider->transform;

	std::vector<vec2> vertices;
	getTransformedVertices(vertices, myGlobalTrans);

	ret.normal = vec2(0);
	ret.depth = std::numeric_limits<float>::max();

	for (int i = 0; i < vertices.size(); ++i) {
		const vec2 edge = vertices[(i + 1) % vertices.size()] - vertices[i];
		const vec2 axis = normalize(vec2{ edge.y, -edge.x });

		std::pair<float, float> p1 = project(axis, myGlobalTrans);
		std::pair<float, float> p2 = collider->project(axis, colliderGlobalTrans);

		if (p1.first >= p2.second || p2.first >= p1.second) {
			return ret;
		}

		float intersect = p2.second - p1.first;
		if (ret.depth > intersect) {
			ret.normal = axis;
			ret.depth = intersect;
		}
	}

	std::vector<vec2> vertices2;
	collider->getTransformedVertices(vertices2, colliderGlobalTrans);
	for (int i = 0; i < vertices2.size(); ++i) {
		const vec2 edge = vertices2[(i + 1) % vertices2.size()] - vertices2[i];
		const vec2 axis = normalize(vec2{ edge.y, -edge.x });

		std::pair<float, float> p1 = project(axis, myGlobalTrans);
		std::pair<float, float> p2 = collider->project(axis, colliderGlobalTrans);

		if (p1.first >= p2.second || p2.first >= p1.second) {
			return ret;
		}

		float intersect = p2.second - p1.first;
		if (ret.depth > intersect) {
			ret.normal = axis;
			ret.depth = intersect;
		}
	}

	float contactDistanceSquared = std::numeric_limits<float>::max();
	int contactPointIndex = 0;

	vec2 contactPoint[2];
	for (int i = 0; i < vertices.size(); ++i) {
		const vec2 originPoint = vertices[i];
		for (int j = 0; j < vertices2.size(); ++j) {
			const vec2 pa = vertices2[(j + 1) % vertices2.size()];
			const vec2 pb = vertices2[j];

			const vec2 p = closestPointOnLine(originPoint, pa, pb);
			const vec2 vec = originPoint - p;
			float distanceSquared = dot(vec, vec);

			if (abs(distanceSquared - contactDistanceSquared) < 0.001f) {
				contactPointIndex = 1;
				contactDistanceSquared = distanceSquared;
				contactPoint[contactPointIndex] = p;
			}
			else if (distanceSquared < contactDistanceSquared) {
				contactPointIndex = 0;
				contactDistanceSquared = distanceSquared;
				contactPoint[0] = p;
			}
		}
	}

	for (int i = 0; i < vertices2.size(); ++i) {
		const vec2 originPoint = vertices2[i];
		for (int j = 0; j < vertices.size(); ++j) {
			const vec2 pa = vertices[(j + 1) % vertices.size()];
			const vec2 pb = vertices[j];

			const vec2 p = closestPointOnLine(originPoint, pa, pb);
			const vec2 vec = originPoint - p;
			float distanceSquared = dot(vec, vec);

			if (abs(distanceSquared - contactDistanceSquared) < 0.001f) {
				contactPointIndex = 1;
				contactDistanceSquared = distanceSquared;
				contactPoint[contactPointIndex] = p;
			}
			else if (distanceSquared < contactDistanceSquared) {
				contactPointIndex = 0;
				contactDistanceSquared = distanceSquared;
				contactPoint[contactPointIndex] = p;
			}
		}
	}
	ret.contactCount = contactPointIndex + 1;
	ret.contact[0] = contactPoint[0];
	ret.contact[1] = contactPoint[1];

	ret.collided = true;
	return ret;
}
