#pragma once
#include <queue>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <limits>

#include "Render/Shape.hpp"
#include "Render/RenderWindow.hpp"

#include "Physics/AABB.hpp"
#include "Physics/RigidBody.hpp"

#include "Container/FreeList.hpp"

class BVH {
private:
	struct Node {
		AABB aabb;

		int object = -1;
		int parent = -1;
		int child[2] = { -1, -1 };
		int height = -1;

		Node() = default;
		Node(const AABB& aabb)
			: aabb(aabb) {

		}
		Node(int objectInd, const AABB& aabb)
			: aabb(aabb), object(objectInd) {

		}
		bool isLeaf() const { return child[0] == -1 && child[1] == -1; }
		bool isLeftChild(int node) { return node == child[0]; }
		bool isRightChild(int node) { return node == child[1]; }
	};
public:
	BVH();
	
	int insert(RigidBody* body);
	void remove(int index);
	void remove(const RigidBody* body);

	void update();

	void render() const;

	void query(const AABB& aabb, std::vector<RigidBody*>& result) const;
	bool hasCollide(const AABB& aabb) const;

	void setAABBEnlargeFactor(float factor);
private:
	FreeList<Node> m_nodes;
	FreeList<RigidBody*> m_bodies;
	int m_root = -1;

	float m_aabbEnlargeFactor = 2.0f;

	void insertLeaf(int object);
	void removeLeaf(const RigidBody* body, bool removeObject = 1);

	int getObjectIndex(const RigidBody* body);
	int getLeafIndex(const RigidBody* body);

	int pickSibling(int object) const;
	float computeInheritCost(int object, int node) const;
	void createParent(int node, int sibling, int object);
	// Pass in the newly created parent
	void refitTree(int node);
	int balanceNode(int node);

	void enlargeAABB(AABB& aabb) const;
};