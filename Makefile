# Example makefile for CPE 464
#
ALL=battle
CC = g++
CFLAGS = -g -Wall -Werror 

OS = $(shell uname -s)
PROC = $(shell uname -p)

all:  $(ALL)

$(ALL): *.cpp
	$(CC) $(CFLAGS) $(OSINC) $(OSLIB) $(OSDEF) -o $@ $^ $(DEBUG)
clean:
	rm -rf $(ALL) *.o

test:   all
	./$(ALL)

debug:
	$(MAKE) DEBUG='-DDEBUG'
	gdb -tui $(ALL)
