CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -g
TARG = matrix
FULL_TARG = s21_$(TARG)
LIB = $(FULL_TARG).a
TEST = $(FULL_TARG)_tests
GCOV = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

ifeq ($(OS),Linux)
    CHECK_LIBS = -lcheck -lm -lrt -lpthread -lsubunit
else
    CHECK_LIBS = -lcheck -lm -lpthread
endif


all: $(LIB) test gcov_report

$(LIB):
	$(CC) -c $(CFLAGS) $(FULL_TARG).c
	ar rcs $(LIB) *.o
	ranlib $(LIB)

test:
	$(CC) $(CFLAGS) tests.c $(FULL_TARG).c -L. $(CHECK_LIBS) $(LIB) -o $(TEST)
	./$(TEST)

gcov_report:
	$(CC) tests.c $(GCOV) $(FULL_TARG).c -o $(TEST) $(CHECK_LIBS)
	./$(TEST)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
ifeq ($(OS),Darwin)
	open ./report/index.html
else
	genhtml -o report/ test.info
	open report/index.html
endif

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	clang-format -i *.c *.h

clean:
	rm -rf *.a *.o *.info *.gcda *.gcno *.gcov report $(TEST) $(FULL_TARG) *.h.gch *.dSYM

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

build:
	gcc $(CFLAGS) main.c $(FULL_TARG).c -o $(FULL_TARG) -lm;./$(FULL_TARG)

test_build:
	checkmk tests.check > tests.c
	$(CC) $(CFLAGS) $(FULL_TARG).c tests.c $(CHECK_LIBS) -o $(TEST);./$(TEST)

as:
	clang -fno-omit-frame-pointer -fsanitize=address -fsanitize=leak \
	-fsanitize=undefined -fsanitize-recover=address \
	$(CFLAGS) main.c $(FULL_TARG).c -lm -o $(FULL_TARG);./$(FULL_TARG)

valgrind: build
	valgrind --leak-check=full --track-origins=yes ./$(FULL_TARG)