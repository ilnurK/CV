CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -g
SANFLAGS = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize-recover=address
PKG = `pkg-config --cflags --libs gtk+-3.0` -rdynamic
TARG = s21_smart_calc
BACKEND = backend/*.c 
GUI = calc_gui/*.c
LIB = $(TARG).a
TESTS = tests/*.c
TEST_EXE = $(TARG)_tests
GCOV = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

ifeq ($(OS),Linux)
    CHECK_LIBS = -lcheck -lm -lrt -lpthread -lsubunit
else
    CHECK_LIBS = -lcheck -lm -lpthread
endif

#PRIMARY
all: test gcov_report

clean:
	rm -rf *.a *.o *.info *.gcda *.gcno *.gcov report $(TEST_EXE) $(TARG) *.h.gch *.dSYM

install: build
	install ./$(TARG) /usr/local/bin

gcov_report:
	$(CC) $(GCOV) $(BACKEND) $(TESTS) -o $(TEST_EXE) $(CHECK_LIBS)
	./$(TEST_EXE)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
ifeq ($(OS),Darwin)
	open ./report/index.html
else
	genhtml -o report/ test.info
	open report/index.html
endif

dist:
	tar -czvf $(TARG).tar.gz $(BACKEND) $(GUI) $(TESTS) *.c *.h

test: $(LIB)
	$(CC) $(CFLAGS) $(BACKEND) $(TESTS) -L. $(CHECK_LIBS) $(LIB) -lm -o $(TEST_EXE)
	./$(TEST_EXE)

#SECONDARY
$(LIB):
	$(CC) -c $(CFLAGS) $(BACKEND)
	ar rcs $(LIB) *.o
	ranlib $(LIB)

asan:
	clang $(SANFLAGS) $(BACKEND) $(GUI) $(TARG).c -o $(TARG) -lm $(PKG) ;./$(TEST_EXE)

build:
	$(CC) $(CFLAGS) $(BACKEND) $(GUI) $(TARG).c -o $(TARG) -lm $(PKG);

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h $(BACKEND) $(GUI) $(TESTS)
	clang-format -i *.c *.h $(BACKEND) $(GUI) $(TESTS)

git_add:
	git add *.c *.h Makefile backend/* calc_gui/* tests/*

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

brew_cairo:
	brew install gtk+3 cairo

run: build
	./$(TARG)

valgrind: build
	valgrind --leak-check=full --track-origins=yes ./$(TEST_EXE)


