PYTHON :=      python3
CC_CPP :=      g++
CC_C :=        gcc
CPPFLAGS :=    -Wall -Werror -Wextra -std=c++17
CFLAGS :=      -Wall -Werror -Wextra
PREFIX :=      s21_
TARGET_NAME := brick_game
TARGET :=      $(PREFIX)$(TARGET_NAME)
TEST_TARGET := $(TARGET)_test
SERVER :=      $(TARGET)s_server
PORT :=        8080

VERSION :=  1.0
DISTNAME := $(TARGET)_v$(VERSION)

#  FOLDERS
## SOURCE FOLDERS
PYTHON_FOLDER := race
CPP_FOLDER :=    snake
C_FOLDER :=      tetris

### MODEL FOLDERS
MODELS_FOLDER :=       $(TARGET_NAME)
PYTHON_MODEL_FOLDER := $(MODELS_FOLDER)/$(PYTHON_FOLDER)
CPP_MODEL_FOLDER :=    $(MODELS_FOLDER)/$(CPP_FOLDER)
C_MODEL_FOLDER :=      $(MODELS_FOLDER)/$(C_FOLDER)
C_LIBRARY_FOLDER :=    $(MODELS_FOLDER)
SERVER_FOLDER :=       $(MODELS_FOLDER)/server

### CONTROLLER FOLDERS
CONTROLLERS_FOLDER :=       controllers
PYTHON_CONTROLLER_FOLDER := $(CONTROLLERS_FOLDER)/$(PYTHON_FOLDER)
CPP_CONTROLLER_FOLDER :=    $(CONTROLLERS_FOLDER)/$(CPP_FOLDER)
C_CONTROLLER_FOLDER :=      $(CONTROLLERS_FOLDER)/$(C_FOLDER)

### VIEW FOLDERS
CLI_VIEW_FOLDER :=     gui/cli
DESKTOP_VIEW_FOLDER := gui/desktop
QT_PRO_PATH := $(DESKTOP_VIEW_FOLDER)/sources
INSTALL_FOLDER := ~/tmp/brick_game

### TEST FOLDERS
TESTS_FOLDER :=        tests
PYTHON_TESTS_FOLDER := $(TESTS_FOLDER)/$(PYTHON_FOLDER)
C_CPP_TESTS_FOLDER :=  $(TESTS_FOLDER)/$(CPP_FOLDER)_$(C_FOLDER)


## OBJ FOLDERS
OBJ_FOLDER := obj

### OBJ SOURCE FOLDERS
OBJ_MODELS_FOLDER :=    $(OBJ_FOLDER)/$(MODELS_FOLDER)
OBJ_CPP_MODEL_FOLDER := $(OBJ_MODELS_FOLDER)/$(CPP_FOLDER)
OBJ_C_MODEL_FOLDER :=   $(OBJ_MODELS_FOLDER)/$(C_FOLDER)


### OBJ CONTROLLER FOLDERS
OBJ_CONTROLLERS_FOLDER :=       $(OBJ_FOLDER)/$(CONTROLLERS_FOLDER)
OBJ_PYTHON_CONTROLLER_FOLDER := $(OBJ_CONTROLLERS_FOLDER)/$(PYTHON_FOLDER)
OBJ_CPP_CONTROLLER_FOLDER :=    $(OBJ_CONTROLLERS_FOLDER)/$(CPP_FOLDER)
OBJ_C_CONTROLLER_FOLDER :=      $(OBJ_CONTROLLERS_FOLDER)/$(C_FOLDER)

### OBJ VIEW FOLDERS
OBJ_CLI_VIEW_FOLDER := $(OBJ_FOLDER)/$(CLI_VIEW_FOLDER)

### OBJ TEST FOLDERS
TEST_OBJ_FOLDER := $(OBJ_FOLDER)/$(TESTS_FOLDER)

#### GCOV FOLDERS
GCOV_OBJ_FOLDER :=              $(OBJ_FOLDER)/gcov
GCOV_OBJ_CPP_MODEL_FOLDER :=    $(GCOV_OBJ_FOLDER)/$(CPP_MODEL_FOLDER)
GCOV_OBJ_C_MODEL_FOLDER :=      $(GCOV_OBJ_FOLDER)/$(C_MODEL_FOLDER)
GCOV_OBJ_C_CONTROLLER_FOLDER := $(GCOV_OBJ_FOLDER)/$(C_CONTROLLER_FOLDER)
GCOV_OBJ_C_LIBRARY_FOLDER :=    $(GCOV_OBJ_FOLDER)/$(MODELS_FOLDER)
GCOV_TEST_OBJ_C_CPP_FOLDER :=   $(GCOV_OBJ_FOLDER)/$(C_CPP_TESTS_FOLDER)

