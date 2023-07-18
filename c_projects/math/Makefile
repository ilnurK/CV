CC := gcc
CC_FLAGS := -std=c11 -Wall -Werror -Wextra
LIB := s21_math.a
TEST := tests.c
MATH := -lm
TEST_EXEC := test_s21_math
GCOV := -fprofile-arcs -ftest-coverage
UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
    CHECK_LIBS = -lcheck -lm -lrt -lpthread -lsubunit
else
    CHECK_LIBS = -lcheck -lm -lpthread
endif

FILES := s21_*.c

all: clean $(LIB)

$(LIB):
	$(CC) -c $(CC_FLAGS) $(FILES)
	ar rcs $(LIB) *.o
	ranlib $(LIB)

gcov_report:
	$(CC) $(TEST) $(GCOV) $(FILES) -o $(TEST_EXEC) $(CHECK_LIBS)
	./$(TEST_EXEC)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
ifeq ($(UNAME),Darwin)
	open ./report/index.html
else ifeq ($(UNAME),Linux)
	open report/index.html
endif

clean:
	rm -rf *.o *.a a.out *.info *.gcda *.gcno *.gcov *.h.gch *.dSYM $(TEST_EXEC)

test_build:
	checkmk test.check > tests.c

test: clean $(LIB)
	$(CC) $(CC_FLAGS) -L. $(TEST) $(CHECK_LIBS) $(LIB) $(MATH) -o $(TEST_EXEC)
	./$(TEST_EXEC)

build: clean $(LIB)
	$(CC) $(CC_FLAGS) main.c -L. $(LIB) $(MATH) -o a.out
	./a.out

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	clang-format -i *.c *.h