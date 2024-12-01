#pragma once
#include <initializer_list>
#include <type_traits>
#include <assert.h>

#include "Debug/Log.hpp"

template<typename T,
	class = std::enable_if_t<
	std::is_trivially_copyable_v<T>&&
	std::is_trivially_move_constructible_v<T>, void>>
class FreeList;

template<typename T>
class FreeList<T> {
private:
	struct Element {
		union {
			T element;
			int next = -1;
		};
		bool removed = 0;
	};
public:
	class iterator;
	class reverse_iterator;
	class const_iterator;
	class const_reverse_iterator;
public:
	FreeList();
	FreeList(int n);
	FreeList(int n, const T& t);
	FreeList(const std::initializer_list<T>& list);
	FreeList(const const_iterator& _start, const const_iterator& _end);
	FreeList(const const_reverse_iterator& _start, const const_reverse_iterator& _end);

	FreeList(const FreeList<T>& other);
	FreeList(FreeList<T>&& other);
	FreeList<T>& operator=(const FreeList<T>& other);

	~FreeList();

	int size() const;
	int capacity() const;
	bool empty() const;
	void clear();

	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

	iterator find(const T& t);
	const_iterator find(const T& t) const;

	int push(const T& val);
	int push(T&& val);
	
	template<typename ... Ts>
	int emplace(Ts&&... val);

	void reserve(int length);

	void remove(int pos);
	void remove(const iterator& pos);
	void remove(const reverse_iterator& pos);

	T& operator[](int pos);
	const T& operator[](int pos) const;

	T& at(int pos);
	const T& at(int pos) const;

	iterator iterAt(int pos);
	const_iterator citerAt(int pos) const;
	const_iterator iterAt(int pos) const;
	reverse_iterator riterAt(int pos);
	const_reverse_iterator criterAt(int pos) const;
	const_reverse_iterator riterAt(int pos) const;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;
private:
	int m_size = 0;
	int m_firstFree = -1;
	Element* m_data = nullptr;
	Element* m_dataEnd = nullptr;
	Element* m_capacity = nullptr;

	int dataSize() const;

	void fillDefault();
	void fillValue(const T& t);
	void fillIter(const_iterator _start, const_iterator _end);
	void fillIter(const_reverse_iterator _start, const_reverse_iterator _end);
	void fillIter(const T* _start, const T* _end);
	void initElement(int _start, int _end);

	void removeElt(int ind);
public:
	class iterator {
		friend class FreeList<T>;
	public:
		iterator() = default;
		iterator(FreeList<T>* list, int ind);

		T& operator*();
		T* operator->();

		iterator operator+(int length) const;
		iterator& operator+=(int length);
		iterator operator-(int length) const;
		iterator& operator-=(int length);

		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);

		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;

		int operator-(const iterator& other) const;
	private:
		FreeList<T>* m_list;
		int m_ind;
	};
	class const_iterator {
		friend class FreeList<T>;
	public:
		const_iterator() = default;
		const_iterator(const FreeList<T>* list, int ind);
		const_iterator(const iterator& iter);

		const T& operator*() const;
		const T* operator->() const;

		const_iterator operator+(int length) const;
		const_iterator& operator+=(int length);
		const_iterator operator-(int length) const;
		const_iterator& operator-=(int length);

		const_iterator& operator++();
		const_iterator operator++(int);
		const_iterator& operator--();
		const_iterator operator--(int);

		bool operator==(const const_iterator& other) const;
		bool operator!=(const const_iterator& other) const;

		int operator-(const const_iterator& other) const;
	private:
		const FreeList<T>* m_list;
		int m_ind;
	};
	class reverse_iterator {
		friend class FreeList<T>;
	public:
		reverse_iterator() = default;
		reverse_iterator(FreeList<T>* list, int ind);

		T& operator*();
		T* operator->();

		reverse_iterator operator+(int length) const;
		reverse_iterator& operator+=(int length);
		reverse_iterator operator-(int length) const;
		reverse_iterator& operator-=(int length);

		reverse_iterator& operator++();
		reverse_iterator operator++(int);
		reverse_iterator& operator--();
		reverse_iterator operator--(int);

		bool operator==(const reverse_iterator& other) const;
		bool operator!=(const reverse_iterator& other) const;

		int operator-(const reverse_iterator& other) const;
	private:
		FreeList<T>* m_list;
		int m_ind;
	};
	class const_reverse_iterator {
		friend class FreeList<T>;
	public:
		const_reverse_iterator() = default;
		const_reverse_iterator(const FreeList<T>* list, int ind);
		const_reverse_iterator(const reverse_iterator& iter);
		const T& operator*() const;
		const T* operator->() const;

		const_reverse_iterator operator+(int length) const;
		const_reverse_iterator& operator+=(int length);
		const_reverse_iterator operator-(int length) const;
		const_reverse_iterator& operator-=(int length);

		const_reverse_iterator& operator++();
		const_reverse_iterator operator++(int);
		const_reverse_iterator& operator--();
		const_reverse_iterator operator--(int);

		bool operator==(const const_reverse_iterator& other) const;
		bool operator!=(const const_reverse_iterator& other) const;

		int operator-(const const_reverse_iterator& other) const;
	private:
		const FreeList<T>* m_list;
		int m_ind;
	};
};

#include "FreeList.inl"