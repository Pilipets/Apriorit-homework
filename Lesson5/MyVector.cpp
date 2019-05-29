#include "MyVector.h"
using namespace MineSTL;
template class MyVector<int>;

template<class T> MyVector<T>::MyVector() noexcept:
	_size(0), _capacity(2){
	_arr = new T[_capacity];
}

template<class T> MyVector<T>::~MyVector() {
	delete[] _arr;
}

template<class T> 
MyVector<T>& MyVector<T>::operator =(const MyVector<T>& other) {
	if (this != &other) {
		this->copyFrom(other);
	}
	return *this;
}

template<class T> 
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) {
	if (this != &other) {
		this->moveFrom(other);
	}
	return *this;
}

template<class T> void MyVector<T>::push_back(const T &val)
{
	if (_size == _capacity) {
		this->extendCapacity();
	}
	_arr[_size] = val;
	_size += 1;
}

template<class T> void MyVector<T>::push_back(T && val) {
	if (_size == _capacity) {
		this->extendCapacity();
	}
	_arr[_size] = std::move(val);
	_size += 1;
}

template<class T> inline void MyVector<T>::copyFrom(const MyVector<T> &src) {
	_size = src._size, _capacity = src._capacity;
	delete[] _arr;
	_arr = new T[_capacity];

	memcpy(_arr, src._arr, _size * sizeof(T));
}

template<class T> inline void MyVector<T>::moveFrom(MyVector<T>& src) {
	_capacity = src._capacity, _size = src._size;
	delete[] _arr;
	_arr = src._arr;

	src._capacity = 2, src._size = 0;
	src._arr = new T[_capacity];
}

template<class T> inline void MyVector<T>::extendCapacity()
{
	_capacity <<= 2;
	T *new_arr = new T[_capacity];
	for (size_t i = 0; i < _size; ++i)
		new_arr[i] = std::move(_arr[i]);

	delete[] _arr;
	_arr = new_arr;
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& other): _arr(nullptr)
{
	this->copyFrom(other);
}

template<class T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept: _arr(nullptr)
{
	this->moveFrom(other);
}