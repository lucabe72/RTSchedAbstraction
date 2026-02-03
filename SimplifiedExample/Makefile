MOPSAFLAGS=-make-target=test -stub-ignore-case=malloc.failure -config=c/tail-cell-itv.json -loop-full-unrolling-at=test.c:47 -stub-alloc-pol=range_control -marker=if -tail-markers=14

CFLAGS+=-Wall -Wextra -g
CFLAGS+=-fsanitize=address
LDFLAGS+=-fsanitize=address
CPPFLAGS=-I..

all: test

test: test.o my_funcs.o

mopsa: mopsa.db
	mopsa-c mopsa.db $(MOPSAFLAGS)
mopsa.txt: mopsa.db
	mopsa-c mopsa.db $(MOPSAFLAGS) -no-color > mopsa.txt

mopsa.db:
	make clean
	mopsa-build make

clean:
	rm -f test
	rm -f *.o
	rm -f mopsa.db 
