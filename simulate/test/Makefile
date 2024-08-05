CC = gcc
CFLAGS = -Wall -Wextra -lm
SRC = ../push-box.c ../../pid.c ../../features/default.c
HEADERS = ../push-box.h ../../pid.h ../../features.h
TESTS = $(wildcard test-*.c)
TARGETS = $(TESTS:.c=.out)

test: test-all

test-all: $(TARGETS)
	@for target in $(TARGETS); do \
		printf "\e[32m- Running:\e[0m $${target%.out}\n"; \
		./$$target; \
		echo; \
	done

test-one: $(TARGETS)
	@if [ -z "$(TEST_NAME)" ]; then \
		echo "Usage: make test-one TEST_NAME=<test-name>"; \
	else \
		executable=$${TEST_NAME}.out; \
		if [ -f "$$executable" ]; then \
			printf "\e[32m- Running:\e[0m $${executable%.out}\n"; \
			./$$executable; \
			echo; \
		else \
			echo "Executable $$executable does not exist."; \
		fi \
	fi

$(TARGETS): %.out: %.c $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $< $(SRC) -o $@

clean:
	rm -f $(TARGETS)

.PHONY: test test-all test-one clean
