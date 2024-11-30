#include "FreeList.hpp"
#pragma once

template<typename T>
inline FreeList<T>::FreeList()
	: m_data(nullptr)
	, m_dataEnd(nullptr)
	, m_capacity(nullptr)
	, m_size(0) {
	
}
template<typename T>
inline FreeList<T>::FreeList(int n) 
	: m_data(malloc(sizeof(Element) * n))
	, m_dataEnd(m_data + n)
	, m_capacity(m_data + n) 
	, m_size(n)
{

	initElement(0, n);
	fillDefault();
}


template<typename T>
inline FreeList<T>::FreeList(int n, const T& t)
	: m_data(malloc(sizeof(Element)* n))
	, m_dataEnd(m_data + n)
	, m_capacity(m_data + n)
	, m_size(n)
{

	initElement(0, n);
	fillValue(t);
}

template<typename T>
inline FreeList<T>::FreeList(const std::initializer_list<T>& list)
	: m_size(list.size())
	, m_data((Element*)malloc(sizeof(Element)* list.size()))
	, m_dataEnd(m_data + list.size())
	, m_capacity(m_data + list.size())
{

	initElement(0, list.size());
	fillIter(list.begin(), list.end());
}
template<typename T>
inline FreeList<T>::FreeList(const const_iterator& _start, const const_iterator& _end)
	: m_size((_end - _start))
	, m_data((Element*)malloc(sizeof(Element)* m_size))
	, m_dataEnd(m_data + m_size)
	, m_capacity(m_data + m_size)
{

	initElement(0, m_size);
	fillIter(_start, m_size);
}

template<typename T>
inline FreeList<T>::FreeList(const const_reverse_iterator& _start, const const_reverse_iterator& _end)
	: m_size(_end - _start)
	, m_data((Element*)malloc(sizeof(Element)* m_size))
	, m_dataEnd(m_data + m_size)
	, m_capacity(m_data + m_size)
{

	initElement(0, m_size);
	fillIter(_start, _end);
}

template<typename T>
inline FreeList<T>::FreeList(const FreeList<T>& other)
	: m_data(malloc(sizeof(Element) * other.capacity()))
	, m_firstFree(other.m_firstFree)
	, m_dataEnd(m_data + (other.m_dataEnd - other.m_data))
	, m_capacity(m_data + other.capacity())
	, m_size(other.m_size)
{

	
}

template<typename T>
inline FreeList<T>::FreeList(FreeList<T>&& other)
	: m_data(other.m_data)
	, m_firstFree(other.m_firstFree)
	, m_dataEnd(other.m_dataEnd)
	, m_capacity(other.m_capacity)
	, m_size(other.m_size)
{


}

template<typename T>
inline FreeList<T>& FreeList<T>::operator=(const FreeList<T>& other) {
	m_data = (Element*)malloc(sizeof(Element) * other.capacity());
	m_dataEnd = m_data + (other.m_dataEnd - other.m_data);
	m_capacity = m_data + other.capacity();
	m_size = other.m_size;
	m_firstFree = other.m_firstFree;

	return *this;
}

template<typename T>
inline FreeList<T>::~FreeList() {
	for (int i = 0; i < dataSize(); ++i) {
		m_data[i].element.~T();
	}
	free(m_data);
}

template<typename T>
inline int FreeList<T>::size() const {
	return m_size;
}

template<typename T>
inline int FreeList<T>::capacity() const {
	return m_capacity - m_data;
}

template<typename T>
inline bool FreeList<T>::empty() const {
	return m_size == 0;
}

template<typename T>
inline T& FreeList<T>::front() {
	return *begin();
}

template<typename T>
inline const T& FreeList<T>::front() const {
	return *begin();
}

template<typename T>
inline T& FreeList<T>::back() {
	return *(end() - 1);
}

template<typename T>
inline const T& FreeList<T>::back() const {
	return *(end() - 1);
}

