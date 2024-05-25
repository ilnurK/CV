CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -Wextra
GCOV_FLAGS = --coverage -fprofile-arcs -ftest-coverage

TARG = 3DViewer
FULL_TARG = s21_$(TARG)

MODEL = ./Model
VIEW = ./$(TARG)
CONTROLLER = ./Controller

TESTS_FOLDER = ./tests
TEST_TARGET = $(FULL_TARG)_tests
DISTNAME = $(TARG)
DISTDIR = $(DISTNAME)_v2.0
SRC = $(wildcard $(MODEL)/*.cc)
OS = $(shell uname)

ifeq ($(OS),Linux)
    GCOV_FLAGS := -fprofile-arcs -ftest-coverage
    CHECK_LIBS := -lcheck -lm -lrt -lpthread -lsubunit
    LDLIBS := -lgtest_main -lgtest -lpthread
    GTEST_DIR := /usr/local
    GTEST_LIB_DIR := -L$(GTEST_DIR)/build/lib
    GTEST_INCLUDE_DIR := -isystem $(GTEST_DIR)/googletest/include
else
    TEST_FLAGS = -lgtest_main -lgtest -lpthread -lm
endif

QMAKE = qmake
# QMAKE = /Applications/Qt/6.6.0/macos/bin/qmake6

all: gcov_report


install: uninstall
	@echo "\033[0;32mInstalling...\033[0m"
	@mkdir -p $(VIEW)/tmp
ifeq ($(OS), Linux)
	@cd $(VIEW)/tmp && $(QMAKE) ../$(DISTNAME).pro > /dev/null 2>&1 && make > /dev/null 2>&1
	@sudo install $(VIEW)/tmp/$(DISTNAME) /usr/local/bin
else
	@cd $(VIEW)/tmp && $(QMAKE) ../$(DISTNAME).pro > /dev/null 2>&1 && make > /dev/null 2>&1
	@mkdir -p ./build
	@mv $(VIEW)/tmp/$(DISTNAME).app ./build/$(DISTNAME).app
	@open ./build
endif
	@rm -rf $(VIEW)/tmp .qmake.stash

dvi:
	@open Readme.md

dist:
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	@cp -rf $(MODEL) $(VIEW) $(CONTROLLER) $(TESTS_FOLDER) ./Makefile ./Readme.md $(DISTDIR)/
	@tar -cf $(DISTNAME).tar $(DISTDIR)
	@rm -rf $(DISTDIR)
	@echo "\033[0;32mCreated $(DISTNAME).tar\033[0m"

uninstall:
ifeq ($(OS), Linux)
	@sudo rm -f /usr/local/bin/$(DISTNAME)
else
	@rm -rf ./build
endif

test:
	@echo "\033[0;32mTesting\033[0m"
	@$(CC) $(CPPFLAGS) $(GTEST_INCLUDE_DIR) $(TEST_FLAGS) $(TESTS_FOLDER)/*.cc $(SRC) -o $(TESTS_FOLDER)/$(TEST_TARGET) $(LDLIBS) $(GTEST_LIB_DIR)
	@$(TESTS_FOLDER)/$(TEST_TARGET)

gcov_report:
	@echo "\033[0;32mCreating a report...\033[0m"
	@$(CC) $(CPPFLAGS) $(TEST_FLAGS) $(GCOV_FLAGS) $(TESTS_FOLDER)/*.cc $(SRC) $(GTEST_INCLUDE_DIR) -o $(TESTS_FOLDER)/$(TEST_TARGET) $(LDLIBS) $(GTEST_LIB_DIR)
	@$(TESTS_FOLDER)/$(TEST_TARGET)
ifeq ($(OS), Linux)
	@lcov -t "test" -o test.info -c -d . 
	@lcov --remove test.info '/usr/*' -o test.info
	@genhtml -o report/ test.info
else
	@lcov --no-external --ignore-errors mismatch --ignore-errors inconsistent -t "test" -o test.info -c -d . 
	@genhtml --ignore-errors inconsistent -o report/ test.info 
endif
	@open report/index.html
	@mkdir -p tmp/
	@mv test.info *.gcda *.gcno $(TESTS_FOLDER)/$(TEST_TARGET) tmp/  

clean:
	@echo "\033[0;32mCleaning...\033[0m"
	@rm -rf *.a *.o *.h.gch *.info *.gcda *.gcno *.gcov *.dSYM report
	@rm -rf $(TESTS_FOLDER)/$(TEST_TARGET) $(TESTS_FOLDER)/*.h.gch $(TESTS_FOLDER)/*.dSYM
	@rm -rf .clang-format
	@rm -rf ./$(DISTNAME).tar
	@rm -rf ./tmp $(TESTS_FOLDER)/*.g*

style:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -n $(MODEL)/*.cc $(MODEL)/*.h $(VIEW)/*.cc $(VIEW)/*.h $(CONTROLLER)/*.h
	@clang-format -i $(MODEL)/*.cc $(MODEL)/*.h $(VIEW)/*.cc $(VIEW)/*.h $(CONTROLLER)/*.h

leaks_check:
	@$(CC) $(CPPFLAGS) $(TEST_FLAGS) $(TESTS_FOLDER)/*.cc $(SRC) -o $(TESTS_FOLDER)/$(TEST_TARGET) > /dev/null 2>&1
	@echo "\033[0;32mChecking for memory leaks...\033[0m"
	@leaks -atExit -- $(TESTS_FOLDER)/$(TEST_TARGET)

valgrind:
	@valgrind --leak-check=full $(TESTS_FOLDER)/$(TEST_TARGET)