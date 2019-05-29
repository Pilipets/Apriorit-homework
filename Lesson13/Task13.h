#pragma once
#include<vector>
#include<stack>
#include<ostream>
using std::vector;

vector<int> prevSmaller(const vector<int> &arr); 
//более правильным показалось добавить в сигнатуру модификатор доступа const перед arr

std::ostream& operator <<(std::ostream& os, const vector<int>& arr);
