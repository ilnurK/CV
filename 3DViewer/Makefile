CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

TARG = 3DViewer
FULL_TARG = s21_$(TARG)

PREFIX_SRC = ./backend
PREFIX_OBJ = ./obj
SRC = $(wildcard $(PREFIX_SRC)/*.c)
OBJ = $(patsubst $(PREFIX_SRC)/%.c, $(PREFIX_OBJ)/%.o, $(SRC))

LIB = $(FULL_TARG).a
TESTS_FOLDER = ./tests
TEST = $(FULL_TARG)_tests
FRONT_FOLDER = $(TARG)
DISTNAME = $(TARG)_v1.0
DISTDIR = $(DISTNAME)
GCOV = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

ifeq ($(OS),Linux)
    CHECK_LIBS = -lcheck -lm -lrt -lpthread -lsubunit
else
    CHECK_LIBS = -lcheck -lm -lpthread
endif

#PRIMARY

all: $(LIB) test gcov_report

install:
	mkdir -p $(FRONT_FOLDER)/tmp
	cd $(FRONT_FOLDER)/tmp && qmake ../$(TARG).pro && make
	mkdir -p ./build
	mv $(FRONT_FOLDER)/tmp/$(TARG).app ./build
	rm -rf $(FRONT_FOLDER)/tmp .qmake.stash

dvi:
	open Readme.md

dist:
	test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	cp -rf $(PREFIX_SRC) $(FRONT_FOLDER) $(TESTS_FOLDER) models ./Makefile ./Readme.md $(DISTDIR)/
	tar -cf $(DISTNAME).tar $(DISTDIR)
	rm -rf $(DISTDIR)

test: $(LIB)
	$(CC) $(CFLAGS) $(TESTS_FOLDER)/*.c -L. $(CHECK_LIBS) $(LIB) -o $(TESTS_FOLDER)/$(TEST)
	$(TESTS_FOLDER)/$(TEST)

gcov_report:
	$(CC) $(GCOV) $(TESTS_FOLDER)/*.c $(SRC) -o $(TESTS_FOLDER)/$(TEST) $(CHECK_LIBS)
	$(TESTS_FOLDER)/$(TEST)
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

uninstall:
	rm -rf ./build

clean:
	rm -rf *.a *.o *.h.gch *.info *.gcda *.gcno *.gcov report
	rm -rf $(PREFIX_OBJ)
	rm -rf $(TESTS_FOLDER)/$(TEST) $(FULL_TARG) $(TESTS_FOLDER)/*.h.gch $(TESTS_FOLDER)/*.dSYM
	rm -rf .clang-format
	rm -rf ./$(DISTNAME).tar
	rm -rf ./tmp


#SECONDARY

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)
	ranlib $(LIB)

$(PREFIX_OBJ)/%.o : $(PREFIX_SRC)/%.c
	test -d $(PREFIX_OBJ) || mkdir -p $(PREFIX_OBJ)
	$(CC) -c $(CFLAGS) $< -o $@

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(PREFIX_SRC)/*.c $(PREFIX_SRC)/*.h
	clang-format -i $(TARG)/*.cpp $(TARG)/*.h
	clang-format -i $(TESTS_FOLDER)/*.c

test_build:
	checkmk $(TESTS_FOLDER)/tests.check > $(TESTS_FOLDER)/tests.c
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(TESTS_FOLDER)/tests.c
	$(CC) $(CFLAGS) $(TESTS_FOLDER)/tests.c $(SRC) $(CHECK_LIBS) -o $(TESTS_FOLDER)/$(TEST); $(TESTS_FOLDER)/$(TEST)

install2:
	mkdir -p $(FRONT_FOLDER)/tmp
	cd $(FRONT_FOLDER)/tmp && /Applications/Qt/6.6.0/macos/bin/qmake6 ../$(TARG).pro && make
	mkdir -p ./build
	mv $(FRONT_FOLDER)/tmp/$(TARG).app ./build
	rm -rf $(FRONT_FOLDER)/tmp .qmake.stash

install3:
	mkdir -p $(FRONT_FOLDER)/tmp
	cd $(FRONT_FOLDER)/tmp && qmake ../$(TARG).pro && make
	mkdir -p ./build
	install $(FRONT_FOLDER)/tmp/$(TARG) /usr/local/bin
	rm -rf $(FRONT_FOLDER)/tmp .qmake.stash


