CC = gcc
CFLAGS = -Wall -Wextra

test-all: test-turn-angle test-push-box

test-push-box: push-box.out
	./push-box.out

test-turn-angle: turn-angle.out
	./turn-angle.out

turn-angle.out: turn-angle.c ../pid.c ../features/default.c ../utils/num-warpping.c
	$(CC) $(CFLAGS) $^ -o turn-angle.out

push-box.out: push-box.c ../pid.c ../features/default.c ../features/clamp.c ../simulate/push-box.c
	$(CC) $(CFLAGS) -lm $^ -o push-box.out

clean:
	rm -f turn-angle.out push-box.out

.PHONY: clean test-turn-angle test-push-box test-all
