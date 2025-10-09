CPPFLAGS=-Isrc

all: test
test: stub/sched.o main.o
	$(CC) main.o stub/sched.o -o test

clean:
	rm -f main.o test stub/sched.o
allclean: clean
	rm -rf tmp src
