cr := gcc
flags := -Wall -Werror -Wextra -std=c11
targ = grep
full_targ := s21_$(targ)
common = ../common/common.c

all: build
	
$(full_targ):
	$(cr) $(flags) $(full_targ).c $(common) -o $(full_targ)

build:
	$(cr) $(flags) $(full_targ).c $(common) -o $(full_targ)

clean:
	rm -rf $(full_targ)
	rm -rf *.o

tests:
	cd ../tests/ && python3 test_${targ}.py
	cd ../$(targ)/

leaks:
	cd ../tests/ && python3 test_${targ}.py val
	cd ../$(targ)/
	