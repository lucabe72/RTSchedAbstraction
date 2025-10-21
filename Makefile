CPPFLAGS=-Isrc

all: test
test: stub/sched.o main.o my_alloc.o
	$(CC) $(LDFLAGS) main.o stub/sched.o my_alloc.o -o test

clean:
	rm -f main.o test stub/sched.o my_alloc.o
allclean: clean
	rm -rf tmp src