template<typename T>
inline typename FreeList<T>::iterator FreeList<T>::find(const T& t) {
	iterator itr = begin();
	for (iterator itrEnd = end(); itr != itrEnd; ++itr) {
		if (*itr == t) {
			break;
		}
	}
	return itr;
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::find(const T& t) const {
	const_iterator itr = begin();
	for (const_iterator itrEnd = end(); itr != itrEnd; ++itr) {
		if (*itr == t) {
			break;
		}
	}
	return itr;
}

template<typename T>
inline int FreeList<T>::push(const T& val) {
	return emplace(val);
}

template<typename T>
inline int FreeList<T>::push(T&& val) {
	return emplace(std::forward<T>(val));
}

template<typename T>
template<typename ...Ts>
inline int FreeList<T>::emplace(Ts && ...val) {
	if (m_data == nullptr) {
		m_data = (Element*)malloc(sizeof(Element) * 4);
		m_dataEnd = m_data;
		m_capacity = m_data + 4;
		initElement(0, 4);
	}
	int ind;
	// No empty space
	if (m_firstFree == -1) {
		// Run out of memory
		if (m_dataEnd == m_capacity) {
			int cap = capacity();
			Element* tmp = (Element*)realloc(m_data, sizeof(Element) * cap * 2);

			if (tmp == nullptr) {
				// No room for realloc, use malloc instead
				tmp = (Element*)malloc(sizeof(Element) * cap * 2);
				std::copy(m_data, m_capacity, tmp);
				free(m_data);
			}
			m_data = tmp;
			m_capacity = m_data + cap * 2;
			m_dataEnd = m_data + cap;
			initElement(m_dataEnd - m_data, m_capacity - m_data);
		}
		new (&m_dataEnd->element) T(val...);
		ind = m_dataEnd - m_data;
		m_dataEnd += 1;
	}
	else {
		m_data[m_firstFree].element.~T();
		int next = m_data[m_firstFree].next;
		new (&m_data[m_firstFree].element) T(val...);
		ind = m_firstFree;
		m_data[m_firstFree].removed = 0;
		m_firstFree = next;
	}

	++m_size;
	return ind;
}

template<typename T>
inline void FreeList<T>::reserve(int length) {
	if (capacity() >= length) {
		return;
	}
	int cap = capacity();
	int data = dataSize();
	Element* tmp = (Element*)realloc(m_data, sizeof(Element) * length);

	if (tmp == nullptr) {
		// No room for realloc, use malloc instead
		tmp = (Element*)malloc(sizeof(Element) * length);
		std::copy(m_data, m_capacity, tmp);
		free(m_data);
	}
	m_data = tmp;
	m_capacity = m_data + length;
	m_dataEnd = m_data + data;
	initElement(m_dataEnd - m_data, m_capacity - m_data);
}

template<typename T>
inline void FreeList<T>::remove(int pos) {
	removeElt(pos);
}

template<typename T>
inline void FreeList<T>::remove(const iterator& pos) {
	removeElt(pos.m_ind);
}

template<typename T>
inline void FreeList<T>::remove(const reverse_iterator& pos) {
	removeElt(pos.m_ind);
}

template<typename T>
inline T& FreeList<T>::operator[](int pos) {
	assert(pos >= 0 && pos < dataSize());
	return m_data[pos].element;
}

template<typename T>
inline const T& FreeList<T>::operator[](int pos) const {
	assert(pos >= 0 && pos < dataSize());
	return m_data[pos].element;
}

template<typename T>
inline T& FreeList<T>::at(int pos) {
	if (pos < 0 || pos >= capacity()) {
		throw std::out_of_range("FreeList subscript out of bound");
	}
	return m_data[pos].element;
}

template<typename T>
inline const T& FreeList<T>::at(int pos) const {
	if (pos < 0 || pos >= capacity()) {
		throw std::out_of_range("FreeList subscript out of bound");
	}
	return m_data[pos].element;;
}

template<typename T>
inline typename FreeList<T>::iterator FreeList<T>::iterAt(int pos) {
	return iterator(this, pos);
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::iterAt(int pos) const {
	return const_iterator(this, pos);
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::citerAt(int pos) const {
	return const_iterator(this, pos);
}

template<typename T>
inline typename FreeList<T>::reverse_iterator FreeList<T>::riterAt(int pos) {
	return reverse_iterator(this, pos);
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::riterAt(int pos) const {
	return const_reverse_iterator(this, pos);
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::criterAt(int pos) const {
	return const_reverse_iterator(this, pos);
}

template<typename T>
inline typename FreeList<T>::iterator FreeList<T>::begin() {
	if (!size()) {
		return iterator(this, 0);
	}
	iterator ret(this, 0);
	while (ret.m_ind < dataSize() && m_data[ret.m_ind].removed) {
		++ret.m_ind;
	}
	if (ret.m_ind >= dataSize()) {
		ret.m_ind = 0;
	}
	return ret;
}
template<typename T>
inline typename FreeList<T>::iterator FreeList<T>::end() {
	if (!size()) {
		return iterator(this, 0);
	}
	return iterator(this, dataSize());
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::begin() const {
	return cbegin();
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::end() const {
	return cend();
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::cbegin() const {
	if (!size()) {
		return const_iterator(this, 0);
	}
	const_iterator ret(this, 0);
	while (ret.m_ind < dataSize() && m_data[ret.m_ind].removed) {
		++ret.m_ind;
	}
	if (ret.m_ind >= dataSize()) {
		ret.m_ind = 0;
	}
	return ret;
}
template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::cend() const {
	if (!size()) {
		return const_iterator(this, 0);
	}
	return const_iterator(this, dataSize());
}

template<typename T>
inline typename FreeList<T>::reverse_iterator FreeList<T>::rbegin() {
	if (!size()) {
		return reverse_iterator(this, 0);
	}
	reverse_iterator ret(this, dataSize() - 1);
	while (ret.m_ind >= 0 && m_data[ret.m_ind].removed) {
		--ret.m_ind;
	}
	if (ret.m_ind < 0) {
		ret.m_ind = 0;
	}
	return ret;
}
template<typename T>
inline typename FreeList<T>::reverse_iterator FreeList<T>::rend() {
	if (!size()) {
		return reverse_iterator(this, 0);
	}
	return reverse_iterator(this, -1);
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::rbegin() const {
	return crbegin();
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::rend() const {
	return crend();
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::crbegin() const {
	if (!size()) {
		return const_reverse_iterator(this, 0);
	}
	const_reverse_iterator ret(this, dataSize() - 1);
	while (ret.m_ind >= 0 && m_data[ret.m_ind].removed) {
		--ret.m_ind;
	}
	if (ret.m_ind < 0) {
		ret.m_ind = 0;
	}
	return ret;
}
template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::crend() const {
	if (!size()) {
		return const_reverse_iterator(this, 0);
	}
	return const_reverse_iterator(this, -1);
}

template<typename T>
inline int FreeList<T>::dataSize() const {
	return m_dataEnd - m_data;
}

template<typename T>
inline void FreeList<T>::fillDefault() {
	for (auto _Begin = begin(), _End = end(); _Begin != _End; ++_Begin) {
		*_Begin = T();
	}
}

template<typename T>
inline void FreeList<T>::fillValue(const T& t) {
	for (auto _Begin = begin(), _End = end(); _Begin != _End; ++_Begin) {
		*_Begin = t;
	}
}

template<typename T>
inline void FreeList<T>::fillIter(const_iterator _start, const_iterator _end) {
	for (auto _Begin = begin(), _End = end(); _Begin != _End; ++_Begin) {
		*_Begin = *_start;
		++_start;
	}
}

template<typename T>
inline void FreeList<T>::fillIter(const_reverse_iterator _start, const_reverse_iterator _end) {
	for (auto _Begin = begin(), _End = end(); _Begin != _End; ++_Begin) {
		*_Begin = *_start;
		++_start;
	}
}

template<typename T>
inline void FreeList<T>::fillIter(const T* _start, const T* _end) {
	for (auto _Begin = begin(), _End = end(); _Begin != _End; ++_Begin) {
		*_Begin = *_start;
		++_start;
	}
}

template<typename T>
inline void FreeList<T>::initElement(int _start, int _end) {
	for (; _start < _end; ++_start) {
		m_data[_start].removed = 0;
		m_data[_start].next = -1;
	}
}

template<typename T>
inline void FreeList<T>::removeElt(int ind) {
	if (m_data == nullptr) {
		return;
	}
	--m_size;
	m_data[ind].next = m_firstFree;
	m_firstFree = ind;
	m_data[ind].removed = 1;
}

template<typename T>
inline FreeList<T>::iterator::iterator(FreeList<T>* list, int ind)
	: m_list(list), m_ind(ind) {

}
template<typename T>
inline T& FreeList<T>::iterator::operator*() {
	return m_list->m_data[m_ind].element;
}

template<typename T>
inline T* FreeList<T>::iterator::operator->() {
	return &m_list->m_data[m_ind].element;
}

template<typename T>
inline typename FreeList<T>::iterator FreeList<T>::iterator::operator+(int length) const {
	iterator ret(m_list, m_ind);
	while (length--) {
		++ret.m_ind;
		while (ret.m_ind < m_list->dataSize() && m_list->m_data[ret.m_ind].removed) {
			++ret.m_ind;
		}
	}
	return ret;
}

template<typename T>
inline typename FreeList<T>::iterator& FreeList<T>::iterator::operator+=(int length) {
	while (length--) {
		++m_ind;
		while (m_ind < m_list->dataSize() && m_list->m_data[m_ind].removed) {
			++m_ind;
		}
	}
	return *this;
}

template<typename T>
inline typename FreeList<T>::iterator FreeList<T>::iterator::operator-(int length) const {
	iterator ret(m_list, m_ind);
	while (length--) {
		--ret.m_ind;
		while (ret.m_ind >= 0 && m_list->m_data[ret.m_ind].removed) {
			--ret.m_ind;
		}
	}
	return ret;
}

template<typename T>
inline typename FreeList<T>::iterator& FreeList<T>::iterator::operator-=(int length) {
	while (length--) {
		--m_ind;
		while (m_ind >= 0 && m_list->m_data[m_ind].removed) {
			--m_ind;
		}
	}
	return *this;
}

template<typename T>
inline typename FreeList<T>::iterator& FreeList<T>::iterator::operator++() {
	operator+=(1);
	return *this;
}

template<typename T>
inline typename FreeList<T>::iterator FreeList<T>::iterator::operator++(int) {
	iterator ret(this);
	operator+=(1);
	return ret;
}

template<typename T>
inline typename FreeList<T>::iterator& FreeList<T>::iterator::operator--() {
	operator-=(1);
	return *this;
}

template<typename T>
inline typename FreeList<T>::iterator FreeList<T>::iterator::operator--(int) {
	iterator ret(this);
	operator-=(1);
	return ret;
}

template<typename T>
inline bool FreeList<T>::iterator::operator==(const typename FreeList<T>::iterator::iterator& other) const {
	return m_list == other.m_list && m_ind == other.m_ind;
}
template<typename T>
inline bool FreeList<T>::iterator::operator!=(const typename FreeList<T>::iterator::iterator& other) const {
	return m_list != other.m_list || m_ind != other.m_ind;
}
template<typename T>
inline int FreeList<T>::iterator::operator-(const typename FreeList<T>::iterator& other) const {
	if (m_list != other.m_list) {
		return 0;
	}
	int ret = 0;
	if (m_ind < other.m_ind) {
		for (int i = m_ind; i < other.m_ind; ++i) {
			ret += !m_list->m_data[i].removed;
		}
		return -ret;
	}
	for (int i = other.m_ind; i < m_ind; ++i) {
		ret += !m_list->m_data[i].removed;
	}
	return ret;
}

template<typename T>
inline FreeList<T>::const_iterator::const_iterator(const FreeList<T>* list, int ind)
	: m_list(list), m_ind(ind) {

}
template<typename T>
inline FreeList<T>::const_iterator::const_iterator(const iterator& iter)
	: m_list(iter.m_list), m_ind(iter.m_ind) {

}
template<typename T>
inline const T& FreeList<T>::const_iterator::operator*() const {
	return m_list->m_data[m_ind].element;
}

template<typename T>
inline const T* FreeList<T>::const_iterator::operator->() const {
	return &m_list->m_data[m_ind].element;
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::const_iterator::operator+(int length) const {
	const_iterator ret(m_list, m_ind);
	while (length--) {
		++ret.m_ind;
		while (ret.m_ind < m_list->dataSize() && m_list->m_data[ret.m_ind].removed) {
			++ret.m_ind;
		}
	}
	return ret;
}

template<typename T>
inline typename FreeList<T>::const_iterator& FreeList<T>::const_iterator::operator+=(int length) {
	while (length--) {
		++m_ind;
		while (m_ind < m_list->dataSize() && m_list->m_data[m_ind].removed) {
			++m_ind;
		}
	}
	return *this;
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::const_iterator::operator-(int length) const {
	const_iterator ret(m_list, m_ind);
	while (length--) {
		--ret.m_ind;
		while (ret.m_ind >= 0 && m_list->m_data[ret.m_ind].removed) {
			--ret.m_ind;
		}
	}
	return ret;
}

template<typename T>
inline typename FreeList<T>::const_iterator& FreeList<T>::const_iterator::operator-=(int length) {
	while (length--) {
		--m_ind;
		while (m_ind >= 0 && m_list->m_data[m_ind].removed) {
			--m_ind;
		}
	}
	return *this;
}

template<typename T>
inline typename FreeList<T>::const_iterator& FreeList<T>::const_iterator::operator++() {
	operator+=(1);
	return *this;
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::const_iterator::operator++(int) {
	const_iterator ret(this);
	operator+=(1);
	return ret;
}

template<typename T>
inline typename FreeList<T>::const_iterator& FreeList<T>::const_iterator::operator--() {
	operator-=(1);
	return *this;
}

template<typename T>
inline typename FreeList<T>::const_iterator FreeList<T>::const_iterator::operator--(int) {
	const_iterator ret(this);
	operator-=(1);
	return ret;
}

template<typename T>
inline bool FreeList<T>::const_iterator::operator==(const typename FreeList<T>::const_iterator::const_iterator& other) const {
	return m_list == other.m_list && m_ind == other.m_ind;
}
template<typename T>
inline bool FreeList<T>::const_iterator::operator!=(const typename FreeList<T>::const_iterator::const_iterator& other) const {
	return m_list != other.m_list || m_ind != other.m_ind;
}

template<typename T>
inline int FreeList<T>::const_iterator::operator-(const typename FreeList<T>::const_iterator& other) const {
	if (m_list != other.m_list) {
		return 0;
	}
	int ret = 0;
	if (m_ind < other.m_ind) {
		for (int i = m_ind; i < other.m_ind; ++i) {
			ret += !m_list->m_data[i].removed;
		}
		return -ret;
	}
	for (int i = other.m_ind; i < m_ind; ++i) {
		ret += !m_list->m_data[i].removed;
	}
	return ret;
}
template<typename T>
inline FreeList<T>::reverse_iterator::reverse_iterator(FreeList<T>* list, int ind)
	: m_list(list), m_ind(ind) {

}
template<typename T>
inline T& FreeList<T>::reverse_iterator::operator*() {
	return m_list->m_data[m_ind].element;
}

template<typename T>
inline T* FreeList<T>::reverse_iterator::operator->() {
	return &m_list->m_data[m_ind].element;
}

template<typename T>
inline typename FreeList<T>::reverse_iterator FreeList<T>::reverse_iterator::operator+(int length) const {
	reverse_iterator ret(m_list, m_ind);
	while (length--) {
		--ret.m_ind;
		while (ret.m_ind >= 0 && m_list->m_data[ret.m_ind].removed) {
			--ret.m_ind;
		}
	}
	return ret;
}

template<typename T>
inline typename FreeList<T>::reverse_iterator& FreeList<T>::reverse_iterator::operator+=(int length) {
	while (length--) {
		--m_ind;
		while (m_ind >= 0 && m_list->m_data[m_ind].removed) {
			--m_ind;
		}
	}
	return *this;
}

template<typename T>
inline typename FreeList<T>::reverse_iterator FreeList<T>::reverse_iterator::operator-(int length) const {
	reverse_iterator ret(m_list, m_ind);
	while (length--) {
		++ret.m_ind;
		while (ret.m_ind < m_list->dataSize() && m_list->m_data[ret.m_ind].removed) {
			++ret.m_ind;
		}
	}
	return ret;
}

template<typename T>
inline typename FreeList<T>::reverse_iterator& FreeList<T>::reverse_iterator::operator-=(int length) {
	while (length--) {
		--m_ind;
		while (m_ind >= 0 && m_list->m_data[m_ind].removed) {
			--m_ind;
		}
	}
	return *this;
}

template<typename T>
inline typename FreeList<T>::reverse_iterator& FreeList<T>::reverse_iterator::operator++() {
	operator+=(1);
	return *this;
}

template<typename T>
inline typename FreeList<T>::reverse_iterator FreeList<T>::reverse_iterator::operator++(int) {
	reverse_iterator ret(this);
	operator+=(1);
	return ret;
}

template<typename T>
inline typename FreeList<T>::reverse_iterator& FreeList<T>::reverse_iterator::operator--() {
	operator-=(1);
	return *this;
}

template<typename T>
inline typename FreeList<T>::reverse_iterator FreeList<T>::reverse_iterator::operator--(int) {
	reverse_iterator ret(this);
	operator-=(1);
	return ret;
}

template<typename T>
inline bool FreeList<T>::reverse_iterator::operator==(const typename FreeList<T>::reverse_iterator::reverse_iterator& other) const {
	return m_list == other.m_list && m_ind == other.m_ind;
}
template<typename T>
inline bool FreeList<T>::reverse_iterator::operator!=(const typename FreeList<T>::reverse_iterator::reverse_iterator& other) const {
	return m_list != other.m_list || m_ind != other.m_ind;
}

template<typename T>
inline int FreeList<T>::reverse_iterator::operator-(const typename FreeList<T>::reverse_iterator& other) const {
	if (m_list != other.m_list) {
		return 0;
	}
	int ret = 0;
	if (m_ind > other.m_ind) {
		for (int i = m_ind; i > other.m_ind; --i) {
			ret += !m_list->m_data[i].removed;
		}
		return -ret;
	}
	for (int i = other.m_ind; i > m_ind; --i) {
		ret += !m_list->m_data[i].removed;
	}
	return ret;
}
template<typename T>
inline FreeList<T>::const_reverse_iterator::const_reverse_iterator(const FreeList<T>* list, int ind)
	: m_list(list), m_ind(ind) {

}
template<typename T>
inline FreeList<T>::const_reverse_iterator::const_reverse_iterator(const reverse_iterator& iter)
	: m_list(iter.m_list), m_ind(iter.m_ind) {

}
template<typename T>
inline const T& FreeList<T>::const_reverse_iterator::operator*() const {
	return m_list->m_data[m_ind].element;
}

template<typename T>
inline const T* FreeList<T>::const_reverse_iterator::operator->() const {
	return &m_list->m_data[m_ind].element;
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::const_reverse_iterator::operator+(int length) const {
	const_reverse_iterator ret(m_list, m_ind);
	while (length--) {
		--ret.m_ind;
		while (ret.m_ind >= 0 && m_list->m_data[ret.m_ind].removed) {
			--ret.m_ind;
		}
	}
	return ret;
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator& FreeList<T>::const_reverse_iterator::operator+=(int length) {
	while (length--) {
		--m_ind;
		while (m_ind >= 0 && m_list->m_data[m_ind].removed) {
			--m_ind;
		}
	}
	return *this;
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::const_reverse_iterator::operator-(int length) const {
	const_reverse_iterator ret(m_list, m_ind);
	while (length--) {
		++ret.m_ind;
		while (ret.m_ind < m_list->dataSize() && m_list->m_data[ret.m_ind].removed) {
			++ret.m_ind;
		}
	}
	return ret;
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator& FreeList<T>::const_reverse_iterator::operator-=(int length) {
	while (length--) {
		++m_ind;
		while (m_ind < m_list->dataSize() && m_list->m_data[m_ind].removed) {
			++m_ind;
		}
	}
	return *this;
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator& FreeList<T>::const_reverse_iterator::operator++() {
	operator+=(1);
	return *this;
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::const_reverse_iterator::operator++(int) {
	const_reverse_iterator ret(this);
	operator+=(1);
	return ret;
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator& FreeList<T>::const_reverse_iterator::operator--() {
	operator-=(1);
	return *this;
}

template<typename T>
inline typename FreeList<T>::const_reverse_iterator FreeList<T>::const_reverse_iterator::operator--(int) {
	const_reverse_iterator ret(this);
	operator-=(1);
	return ret;
}

template<typename T>
inline bool FreeList<T>::const_reverse_iterator::operator==(const typename FreeList<T>::const_reverse_iterator::const_reverse_iterator& other) const {
	return m_list == other.m_list && m_ind == other.m_ind;
}
template<typename T>
inline bool FreeList<T>::const_reverse_iterator::operator!=(const typename FreeList<T>::const_reverse_iterator::const_reverse_iterator& other) const {
	return m_list != other.m_list || m_ind != other.m_ind;
}
template<typename T>
inline int FreeList<T>::const_reverse_iterator::operator-(const typename FreeList<T>::const_reverse_iterator& other) const {
	if (m_list != other.m_list) {
		return 0;
	}
	int ret = 0;
	if (m_ind > other.m_ind) {
		for (int i = m_ind; i > other.m_ind; --i) {
			ret += !m_list->m_data[i].removed;
		}
		return -ret;
	}
	for (int i = other.m_ind; i > m_ind; --i) {
		ret += !m_list->m_data[i].removed;
	}
	return ret;
}