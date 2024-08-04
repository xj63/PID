test: push-box

push-box: ../push-box.c ../push-box.h ./test-push-box.c
	gcc test-push-box.c ../push-box.c -lm
	./a.out

clean:
	rm a.out
