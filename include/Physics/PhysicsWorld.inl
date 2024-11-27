template<typename BodyT, typename>
BodyT* PhysicsWorld::createBody(RigidBody::BodyType type, const RigidBodySetting& setting) {
	int id = m_bodies.emplace(nullptr);
	m_bodies[id] = (BodyT*)m_allocator.allocate();
	new(m_bodies[id]) BodyT(type, id, this);

	//RigidBody* ptr = new RigidBody(type, id, this);;
	//m_bodies[id] = ptr;

	m_treeTiles.insert(m_bodies[id]);

	return m_bodies[id];
}
