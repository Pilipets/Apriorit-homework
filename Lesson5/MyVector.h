#pragma once
#include<iostream>
#include<ostream>
namespace MineSTL {
	template<class T>
	class MyVector {
	private:
		size_t _capacity, _size;
		T* _arr;
	public:
		//Constructor, Destructor, Assignment,
		MyVector() noexcept;
		MyVector(const MyVector<T> &);
		MyVector(MyVector<T> &&) noexcept;
		~MyVector();
		MyVector<T>& operator = (const MyVector<T> &);
		MyVector<T>& operator = (MyVector<T> &&);

		//Modify
		void push_back(const T &);
		void push_back(T &&);

		//Print
		friend std::ostream& operator <<(std::ostream& os, const MyVector& obj){
			os << "[";
			if (obj._size) {
				for (int i = 0; i < obj._size - 1; ++i)
					os << obj._arr[i] << ", ";

				os << obj._arr[obj._size - 1];
			}
			os << "]";
			return os;
		}
	private:
		//copy,move helper functions
		inline void copyFrom(const MyVector<T>& src);
		inline void moveFrom(MyVector<T>& src);
		inline void extendCapacity();
	};
}


