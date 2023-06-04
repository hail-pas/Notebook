multi-t: hello.c thread.h
	gcc -ggdb -Wall -o a.out $<

stack: stack-probe.c thread.h
	gcc -ggdb -Wall -o a.out $<

alipy: alipay.c
	gcc -ggdb -Wall -o a.out $<

sum: sum.c
	gcc -ggdb -Wall -o a.out $<

store-load: store-load.c
	gcc -ggdb -Wall -o a.out $<

clean:
	rm -f a.out
sum-mutex: sum-mutex.c
	gcc -O2 $(CFLAGS) -o sum-mutex $<