# BUILD_FOLDER := build

#   FILES
##  SOURCE FILES
### MODEL FILES
CPP_MODEL := $(wildcard $(CPP_MODEL_FOLDER)/$(PREFIX)*.cc)
C_MODEL :=   $(wildcard $(C_MODEL_FOLDER)/$(PREFIX)*.c) 
C_LIBRARY := $(wildcard $(C_LIBRARY_FOLDER)/$(PREFIX)*.c)
PYTHON_SERVER_PATH := $(SERVER_FOLDER)/$(SERVER)
PYTHON_SERVER_MODULE := $(subst /,.,$(PYTHON_SERVER_PATH))


### CONTROLLER SOURCES
PYTHON_CONTROLLER :=      $(wildcard $(PYTHON_CONTROLLER_FOLDER)/$(PREFIX)*.cc)
CPP_CONTROLLER :=         $(wildcard $(CPP_CONTROLLER_FOLDER)/$(PREFIX)*.cc)
C_CONTROLLER :=           $(wildcard $(C_CONTROLLER_FOLDER)/$(PREFIX)*.c) 
C_CPP_CONTROLLER :=       $(wildcard $(C_CONTROLLER_FOLDER)/$(PREFIX)*.cc)

### VIEW SOURCES
CLI_VIEW := $(wildcard $(CLI_VIEW_FOLDER)/$(PREFIX)*.cc)

### TEST SOURCES
C_CPP_TEST := $(wildcard $(C_CPP_TESTS_FOLDER)/$(PREFIX)*.cc)

##  OBJ FILES
### MODEL OBJS
OBJ_CPP_MODEL :=  $(CPP_MODEL:$(CPP_MODEL_FOLDER)/%.cc=$(OBJ_CPP_MODEL_FOLDER)/%.o)
OBJ_C_MODEL :=    $(C_MODEL:$(C_MODEL_FOLDER)/%.c=$(OBJ_C_MODEL_FOLDER)/%.o)
OBJ_C_LIBRARY :=  $(OBJ_MODELS_FOLDER)/highscore.o
SOBJ_C_LIBRARY := $(OBJ_MODELS_FOLDER)/libhighscore.so

### CONTROLLER OBJS
OBJ_PYTHON_CONTROLLER :=    $(PYTHON_CONTROLLER:$(PYTHON_CONTROLLER_FOLDER)/%.cc=$(OBJ_PYTHON_CONTROLLER_FOLDER)/%.o)
OBJ_C_CONTROLLER :=         $(C_CONTROLLER:$(C_CONTROLLER_FOLDER)/%.c=$(OBJ_C_CONTROLLER_FOLDER)/%.o)
OBJ_C_CPP_CONTROLLER :=     $(C_CPP_CONTROLLER:$(C_CONTROLLER_FOLDER)/%.cc=$(OBJ_C_CONTROLLER_FOLDER)/%.o)
OBJ_C_LIBRARY_CONTROLLER := $(OBJ_C_CONTROLLER_FOLDER)/libtetris.so
OBJ_CPP_LIBRARY_CONTROLLER := $(OBJ_CPP_CONTROLLER_FOLDER)/libsnake.so

### VIEW OBJS
OBJ_CLI_VIEW := $(CLI_VIEW:$(CLI_VIEW_FOLDER)/%.cc=$(OBJ_CLI_VIEW_FOLDER)/%.o)

### TEST OBJS
TEST_OBJ_C_CPP := $(C_CPP_TEST:$(C_CPP_TESTS_FOLDER)/%.cc=$(TEST_OBJ_FOLDER)/%.o) 

GCOV_OBJ_CPP_MODEL :=    $(CPP_MODEL:$(CPP_MODEL_FOLDER)/%.cc=$(GCOV_OBJ_CPP_MODEL_FOLDER)/%.o) 
GCOV_OBJ_C_MODEL :=      $(C_MODEL:$(C_MODEL_FOLDER)/%.c=$(GCOV_OBJ_C_MODEL_FOLDER)/%.o)
GCOV_OBJ_C_CONTROLLER := $(C_CONTROLLER:$(C_CONTROLLER_FOLDER)/%.c=$(GCOV_OBJ_C_CONTROLLER_FOLDER)/%.o)
GCOV_OBJ_C_LIBRARY :=    $(C_LIBRARY:$(MODELS_FOLDER)/%.c=$(GCOV_OBJ_C_LIBRARY_FOLDER)/%.o)
GCOV_TEST_OBJ_C_CPP :=   $(C_CPP_TEST:$(C_CPP_TESTS_FOLDER)/%.cc=$(GCOV_TEST_OBJ_C_CPP_FOLDER)/%.o)

