CC_CPP := g++
CPPFLAGS := -Wall -Werror -Wextra -Wconversion -Wsign-conversion -std=c++17
CC_C := gcc
CFLAGS := -Wall -Werror -Wextra -Wconversion -Wsign-conversion 
PREFIX := s21_
TARGET_NAME := snake


SRC_FOLDER_CPP := brick_game/snake
SRC_FOLDER_C := brick_game/tetris_c
TEST_FOLDER := tests
CLI_FOLDER := gui/cli
OBJ_FOLDER := obj
TEST_OBJ_FOLDER := test_obj
GCOV_FOLDER := gcov_obj
FRONT_FOLDER := gui/desktop/brick_game
BUILD_FOLDER := build


SRC_CPP := $(wildcard $(SRC_FOLDER_CPP)/$(PREFIX)*.cc) 
SRC_C := $(wildcard $(SRC_FOLDER_C)/$(PREFIX)*.c) 

CLI_CPP := $(wildcard $(CLI_FOLDER)/$(PREFIX)*.cc)
CLI_C := $(wildcard $(CLI_FOLDER)/$(PREFIX)*.c)

TEST_CPP := $(wildcard $(TEST_FOLDER)/$(PREFIX)*.cc)
TEST_C := $(wildcard $(TEST_FOLDER)/$(PREFIX)*.c)


OBJ_CPP := $(SRC_CPP:$(SRC_FOLDER_CPP)/%.cc=$(OBJ_FOLDER)/%.o) 
OBJ_C :=	$(SRC_C:$(SRC_FOLDER_C)/%.c=$(OBJ_FOLDER)/%.o)

CLI_OBJ_CPP := $(CLI_CPP:$(CLI_FOLDER)/%.cc=$(OBJ_FOLDER)/%.o)
CLI_OBJ_C := $(CLI_C:$(CLI_FOLDER)/%.c=$(OBJ_FOLDER)/%.o)

TEST_OBJ_CPP := $(TEST_CPP:$(TEST_FOLDER)/%.cc=$(TEST_OBJ_FOLDER)/%.o)
TEST_OBJ_C := $(TEST_C:$(TEST_FOLDER)/%.c=$(TEST_OBJ_FOLDER)/%.o)

GCOV_OBJ_CPP := $(SRC_CPP:$(SRC_FOLDER_CPP)/%.cc=$(GCOV_FOLDER)/%.o) 
GCOV_OBJ_C :=	$(SRC_C:$(SRC_FOLDER_C)/%.c=$(GCOV_FOLDER)/%.o)
GCOV_TEST_OBJ_CPP := $(TEST_CPP:$(TEST_FOLDER)/%.cc=$(GCOV_FOLDER)/%.o)
GCOV_TEST_OBJ_C := $(TEST_C:$(TEST_FOLDER)/%.c=$(GCOV_FOLDER)/%.o)


TARGET := $(PREFIX)$(TARGET_NAME)
VERSION := 1.0
DISTNAME := $(TARGET)_v$(VERSION)
TEST_TARGET := $(TARGET)_test


TEST_FLAGS := -lgtest_main -lgtest -lpthread

OS = $(shell uname)
ifeq ($(OS),Linux)
  GCOV_FLAGS := -fprofile-arcs -ftest-coverage
	CHECK_LIBS := -lcheck -lm -lrt -lpthread -lsubunit
  LDLIBS := -lgtest_main -lgtest -lpthread
	GTEST_DIR := /usr/local
	GTEST_LIB_DIR := -L$(GTEST_DIR)/build/lib
	GTEST_INCLUDE_DIR := -isystem $(GTEST_DIR)/googletest/include
	QMAKE := ~/Qt/6.6.1/gcc_64/bin/qmake6
else
	LDLIBS_MAC := -lgtest_main -lgtest -lpthread -lm --coverage -fprofile-arcs -ftest-coverage
  QMAKE := /Applications/Qt/6.6.0/macos/bin/qmake6
  # QMAKE := qmake
endif

EXISTING_DEPS = $(wildcard $(OBJ_CPP:.o=.d) $(OBJ_C:.o=.d) $(TEST_OBJ_CPP:.o=.d) $(CLI_OBJ_C:.o=.d) $(CLI_OBJ_CPP:.o=.d))


all: highscore_reset gcov_report

install:
	@echo "Installing..."
	@mkdir -p ./tmp
	@cd ./tmp && $(QMAKE) ../$(FRONT_FOLDER)/bg_src/$(TARGET_NAME).pro && make
ifeq ($(OS), Linux)
	@sudo install tmp/$(TARGET_NAME) /usr/local/bin
else
	@mv ./tmp/$(TARGET_NAME).app /Applications
endif
	@rm -rf ./tmp .qmake.stash

uninstall:
ifeq ($(OS), Linux)
	@sudo rm -rf /usr/local/bin/$(TARGET_NAME)
else
	@rm -rf /Applications/$(TARGET_NAME).app
endif
  

dvi:
	open ../README.md

