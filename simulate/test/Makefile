test: push-box

push-box: ../push-box.c ../push-box.h ./test-push-box.c
	gcc test-push-box.c ../push-box.c -lm
	./a.out

push-box-alternative: ./test-push-box.c ./push-box.alternative.c
	gcc test-push-box.c push-box.alternative.c
	./a.out

clean:
	rm a.out