# LIBS AND FLAGS
PYTHON_H_PATH :=   $(shell $(PYTHON) -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")
PYTHON_LIB :=      $(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('LIBDIR'))" )
PYTHON_LIB_NAME := $(shell $(PYTHON) -c "import sysconfig; print('python' + sysconfig.get_python_version())")


OS = $(shell uname)
ifeq ($(OS),Linux)
	GCOV_FLAGS :=        -fprofile-arcs -ftest-coverage
	CHECK_LIBS :=        -lcheck -lm -lrt -lpthread -lsubunit
	LDLIBS :=            -lgtest_main -lgtest -lpthread
	GTEST_DIR :=         /usr/local
	GTEST_LIB_DIR :=     -L$(GTEST_DIR)/build/lib
	GTEST_INCLUDE_DIR := -isystem $(GTEST_DIR)/googletest/include
	QMAKE :=             /usr/bin/qmake6
else
	LDLIBS_MAC :=        -lgtest_main -lgtest -lpthread -lm --coverage -fprofile-arcs -ftest-coverage
	QMAKE :=             /Applications/Qt/6.6.0/macos/bin/qmake6
	# QMAKE :=           qmake
endif

# DEPENDENCY
EXISTING_DEPS = $(wildcard $(OBJ_CPP_MODEL:.o=.d) $(OBJ_C_MODEL:.o=.d) \
				$(OBJ_PYTHON_CONTROLLER:.o=.d) $(OBJ_C_CONTROLLER:.o=.d) \
				$(OBJ_C_CPP_CONTROLLER:.o=.d) $(OBJ_CLI_VIEW:.o=.d) \
				$(OBJ_C_LIBRARY_CONTROLLER:.so=.d) \
				$(OBJ_CPP_LIBRARY_CONTROLLER:.so=.d))

include $(EXISTING_DEPS)

# TARGETS
all: delete_highscores tests install


install: library_highscore
	@echo "Installing..."
	@mkdir -p $(INSTALL_FOLDER) 
	@cp -r ./ $(INSTALL_FOLDER)/
	@cd $(INSTALL_FOLDER) && $(QMAKE) $(QT_PRO_PATH)/$(TARGET_NAME)s.pro && make
ifeq ($(OS), Linux)
	@sudo install $(INSTALL_FOLDER)/$(TARGET_NAME)s /usr/local/bin
else
	@mv $(INSTALL_FOLDER)/$(TARGET_NAME)s.app /Applications
endif
	@rm -rf $(INSTALL_FOLDER) .qmake.stash

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
	@cp -rf brick_game/ gui/ tests/ ./Makefile ../README.md $(DISTNAME)/
	@tar -cf $(DISTNAME).tar $(DISTNAME)
	@rm -rf $(DISTNAME)

server_start: library_highscore library_tetris library_snake
	@uvicorn ${PYTHON_SERVER_MODULE}:app --host localhost --port $(PORT) --log-level debug

cli: $(OBJ_CPP_MODEL) $(OBJ_C_MODEL) $(OBJ_PYTHON_CONTROLLER) $(OBJ_C_CONTROLLER) $(OBJ_C_CPP_CONTROLLER) $(OBJ_CLI_VIEW) library_highscore
	@echo "Linking..."
	$(CC_CPP) $(OBJ_C_LIBRARY) $(OBJ_CPP_MODEL) $(OBJ_C_MODEL) $(OBJ_PYTHON_CONTROLLER) $(OBJ_C_CONTROLLER) $(OBJ_C_CPP_CONTROLLER) $(OBJ_CLI_VIEW) -I$(PYTHON_H_PATH) -l$(PYTHON_LIB_NAME) -lncurses -o $(TARGET)
	@./$(TARGET)

tests: delete_highscores test_python test_c_cpp

test_python: library_highscore library_tetris library_snake
	@pytest --cov=$(PREFIX)$(PYTHON_FOLDER) --cov-report=html $(PYTHON_TESTS_FOLDER)/

test_c_cpp: $(OBJ_CPP_MODEL) $(OBJ_C_MODEL) $(OBJ_C_CONTROLLER) $(OBJ_C_LIBRARY) $(TEST_OBJ_C_CPP)
	@$(CC_CPP) $(CPPFLAGS) $(OBJ_CPP_MODEL) $(OBJ_C_MODEL) $(OBJ_C_CONTROLLER) $(OBJ_C_LIBRARY) $(TEST_OBJ_C_CPP) $(LDLIBS) -o $(TEST_TARGET)
	@./$(TEST_TARGET)

library_highscore: $(OBJ_C_LIBRARY)
	@$(CC_C) $(CFLAGS) -shared -o $(SOBJ_C_LIBRARY) -fPIC $(OBJ_C_LIBRARY)

library_tetris: $(OBJ_C_LIBRARY_CONTROLLER)

library_snake: $(OBJ_CPP_LIBRARY_CONTROLLER)

gcov_report: $(GCOV_OBJ_CPP_MODEL) $(GCOV_OBJ_C_MODEL)  $(GCOV_OBJ_C_CONTROLLER) $(GCOV_OBJ_C_LIBRARY) $(GCOV_TEST_OBJ_C_CPP) delete_highscores
	@echo "Creating a report..."
ifeq ($(OS), Linux)
	@$(CC_CPP) \
	$(GCOV_OBJ_CPP_MODEL) $(GCOV_OBJ_C_MODEL)  $(GCOV_OBJ_C_CONTROLLER) $(GCOV_OBJ_C_LIBRARY) $(GCOV_TEST_OBJ_C_CPP) \
	$(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) \
	--coverage -o $(TEST_TARGET) $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS);
	@ ./$(TEST_TARGET)
	@lcov -t "test" -o test.info -c -d $(GCOV_OBJ_FOLDER)/
	@lcov --remove test.info '/usr/*' -o filtered_coverage.info
	@genhtml -o report/ filtered_coverage.info
