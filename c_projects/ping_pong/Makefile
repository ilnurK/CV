flags = -Wall -Werror -Wextra -lncurses

all: build

build:
	gcc pong2.c $(flags) -o pong

clean:
	rm -rf *.o a.out

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem pong2.c
