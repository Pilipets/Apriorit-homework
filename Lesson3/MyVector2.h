#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include<memory>
using std::vector;
using std::string;

template <typename T>
class MyVector : public std::vector<T>
{
public:
	MyVector()
	{
		p_names = std::make_shared<vector<string>>();
	}

	MyVector(const MyVector& other) = default;
	//default copy ctor would act in the expected way due to shared_ptr: no issues here

	MyVector& operator =(const MyVector&other) = delete;
	//the problem with the default copy assignment operator is memory leakage in base vector class
	//so to keep behaviour like in MyVector.h we will just delete it
	
	void push_back(const T& obj, const string& name)
	{
		copy_names();

		vector<T>::push_back(obj);
		p_names->push_back(name);
	}

	std::pair<const T&, const string&> operator[](int index) const
	{
		if (index >= vector<T>::size())
		{
			throw std::out_of_range("Index is out of range");
		}
		return std::pair<const T&, const std::string&>(std::vector<T>::operator[](index), (*p_names)[index]);
	}

	const T& operator[](const string& name) const
	{
		vector<string>::const_iterator iter = std::find(p_names->begin(), p_names->end(), name);
		if (iter == p_names->end())
		{
			throw std::invalid_argument(name + " is not found in the MyVector");
		}

		return vector<T>::operator[](iter - p_names->begin());
	}

private:
	void copy_names()
	{
		if (p_names.use_count() == 1)
		{
			return;
		}

		p_names = std::make_shared<vector<string>>(*p_names);
	}

private:
	// Use copy-on-write idiom for names for efficiency
	std::shared_ptr<vector<string>> p_names;
};