else
	@$(CC_CPP) $(CPPFLAGS) $(LDLIBS_MAC) \
	$(GCOV_OBJ_CPP_MODEL) $(GCOV_OBJ_C_MODEL)  $(GCOV_OBJ_C_CONTROLLER) $(GCOV_OBJ_C_LIBRARY) $(GCOV_TEST_OBJ_C_CPP) \
	-o $(TEST_TARGET); ./$(TEST_TARGET)
	@lcov --no-external --ignore-errors mismatch --ignore-errors inconsistent -t "test" -o test.info -c -d . > /dev/null 2>&1
	@genhtml --ignore-errors inconsistent -o report/ test.info > /dev/null 2>&1
endif
	@mv *.info $(GCOV_OBJ_FOLDER)
	@open report/index.html

valgrind: test_c_cpp
	@valgrind --leak-check=full --track-origins=yes --log-file=record.log ./$(TEST_TARGET)

style:
	# @cp ../materials/.clang-format clang-format
	@find . \( -name "*.cc" -o -name "*.h" -o -name "*.c" \) -exec clang-format -n {} +
	@find . \( -name "*.cc" -o -name "*.h" -o -name "*.c" \) -exec clang-format -i {} +

clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJ_FOLDER)/
	@rm -rf *.out *.o *.info *.log 
	@rm -rf tmp/ htmlcov/ report/
	@rm -rf $(TARGET) $(TEST_TARGET) ./$(DISTNAME).tar
	@rm -rf $(INSTALL_FOLDER)

delete_highscores:
	@rm -rf ~/brick_games/

#INSTALL LIBS
install_gtest:
	@echo "Installing gtest"
	@git clone https://github.com/google/googletest.git
	@cd googletest
	@mkdir build && cd build
	@cmake ..
	@make
	@sudo make install

install_lcheck:
	@echo "Installing lcheck"
	@sudo apt-get install check

install_lncurses:
	@echo "Installing ncurses"
	@sudo apt-get install libncurses5-dev libncursesw5-dev

install_lcov:
	@sudo apt-get install lcov

install_qt6:
	@sudo add-apt-repository ppa:qtproject/ppa
	@sudo apt update
	@sudo apt install qt6-default

#  CREATING OBJS
## MODEL OBJS
$(OBJ_CPP_MODEL_FOLDER)/%.o: $(CPP_MODEL_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CPPFLAGS) -MMD -c $< -o $@

$(OBJ_C_MODEL_FOLDER)/%.o: $(C_MODEL_FOLDER)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CFLAGS) -MMD -c $< -o $@

