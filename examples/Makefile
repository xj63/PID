CC = gcc
CFLAGS = -Wall -Wextra

test-all: test-turn-angle

test-turn-angle: turn-angle.out
	./turn-angle.out

turn-angle.out: turn-angle.c ../pid.c ../features/default.c ../utils/num-warpping.c
	$(CC) $(CFLAGS) $^ -o turn-angle.out

clean:
	rm turn-angle.out

.PHONY: clean test-turn-angle
