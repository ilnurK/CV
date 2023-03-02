flags = -Wall -Werror -Wextra -lncurses

all: build

build:
	gcc game_of_life.c $(flags) -o game_of_life.out

clean:
	rm -rf *.o a.out

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem pong2.c

git:
	git add *!(*.json, *.out)