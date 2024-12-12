#include "Physics/BoundingVolumeHierarchy.hpp"

BVH::BVH() {

}

int BVH::insert(RigidBody* body) {
	int ind = m_bodies.push(body);
	insertLeaf(ind);

	return ind;
}

void BVH::remove(int index) {
	removeLeaf(m_bodies[index]);
}

void BVH::remove(const RigidBody* body) {
	removeLeaf(body);
}

void BVH::update() {
	for (const Node& node : m_nodes) {
		if (!node.isLeaf()) {
			continue;
		}
		
		if (node.aabb.contain(m_bodies[node.object]->getAABB())) {
			continue;
		}

		const RigidBody* body = m_bodies[node.object];
		removeLeaf(body, 0);
		insertLeaf(node.object);
	}
}

float BVH::computeInheritCost(int object, int node) const {
	float cost = 0.0f;
	AABB aabb = m_bodies[object]->getAABB();
	enlargeAABB(aabb);
	while (node != -1 && m_nodes[node].parent != -1) {
		cost +=
			(m_nodes[node].aabb | aabb).area()
			- m_nodes[node].aabb.area();
		node = m_nodes[node].parent;
	}
	return cost;
}

int BVH::pickSibling(int object) const {
	AABB aabb = m_bodies[object]->getAABB();
	enlargeAABB(aabb);
	int node = m_root;

	while (!m_nodes[node].isLeaf()) {
		int lchild = m_nodes[node].child[0];
		int rchild = m_nodes[node].child[1];

		int cost = (m_nodes[node].aabb | aabb).area();
		cost += computeInheritCost(object, m_nodes[node].parent);

		int lcost = (m_nodes[lchild].aabb | aabb).area();
		lcost += computeInheritCost(object, m_nodes[lchild].parent);

		int rcost = (m_nodes[rchild].aabb | aabb).area();
		rcost += computeInheritCost(object, m_nodes[rchild].parent);

		if (cost < lcost && cost < rcost) {
			break;
		}
		else if (lcost < rcost) {
			node = lchild;
		}
		else {
			node = rchild;
		}
	}

	return node;
}

void BVH::insertLeaf(int object) {
	// Create a new node
	AABB aabb = m_bodies[object]->getAABB();
	enlargeAABB(aabb);
	int node = m_nodes.emplace(object, aabb);
	if (m_nodes.size() == 1) {
		// Set it to root node
		m_root = node;
		return;
	}

	int sibling = pickSibling(object);
	createParent(node, sibling, object);
	refitTree(m_nodes[node].parent);
}

void BVH::render(const RenderWindow& window) const {
	Rectangle rect;
	rect.outlineColor = vec4(255.0);
	rect.outlineThickness = 1.0;
	rect.rotation = 0.0f;

	for (const Node& node : m_nodes) {
		//if (node.object != -1) {
		//	continue;
		//}
		rect.size = node.aabb.size();
		rect.position = node.aabb.lowerBound + rect.size * 0.5f;
		if (node.isLeaf()) {
			rect.outlineThickness = 5;
			//rect.size = m_bodies[node.object]->getAABB().size();
		}
		else {
			rect.outlineThickness = 1;
		}
		window.draw(rect);
	}
}

void BVH::query(const AABB& aabb, std::vector<RigidBody*>& result) const {
	std::vector<int> st;
	st.push_back(m_root);
	while (!st.empty()) {
		int node = st.back();
		st.pop_back();

		if (m_nodes[node].aabb.intersect(aabb)) {
			if (m_nodes[node].isLeaf() && m_bodies[m_nodes[node].object]->getAABB().intersect(aabb)) {
				result.push_back(m_bodies[m_nodes[node].object]);
			}
			else {
				if (m_nodes[node].child[0] != -1) st.push_back(m_nodes[node].child[0]);
				if (m_nodes[node].child[1] != -1) st.push_back(m_nodes[node].child[1]);
			}
		}
	}
}

void BVH::refitTree(int node) {
	while (node != -1) {
		node = balanceNode(node);

		int child0 = m_nodes[node].child[0];
		int child1 = m_nodes[node].child[1];

		m_nodes[node].aabb = m_nodes[child0].aabb | m_nodes[child1].aabb;
		m_nodes[node].height = std::max(
			m_nodes[child0].height,
			m_nodes[child1].height
		) + 1;

		node = m_nodes[node].parent;
	}
}

