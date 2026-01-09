MOPSAFLAGS=-make-target=test -stub-ignore-case=malloc.failure -config=c/cell-string-length-pack-rel-itv-congr.json -loop-unrolling=4 -loop-unrolling-at=string.c:99:800 -stub-use-forall-loop-evaluation

CFLAGS+=-Wall -Wextra -g
CFLAGS+=-fsanitize=address
LDFLAGS+=-fsanitize=address
CPPFLAGS=-I..

all: test

mopsa: mopsa.db
	mopsa-c mopsa.db $(MOPSAFLAGS)
mopsa.txt: mopsa.db
	mopsa-c mopsa.db $(MOPSAFLAGS) -no-color > mopsa.txt

mopsa.db:
	mopsa-build make

clean:
	rm -f test
	rm -f mopsa.db 
