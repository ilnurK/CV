flags = -Wall -Werror -Wextra -lncurses

all: build

build:
	gcc pong2.c $(flags)

clean:
	rm -rf *.o a.out

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem pong2.c
