CC := gcc
FLAGS := -Wall -Werror -Wextra -std=c11 -lncurses
TARG = pong

all: build

build:
	$(CC) $(TARG).c $(FLAGS) -o $(TARG)

clean:
	rm -rf *.o $(TARG)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(TARG).c