void BVH::createParent(int node, int sibling, int object) {
	AABB aabb = m_bodies[object]->getAABB();
	enlargeAABB(aabb);
	int oldParent = m_nodes[sibling].parent;
	int newParent = m_nodes.emplace(aabb);

	m_nodes[newParent].parent = oldParent;
	m_nodes[newParent].aabb = aabb | m_nodes[sibling].aabb;
	m_nodes[newParent].height = m_nodes[node].height + 1;

	if (oldParent != -1) {
		if (m_nodes[oldParent].child[0] == sibling) {
			m_nodes[oldParent].child[0] = newParent;
		}
		else {
			m_nodes[oldParent].child[1] = newParent;
		}
		m_nodes[newParent].child[0] = sibling;
		m_nodes[sibling].parent = newParent;
		m_nodes[newParent].child[1] = node;
		m_nodes[node].parent = newParent;
	}
	else {
		m_nodes[newParent].child[0] = sibling;
		m_nodes[sibling].parent = newParent;
		m_nodes[newParent].child[1] = node;
		m_nodes[node].parent = newParent;
		m_root = newParent;
	}
}

bool BVH::hasCollide(const AABB& aabb) const {
	std::vector<int> st;
	st.push_back(m_root);
	while (!st.empty()) {
		int node = st.back();
		st.pop_back();

		if (m_nodes[node].aabb.intersect(aabb)) {
			if (m_nodes[node].isLeaf()) {
				return 1;
			}
			else {
				if (m_nodes[node].child[0] != -1) st.push_back(m_nodes[node].child[0]);
				if (m_nodes[node].child[1] != -1) st.push_back(m_nodes[node].child[1]);
			}
		}
	}
	return 0;
}

void BVH::setAABBEnlargeFactor(float factor) {
	assert(factor >= 1.0f);
	m_aabbEnlargeFactor = factor;
}

void BVH::removeLeaf(const RigidBody* body, bool removeObject) {
	// Find leaf
	int node = getLeafIndex(body);

	if (node == -1) {
		return;
	}
	if (node == m_root) {
		m_root = -1;
		if (removeObject) {
			m_bodies.remove(m_nodes[node].object);
		}
		m_nodes.remove(node);
		return;
	}	

	int parent = m_nodes[node].parent;
	int grandParent = m_nodes[parent].parent;
	int sibling;
	if (m_nodes[parent].isLeftChild(node)) {
		sibling = m_nodes[parent].child[1];
	}
	else {
		sibling = m_nodes[parent].child[0];
	}

	if (grandParent != -1) {
		if (m_nodes[grandParent].isLeftChild(parent)) {
			m_nodes[grandParent].child[0] = sibling;
		}
		else {
			m_nodes[grandParent].child[1] = sibling;
		}
		m_nodes[sibling].parent = grandParent;
		m_nodes.remove(parent);

		refitTree(grandParent);
	}
	else {
		m_root = sibling;
		m_nodes[sibling].parent = -1;
		m_nodes.remove(parent);
	}
	if (removeObject) {
		m_bodies.remove(m_nodes[node].object);
	}
	m_nodes.remove(node);
}

int BVH::getObjectIndex(const RigidBody* body) {
	int index = getLeafIndex(body);
	if (index == -1) {
		return -1;
	}
	return m_nodes[index].object;
}

