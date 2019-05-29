#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include<memory>
using std::vector;
using std::string;

template <typename T>
class MyVector
{
public:


	MyVector() noexcept
	{
		p_keys = std::make_shared<vector<T>>();
		p_names = std::make_shared<vector<string>>();
	}

	MyVector& operator =(const MyVector&other) = delete;
	MyVector(const MyVector& other) = default;
	//copy assignment operator and copy ctor would act in the expected way due to shared_ptr: no issues here
	//but to keep behavior as in MyVector.h copy assignment operator is intentionally deleted

	void push_back(const T& obj, const string& name)
	{
		copy_names();

		p_keys->push_back(obj);
		p_names->push_back(name);
	}

	auto operator[](int index) const
	{
		if (index >= p_keys->size())
		{
			throw std::out_of_range("Index is out of range");
		}
		return std::make_pair((*p_keys)[index], (*p_names)[index]);
	}

	const T& operator[](const string& name) const
	{
		vector<string>::const_iterator iter = std::find(p_names->begin(), p_names->end(), name);
		if (iter == p_names->end())
		{
			throw std::invalid_argument(name + " is not found in the MyVector");
		}

		return (*p_keys)[iter - p_names->begin()];
	}

private:
	void copy_names()
	{
		if (p_names.use_count() == 1)
		{
			return;
		}

		p_names = std::make_shared<vector<string>>(*p_names);
		p_keys = std::make_shared<vector<T>>(*p_keys);
	}

private:
	//added copy-on-write for keys also
	std::shared_ptr<vector<T>> p_keys;

	// Use copy-on-write idiom for names for efficiency
	std::shared_ptr<vector<string>> p_names;
};
