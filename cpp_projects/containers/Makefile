CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra
TEST_FLAGS = -lgtest_main -lgtest -lpthread
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

TARGET = containers
FULL_TARGET = s21_$(TARGET)

TESTS_FOLDER = ./tests
TEST_TARGET = $(FULL_TARGET)_test

CHECK_LIBS = -lcheck -lm -lrt -lpthread -lsubunit
LDLIBS = -lgtest_main -lgtest -lpthread

OS = $(shell uname)
ifeq ($(OS),Linux)
	GTEST_DIR = /usr/local
	GTEST_LIB_DIR = -L$(GTEST_DIR)/build/lib
	GTEST_INCLUDE_DIR = -isystem $(GTEST_DIR)/googletest/include
else
	GTEST_LIB_DIR = 
	GTEST_INCLUDE_DIR = 
endif

all: test

test:
	@$(CC) $(CPPFLAGS) $(GTEST_INCLUDE_DIR) $(TESTS_FOLDER)/*.cc -o $(TESTS_FOLDER)/$(TEST_TARGET) $(GTEST_LIB_DIR) $(TEST_FLAGS)
	@$(TESTS_FOLDER)/$(TEST_TARGET)

gcov_report:
	@echo "Creating a report..."
ifeq ($(OS),Linux)
	@$(CC) $(CPPFLAGS) $(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) --coverage $(TESTS_FOLDER)/*.cc -o $(TEST_TARGET) $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
	@./$(TEST_TARGET)
	@lcov -t "test" -o test.info -c -d .
	@lcov --remove test.info '/usr/*' -o filtered_coverage.info
	@genhtml -o report/ filtered_coverage.info
	@open report/index.html
else
	@$(CC) -pthread $(CPPFLAGS) $(GTEST_INCLUDE_DIR) --coverage $(TESTS_FOLDER)/*.cc $(TEST_FLAGS) -o $(TEST_TARGET) $(GTEST_LIB_DIR)
	@./$(TEST_TARGET) > /dev/null 2>&1
	@lcov --no-external --ignore-errors mismatch --ignore-errors inconsistent -t "test" -o test.info -c -d . > /dev/null 2>&1
	@genhtml --ignore-errors inconsistent -o report/ test.info > /dev/null 2>&1
	@open report/index.html
endif
	@mkdir -p tmp/
	@mv test.info *.gcda *.gcno $(TEST_TARGET) tmp/  

clean:
	@echo "Cleaning..."
	@rm -rf *.a *.o *.h.gch *.info *.gcda *.gcno *.gcov
	@rm -rf $(TESTS_FOLDER)/$(TEST_TARGET)
	@rm -rf ./report
	@rm -rf ./tmp
	@rm -rf .clang-format

leaks_check:
	@$(CC) $(CPPFLAGS) $(GTEST_INCLUDE_DIR) $(TESTS_FOLDER)/*.cc $(TEST_FLAGS) -o $(TESTS_FOLDER)/$(TEST_TARGET) $(GTEST_LIB_DIR)
	@echo "Checking for memory leaks..."
	@leaks -atExit -- $(TESTS_FOLDER)/$(TEST_TARGET) | grep LEAK: || (echo "\033[0;32mno leaks\033[0m")

valgrind:
	@valgrind --leak-check=full ./$(FULL_TARGET)

format_style:
	@cp ../materials/linters/.clang-format .clang-format
	@find . \( -name "*.cc" -o -name "*.h" -o -name "*.tpp" \) -exec clang-format -i {} +

check_style:
	@cp ../materials/linters/.clang-format .clang-format
	@find . \( -name "*.cc" -o -name "*.h" -o -name "*.tpp" \) -exec clang-format -n {} +

install_gtest:
	git clone https://github.com/google/googletest.git && \
	cd googletest && \
	mkdir build && \
	cd build && \
	cmake .. && \
	make && \
	sudo make install && \
	echo "export GTEST_ROOT=/usr/local/gtest" >> ~/.bash_profile && \
	source ~/.bash_profile && \
	cd ../../ && \
	sudo cp -r ./googletest/googletest/include/gtest /usr/local/include/ && \
	sudo cp ./googletest/build/lib/*.a /usr/local/lib/
