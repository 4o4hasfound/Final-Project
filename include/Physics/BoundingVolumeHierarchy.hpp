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

// Bounding volume hierarchy, 
// a tree structure on a set of geometric objects, 
// a spatial data structure used for efficient collision detection and rendering
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
		// Checks if this node is a leaf (has no children)
		bool isLeaf() const { return child[0] == -1 && child[1] == -1; }
		// Checks if the given node index is the left child of this node
		bool isLeftChild(int node) { return node == child[0]; }
		// Checks if the given node index is the right child of this node
		bool isRightChild(int node) { return node == child[1]; }
	};
public:
	BVH();

	// Insert a rigid body into the BVH, returning the index of the inserted node
	int insert(RigidBody* body);
	// Remove a node from the BVH by its index
	void remove(int index);
	// Remove a rigid body from the BVH
	void remove(const RigidBody* body);

	// Update the BVH, refitting or rebalancing nodes as necessary
	void update();

	// Render the BVH structure
	void render(const RenderWindow& window) const;

	// Perform a query to find all rigid bodies intersecting the given AABB
	void query(const AABB& aabb, std::vector<RigidBody*>& result) const;
	// Check if any object in the BVH collides with the given AABB
	bool hasCollide(const AABB& aabb) const;

	// Set the enlargement factor for AABBs during insertion
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