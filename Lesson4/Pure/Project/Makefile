ifndef GTEST_DIR
GTEST_DIR = ../googletest/googletest
endif

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -std=gnu++11 -Wall -Wextra -pthread

TESTS = sorting_gTest

SOURCE_DIR = project
LIB_DIR = project
TEST_DIR = test


GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : $(TESTS)

clean :
	rm -fr $(TESTS) gtest.a gtest_main.a *.o


GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)


gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.
Sorting.o : $(SOURCE_DIR)/Sorting.cpp $(SOURCE_DIR)/Sorting.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SOURCE_DIR)/Sorting.cpp

sorting_gTest.o : $(TEST_DIR)/sorting_gTest.cpp $(SOURCE_DIR)/Sorting.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) -I$(SOURCE_DIR) $(CXXFLAGS) -c $(TEST_DIR)/sorting_gTest.cpp

sorting_gTest : Sorting.o sorting_gTest.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ -L. -L$(LIB_DIR)
	./$(TESTS)
