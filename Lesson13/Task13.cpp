#include "Task13.h"

vector<int> prevSmaller(const vector<int>& arr)
{
	size_t n = arr.size();
	std::stack<int> s;
	vector<int> res(n);

	for (size_t i = 0; i < n; ++i) {
		while (!s.empty() && arr[s.top()] >= arr[i])
			s.pop();
		res[i] = s.empty() ? -1 : s.top();

		s.push(i);
	}
	return res;
}

std::ostream& operator <<(std::ostream& os, const vector<int>& arr)
{
	os << "[";
	for (size_t i = 0; i < arr.size() - 1; ++i)
		os << arr[i] << ", ";
	os << arr.back() << "]";
	return os;
}