int BVH::balanceNode(int node) {
	if (m_nodes[node].isLeaf() || m_nodes[node].height < 2 || node == -1) {
		return node;
	}
	int b = m_nodes[node].child[0];
	int c = m_nodes[node].child[1];

	if (b == -1 || c == -1) {
		return node;
	}

	int balance = m_nodes[c].height - m_nodes[b].height;

	if (balance > 2) {
		int f = m_nodes[c].child[0];
		int g = m_nodes[c].child[1];

		m_nodes[c].child[0] = node;
		m_nodes[c].parent = m_nodes[node].parent;
		m_nodes[node].parent = c;

		int cParent = m_nodes[c].parent;
		if (cParent != -1) {
			if (m_nodes[cParent].child[0] == node) {
				m_nodes[cParent].child[0] = c;
			}
			else {
				m_nodes[cParent].child[1] = c;
			}
		}
		else {
			m_root = c;
		}

		// rotate
		if (m_nodes[f].height > m_nodes[g].height) {
			m_nodes[c].child[1] = f;
			m_nodes[node].child[1] = g;
			m_nodes[g].parent = node;

			m_nodes[node].aabb = m_nodes[b].aabb | m_nodes[g].aabb;
			m_nodes[c].aabb = m_nodes[node].aabb | m_nodes[f].aabb;

			m_nodes[node].height = std::max(m_nodes[b].height, m_nodes[g].height) + 1;
			m_nodes[c].height = std::max(m_nodes[node].height, m_nodes[f].height) + 1;
		}
		else {
			m_nodes[c].child[1] = g;
			m_nodes[node].child[1] = f;
			m_nodes[f].parent = node;

			m_nodes[node].aabb = m_nodes[b].aabb | m_nodes[f].aabb;
			m_nodes[c].aabb = m_nodes[node].aabb | m_nodes[g].aabb;

			m_nodes[node].height = std::max(m_nodes[b].height, m_nodes[f].height) + 1;
			m_nodes[c].height = std::max(m_nodes[node].height, m_nodes[g].height) + 1;
		}
		return c;
	}


	// rotate b up
	if (balance < -2) {

		int d = m_nodes[b].child[0];
		int e = m_nodes[b].child[1];

		// swap node and b
		m_nodes[b].child[0] = node;
		m_nodes[b].parent = m_nodes[node].parent;
		m_nodes[node].parent = b;

		// node's old parent should point to b
		int bParent = m_nodes[b].parent;
		if (bParent != -1) {
			if (m_nodes[bParent].child[0] == node) {
				m_nodes[bParent].child[0] = b;
			}
			else {
				m_nodes[bParent].child[1] = b;
			}
		}
		else {
			m_root = b;
		}

		// rotate
		if (m_nodes[d].height > m_nodes[e].height) {
			m_nodes[b].child[1] = d;
			m_nodes[node].child[0] = e;
			m_nodes[e].parent = node;

			m_nodes[node].aabb = m_nodes[c].aabb | m_nodes[e].aabb;
			m_nodes[b].aabb = m_nodes[node].aabb | m_nodes[d].aabb;

			m_nodes[node].height = 1 + std::max(m_nodes[c].height, m_nodes[e].height);
			m_nodes[b].height = 1 + std::max(m_nodes[node].height, m_nodes[d].height);
		}
		else {
			m_nodes[b].child[1] = e;
			m_nodes[node].child[0] = d;
			m_nodes[d].parent = node;

			m_nodes[node].aabb = m_nodes[c].aabb | m_nodes[d].aabb;
			m_nodes[b].aabb = m_nodes[node].aabb | m_nodes[e].aabb;

			m_nodes[node].height = std::max(m_nodes[c].height, m_nodes[d].height) + 1;
			m_nodes[b].height = std::max(m_nodes[node].height, m_nodes[e].height) + 1;
		}

		return b;
	}

	return node;
}

int BVH::getLeafIndex(const RigidBody* body) {
	//int index;
	//std::stack<int> nodes;
	//nodes.push(m_root);

	//while (!nodes.empty()) {
	//	int node = nodes.top();
	//	nodes.pop();

	//	if (m_nodes[node].isLeaf()) {
	//		if (m_bodies[m_nodes[node].object] == body) {
	//			return node;
	//		}
	//		continue;
	//	}
	//	if (!m_nodes[node].aabb.contain(body->getAABB())) {
	//		continue;
	//	}
	//	if (m_nodes[node].child[0] != -1) nodes.push(m_nodes[node].child[0]);
	//	if (m_nodes[node].child[1] != -1) nodes.push(m_nodes[node].child[1]);
	//}
	//return -1;
	for (const Node& node : m_nodes) {
		if (!node.isLeaf()) {
			continue;
		}
		if (m_bodies[node.object] == body) {
			if (node.parent == -1) {
				return m_root;
			}
			else if (&m_nodes[m_nodes[node.parent].child[0]] == &node) {
				return m_nodes[node.parent].child[0];
			}
			else {
				return m_nodes[node.parent].child[1];
			}
		}
	}
	return -1;
}

void BVH::enlargeAABB(AABB& aabb) const {
	aabb.enlarge(aabb.size() * m_aabbEnlargeFactor);
}
