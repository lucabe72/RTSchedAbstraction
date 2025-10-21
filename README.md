# How to Use

First of all, import the Linux kernel sources to be analyzed (mainly `rt.c`):

	sh prepare.sh <absolute path to Linux sources>

(to run `prepare.sh`, you need to install the Python bindings for clang;
on Debian, Ubuntu, or similar, this is something like the `python3-clang`
package).
Then, run Mopsa with

	make mopsa

You can also build a simple test program with a simple

	make


# Organization of the Source Code

The `src` directory (created by `prepare.sh`) contains unmodified Linux code,
mainly `rt.c`, but also some data structures needed to compile it (to make the
code more self-contained, some data structures have been split out of larger
header files, but they are copied without modifications).

The `stub` directory, instead, contains some stub/glue code needed to compile
the real-time scheduling class. Some of this code is inspired by Linux (with
some modifications), while some other code is written from scratch (and some
functions or structures are even empty).
