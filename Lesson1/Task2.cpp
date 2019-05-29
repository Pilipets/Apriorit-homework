/*Find the missing number in a file, containing 2 billion integers 
Using 1GB of memory.

So let's describe an algorithm
Under the terms each integer takes 4 bytes of memory
2 billion integers would take: 4 bytes * (2 * 10^9) = 8 * 10^9 bytes = 8GB

The idea is to create kinda bitset, where each bit would represent presence of the 
corresponding number in given file. Such array could be std::vector<bool> or std::bitset.
vector<bool> would actually occupy more place for effective push_back operations, so
more efficient would be to have std::bitset.

Memory required to store 2 billion booleans = 1bit *(2*10^9)= 2Gbit = 0.25 GB
We have a boolean array, load numbers from the file in a loop and fill the boolean array by
marking corresponding index to given number with 1.
After reaching the file's end all integers have been processed and we make one pass through
boolean array and find first 0 in it. Which mean that integer is absent.


Each integer takes 4-bytes
1) last bit for sign which implies 2^31 = 2147483648 ~ 2 * 10^9 = 2 billion
2) 2^32 = 4294967296 ~ 4*10^9 = 4 billion

In provided algorithm there would be only one passing through given file. 
The only problems are
1)It could be integers greater than 2^31 which implies reading to long long and having boolean array
with those indices also
2)It could be negative integers
Let's try to handle that
We would maintain one array for 4 bytes positive numbers of size 4e9 bits = 0.5GB [0...2^32-1]
and another one with size 2e9 bits = 0.25GB [-2^31-1...0]
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<bitset>
#include <stdio.h>
const size_t P_SIZE = 0xFFFFFFFF;
const size_t N_SIZE = 0x7FFFFFFF;
using std::bitset;

long long findMissing()
{
	//bitset<P_SIZE> p_num_presence;
	//bitset<N_SIZE> n_num_presence;
	bitset<1000> p_num_presence;
	bitset<1000> n_num_presence;

	FILE* fin = fopen("Data.txt", "r");
	if (fin != nullptr) {
		long long tmp;
		while (!feof(fin)) {
			fscanf(fin, "%lld", &tmp);
			if (tmp > 0)
				p_num_presence.set(tmp);
			else if (tmp < 0)
				n_num_presence.set(-static_cast<int>(tmp));
			else
				p_num_presence.set(0), n_num_presence.set(0);
		}
	}
	fclose(fin);

	for (size_t i = 0; i < p_num_presence.size(); ++i)
		if (!p_num_presence[i])
			return i;
	for(size_t i = 0; i < n_num_presence.size(); ++i)
		if (!n_num_presence[i])
			return -static_cast<int>(i);
}
int main() {
	std::cout << findMissing() << "\n";
	system("pause");
	return 0;
}