$(OBJ_C_LIBRARY):
	@mkdir -p $(@D)
	@$(CC_C) -c $(CFLAGS) -o $(OBJ_C_LIBRARY) -fPIC $(C_LIBRARY)

## CONTROLLER OBJS
$(OBJ_PYTHON_CONTROLLER_FOLDER)/%.o: $(PYTHON_CONTROLLER_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CPPFLAGS) -I$(PYTHON_H_PATH) -l$(PYTHON_LIB_NAME) -MMD -c $< -o $@

$(OBJ_C_CONTROLLER_FOLDER)/%.o: $(C_CONTROLLER_FOLDER)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CFLAGS) -MMD -c $< -o $@

$(OBJ_C_CONTROLLER_FOLDER)/%.o: $(C_CONTROLLER_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CPPFLAGS) -MMD -c $< -o $@

$(OBJ_C_LIBRARY_CONTROLLER):
	@mkdir -p $(@D)
	@$(CC_C) -shared $(CFLAGS) -o $(OBJ_C_LIBRARY_CONTROLLER) -fPIC $(C_CONTROLLER) $(C_MODEL) $(C_LIBRARY)

$(OBJ_CPP_LIBRARY_CONTROLLER):
	@mkdir -p $(@D)
	@$(CC_CPP) -shared $(CPPFLAGS) -o $(OBJ_CPP_LIBRARY_CONTROLLER) -fPIC $ $(CPP_MODEL) $(C_LIBRARY) $(CPP_CONTROLLER)

## VIEW OBJS
$(OBJ_CLI_VIEW_FOLDER)/%.o: $(CLI_VIEW_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CPPFLAGS) -I$(PYTHON_H_PATH) -l$(PYTHON_LIB_NAME) -lncurses -MMD -c $< -o $@

## TEST OBJS
$(TEST_OBJ_FOLDER)/%.o: $(C_CPP_TESTS_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
	@$(CC_CPP) $(CPPFLAGS) $(GTEST_INCLUDE_DIR) -MMD -c $< -o $@ $(GTEST_LIB_DIR)

##  GCOV OBJS
### GCOV_OBJ_CPP_MODEL
$(GCOV_OBJ_CPP_MODEL_FOLDER)/%.o: $(CPP_MODEL_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
ifeq ($(OS), Linux)
	@$(CC_CPP) $(CPPFLAGS) $(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) --coverage -MMD -c $< -o $@ $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
else
	@$(CC_CPP) $(CPPFLAGS) --coverage -MMD -c $< -o $@
endif

### GCOV_OBJ_C_MODEL
$(GCOV_OBJ_C_MODEL_FOLDER)/%.o: $(C_MODEL_FOLDER)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
ifeq ($(OS), Linux)
	@$(CC_C) $(CFLAGS) $(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) --coverage -MMD -c $< -o $@ $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
else
	@$(CC_C) $(CFLAGS) --coverage -MMD -c $< -o $@
endif

### GCOV_OBJ_C_CONTROLLER
$(GCOV_OBJ_C_CONTROLLER_FOLDER)/%.o: $(C_CONTROLLER_FOLDER)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
ifeq ($(OS), Linux)
	@$(CC_C) $(CFLAGS) $(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) --coverage -MMD -c $< -o $@ $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
else
	@$(CC_C) $(CFLAGS) --coverage -MMD -c $< -o $@
endif

### GCOV_OBJ_C_LIBRARY
$(GCOV_OBJ_C_LIBRARY_FOLDER)/%.o: $(C_LIBRARY_FOLDER)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
ifeq ($(OS), Linux)
	@$(CC_C) $(CFLAGS) $(GCOV_FLAGS) -pthread $(GTEST_INCLUDE_DIR) --coverage -MMD -c $< -o $@ $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
else
	@$(CC_C) $(CFLAGS) --coverage -MMD -c $< -o $@
endif

### GCOV_TEST_OBJ_C_CPP
$(GCOV_TEST_OBJ_C_CPP_FOLDER)/%.o: $(C_CPP_TESTS_FOLDER)/%.cc
	@mkdir -p $(@D)
	@echo "Compiling $< -> $@..."
ifeq ($(OS), Linux)
	@$(CC_CPP) $(CPPFLAGS) $(GCOV_FLAGS)  -pthread $(GTEST_INCLUDE_DIR) --coverage -MMD -c $< -o $@ $(GTEST_LIB_DIR) $(LDLIBS) $(CHECK_LIBS)
else
	@$(CC_CPP) $(CPPFLAGS) --coverage -MMD -c $< -o $@
endif
