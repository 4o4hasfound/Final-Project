//#pragma once
//
//template<typename T>
//PoolAllocator<T>::PoolAllocator(int initObjectCount) {
//	m_freelist.reserve(initObjectCount);
//	constexpr int objectSize = (sizeof(T) + alignof(T));
//	m_ptr = malloc(objectSize * initObjectCount);
//	for (int i = 0; i < initObjectCount; ++i) {
//		int id = m_freelist.push(Chunk{});
//		m_freelist[id].ptr = (T*)m_ptr + i;
//		m_freelist[id].id = id;
//	}
//}
//template<typename T>
//PoolAllocator<T>::~PoolAllocator() {
//	delete m_ptr;
//}