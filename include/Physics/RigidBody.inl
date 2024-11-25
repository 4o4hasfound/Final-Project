#pragma once

template<typename ColliderType, typename ...Ts, typename>
inline ColliderType* RigidBody::addCollider(Ts && ...params) {
	ColliderType* ptr = new ColliderType(std::forward<Ts>(params)...);
	
	m_collider.reset(ptr);

	m_aabb |= ptr->getTransformedAABB();

	m_inertia = ptr->getInertia(m_mass);

	if (m_inertia && type == RigidBody::Dynamic) {
		m_invInertia = 1.0 / m_inertia;
	}

	return ptr;
}
