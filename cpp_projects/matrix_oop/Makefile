CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra

TARGET = matrix_oop
FULL_TARGET = s21_$(TARGET)
TEST_TARGET = $(FULL_TARGET)_tests
LIB = $(FULL_TARGET).a

DIR_SRCS = .
DIR_OBJS = obj
DIR_TESTS = tests

SRCS = $(DIR_SRCS)/*.cpp
TEST_SRCS = $(DIR_TESTS)/*.cpp
OBJS = $(DIR_OBJS)/*.o

GTEST_DIR = /usr/local
LDLIBS = -lgtest_main -lgtest -lpthread

GCOV = -fprofile-arcs -ftest-coverage
OS = $(shell uname)
ifeq ($(OS),Linux)
	GTEST_LIB_DIR = -L$(GTEST_DIR)/build/lib
	GTEST_INCLUDE_DIR = -isystem $(GTEST_DIR)/googletest/include
	CHECK_LIBS = -lcheck -lm -lrt -lpthread -lsubunit
else
	CHECK_LIBS = -lcheck -lm -lpthread
	GTEST_LIB_DIR = 
	GTEST_INCLUDE_DIR = 
endif

#PRIMARY

all: $(LIB) test

$(LIB): objects
	ar rcs $(LIB) $(OBJS)
	ranlib $(LIB)

objects:
	test -d $(DIR_OBJS) || mkdir -p $(DIR_OBJS)
	$(CC) $(CPPFLAGS) $(SRCS) -c 
	mv *.o $(DIR_OBJS)/

test_objects:
	test -d $(DIR_TESTS) || mkdir -p $(DIR_TESTS)
	$(CC) $(CPPFLAGS) -pthread $(TEST_SRCS) -c
	mv *.o $(DIR_OBJS)/

test: objects test_objects
	$(CC) -pthread $(GTEST_INCLUDE_DIR) $(OBJS) -o $(TEST_TARGET) $(GTEST_LIB_DIR) $(LDLIBS)
	./$(TEST_TARGET)

#SECONDARY

clean:
	rm -rf *.a *.o *.out *.g* *.info
	rm -rf $(FULL_TARGET)
	rm -rf $(DIR_OBJS)
	rm -rf $(TEST_TARGET)
	rm -rf .clang-format
	rm -rf tmp/ report/

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(DIR_SRCS)/*.cpp $(DIR_SRCS)/*.h
	clang-format -i $(DIR_TESTS)/*.cpp

build: objects
	g++ $(OBJS) -o $(FULL_TARGET); ./$(FULL_TARGET)

gtest_inst:
	sudo apt-get install cmake
	git clone https://github.com/google/googletest.git
	cd googletest
	mkdir build
	cd build
	cmake ..
	make
	sudo make install
	ls /usr/local/lib/libgtest.a

gtest_mac:
	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
	brew install googletest

gcov_report:
	$(CC) $(GCOV) -pthread $(GTEST_INCLUDE_DIR) $(SRCS) $(TEST_SRCS) -o $(TEST_TARGET) $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
	./$(TEST_TARGET)
	gcov -p -r /usr/local/include/*
	lcov -t "test" -o test.info -c -d .
ifeq ($(OS),Darwin)
	genhtml --ignore-errors unmapped -o report/ test.info
	open ./report/index.html
else
	genhtml -o report/ test.info
	open report/index.html
endif
	mkdir -p tmp/
	mv test.info *.gcda *.gcno tmp/

