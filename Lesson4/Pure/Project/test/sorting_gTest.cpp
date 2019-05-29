#include <gtest/gtest.h>
#include "Sorting.h"
#include <algorithm>

TEST(BubbleSortTests, EmptyArray) {
    std::vector<int> v;
    BubbleSort(v);
    
    EXPECT_EQ(v.size(),0);
}
TEST(BubbleSortTests, OneElementArray) {
    std::vector<int> v1 = {1};
    std::vector<int> v2(v1);
    BubbleSort(v1);

    ASSERT_EQ(v1.size(), v2.size());
    EXPECT_EQ(v1[0],v2[0]);
}
TEST(BubbleSortTests, SortedArray) {
    std::vector<int> v1 = {1,2,3,4,5};
    std::vector<int> v2 = v1;
    BubbleSort(v1);

    ASSERT_EQ(v1.size(), v2.size());
    for(size_t i = 0; i < 5; ++i)
    	EXPECT_EQ(v1[i],v2[i]);
}
TEST(BubbleSortTests, FinishedEarliedbyFlag) {
    std::vector<int> v1 = {-3,2,0,-1};
    std::vector<int> v2(v1);

    BubbleSort(v1);
    std::sort(v2.begin(), v2.end());

    ASSERT_EQ(v1.size(), v2.size());
    for(size_t i = 0; i < v1.size(); ++i)
    {
    	EXPECT_EQ(v1[i],v2[i]);
    }
}

TEST(BubbleSortTests, NormalTest) {
	std::vector<int> v1,v2;
    for(size_t i = 0; i < 30; ++i)
    {
    	int tmp = rand();
    	v1.push_back(tmp);
    	v2.push_back(tmp);
    }
    BubbleSort(v1);
    std::sort(v2.begin(), v2.end());

    ASSERT_EQ(v1.size(), v2.size());
    for(size_t i = 0; i < v1.size(); ++i)
    {
    	EXPECT_EQ(v1[i],v2[i]);
    }
}

TEST(BubbleSortTests, HugeTest) {
	std::vector<int> v1,v2;
    for(size_t i = 0; i < 3000; ++i)
    {
    	int tmp = rand();
    	v1.push_back(tmp);
    	v2.push_back(tmp);
    }
    BubbleSort(v1);
    std::sort(v2.begin(), v2.end());

    ASSERT_EQ(v1.size(), v2.size());
    for(size_t i = 0; i < v1.size(); ++i)
    {
    	EXPECT_EQ(v1[i],v2[i]);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}