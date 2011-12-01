CFLAGS += -g -pedantic -Wall -Wextra -std=c99
 
binaries = $(sort $(basename $(wildcard *c)))

.PHONY: all
all: $(binaries)

$(binaries) : % : %.c

.PHONY: clean
clean:
	rm -f $(binaries)