dist:
	@mkdir -p $(DISTNAME)/
	@cp -rf brick_game/ gui/ tests/ logs/ ./Makefile ../README.md $(DISTNAME)/
	@tar -cf $(DISTNAME).tar $(DISTNAME)
	@rm -rf $(DISTNAME)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER_CPP)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CPPFLAGS) -MMD -c $< -o $@

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER_C)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_C) $(CFLAGS) -MMD -c $< -o $@

$(TEST_OBJ_FOLDER)/%.o: $(TEST_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CPPFLAGS) $(GTEST_INCLUDE_DIR) -MMD -c $< -o $@ $(GTEST_LIB_DIR)

$(TEST_OBJ_FOLDER)/%.o: $(TEST_FOLDER)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_C) $(CFLAGS) $(GTEST_INCLUDE_DIR) -MMD -c $< -o $@ $(GTEST_LIB_DIR)

include $(EXISTING_DEPS)

tests: $(OBJ_CPP) $(OBJ_C) $(TEST_OBJ_CPP) $(TEST_OBJ_C)
	@$(CC_CPP) $(OBJ_CPP) $(OBJ_C) $(TEST_OBJ_CPP) $(TEST_OBJ_C) -o $(TEST_TARGET) $(TEST_FLAGS);./$(TEST_TARGET)


$(GCOV_FOLDER)/%.o: $(SRC_FOLDER_CPP)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
ifeq ($(OS), Linux)
	@$(CC_CPP) $(CPPFLAGS) $(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) --coverage -MMD -c $< -o $@ $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
else
	@$(CC_CPP) $(CPPFLAGS) --coverage -MMD -c $< -o $@
endif

$(GCOV_FOLDER)/%.o: $(SRC_FOLDER_C)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
ifeq ($(OS), Linux)
	@$(CC_C) $(CFLAGS) $(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) --coverage -MMD -c $< -o $@ $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
else
	@$(CC_C) $(CFLAGS) --coverage -MMD -c $< -o $@
endif

$(GCOV_FOLDER)/%.o: $(TEST_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
ifeq ($(OS), Linux)
	@$(CC_CPP) $(CPPFLAGS) $(GCOV_FLAGS)  -pthread $(GTEST_INCLUDE_DIR) --coverage -MMD -c $< -o $@ $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
else
	@$(CC_CPP) $(CPPFLAGS) --coverage -MMD -c $< -o $@
endif

$(GCOV_FOLDER)/%.o: $(TEST_FOLDER)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
ifeq ($(OS), Linux)
	@$(CC_C) $(CFLAGS) $(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) --coverage -MMD -c $< -o $@ $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
else
	@$(CC_C) $(CFLAGS) --coverage -MMD -c $< -o $@
endif

gcov_report: $(GCOV_OBJ_CPP) $(GCOV_OBJ_C) $(GCOV_TEST_OBJ_CPP) $(GCOV_TEST_OBJ_C)
	@echo "Creating a report..."
ifeq ($(OS), Linux)
	@$(CC_CPP)  $(GCOV_FOLDER)/*.o $(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) --coverage -o $(TEST_TARGET) $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS); ./$(TEST_TARGET)
	@lcov -t "test" -o test.info -c -d $(GCOV_FOLDER)/
	@lcov --remove test.info '/usr/*' -o filtered_coverage.info
	@genhtml -o report/ filtered_coverage.info
else
	@$(CC_CPP) $(CPPFLAGS) $(LDLIBS_MAC) $(GCOV_FOLDER)/*.o -o $(TEST_TARGET); ./$(TEST_TARGET)
	@lcov --no-external --ignore-errors mismatch --ignore-errors inconsistent -t "test" -o test.info -c -d . > /dev/null 2>&1
	@genhtml --ignore-errors inconsistent -o report/ test.info > /dev/null 2>&1
endif
	@mv *.info $(GCOV_FOLDER)
	@open report/index.html

valgrind:
	@valgrind --leak-check=full --track-origins=yes ./$(TEST_TARGET)

cli: linking_cli

linking_cli: $(OBJ_CPP) $(OBJ_C) $(CLI_OBJ_C) $(CLI_OBJ_CPP)
	@echo "Linking..."
	@$(CC_CPP) $(OBJ_CPP) $(OBJ_C) $(CLI_OBJ_C) $(CLI_OBJ_CPP) -lncurses -o $(TARGET)
	@./$(TARGET)

$(OBJ_FOLDER)/%.o: $(CLI_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CPPFLAGS) -lncurses -MMD -c $< -o $@

$(OBJ_FOLDER)/%.o: $(CLI_FOLDER)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_C) $(CFLAGS) -lncurses -MMD -c $< -o $@

style:
	@cp ../materials/linters/.clang-format .clang-format
	@find . \( -name "*.cc" -o -name "*.h" -o -name "*.c" \) -exec clang-format -n {} +
	@find . \( -name "*.cc" -o -name "*.h" -o -name "*.c" \) -exec clang-format -i {} +

clean:
	@echo "Cleaning up..."
	@rm -rf *.out *.o *.info $(OBJ_FOLDER) $(TEST_OBJ_FOLDER) $(TEST_TARGET)
	@rm -rf tmp/ report/ $(TARGET) ./$(DISTNAME).tar *.gcno $(GCOV_FOLDER)

highscore_reset:
	@echo > logs/snake_score.log
	@echo > logs/tetris_score.log
