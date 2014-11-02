
bin_PROGRAMS = snafu prototrick simple_inheritance printer painting foo1

snafu_SOURCES = snafu.c
prototrick_SOURCES = prototrick.c
simple_inheritance_SOURCES = simple_inheritance.c
printer_SOURCES = printer.c
painting_SOURCES = painting.c
foo1_SOURCES = foo1.c # foo2.c # demo to show duplicate symbol won't link

AM_CPPFLAGS = -I../include -Wall -pedantic -Wno-comment -D$*_STANDALONE

clean-local:
	rm -rf *~
