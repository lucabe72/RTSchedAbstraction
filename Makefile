CPPFLAGS=-Isrc

all: test
test: stub/sched.o main.o my_alloc.o
	$(CC) $(LDFLAGS) main.o stub/sched.o my_alloc.o -o test

mopsa: mopsa.db
	mopsa-c mopsa.db -make-target=test -stub-ignore-case=malloc.failure -config=c/cell-string-length-itv.json -loop-unrolling=4 -loop-unrolling-at=string.c:99:800 -stub-use-forall-loop-evaluation

mopsa.db:
	mopsa-build make

clean:
	rm -f main.o test stub/sched.o my_alloc.o
mopsa-clean:
	rm -f mopsa.db
allclean: clean mopsa-clean
	rm -rf tmp src
