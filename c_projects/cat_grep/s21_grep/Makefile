CC := gcc
FLAGS := -Wall -Werror -Wextra -std=c11
TARG = s21_grep
COMMON = ../common/common.c

all: build
	
$(TARG):
	$(CC) $(FLAGS) $(TARG).c $(COMMON) -o $(TARG)

build:
	$(CC) $(FLAGS) $(TARG).c $(COMMON) -o $(TARG)

clean:
	rm -rf $(TARG)
	rm -rf *.o

install: build
	install ./$(TARG) /usr/local/bin

uninstall:
	rm -f /usr/local/bin/$(TARG)

tests:
	cd ../tests/ && python3 test_$(TARG).py
	cd ../$(TARG)/

leaks:
	cd ../tests/ && python3 test_$(TARG).py val
	cd ../$(TARG)/
	