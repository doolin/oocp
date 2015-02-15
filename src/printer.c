#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * One of the useful things about Java and many scripting languages
 * such as Python or Ruby is having the ability to print something
 * about each class and object. C of course doesn't have this, but
 * adding such capability is not difficult. A first step is defining
 * a generalized way to print.
 */

/** TODO:
 * 1. set up new and and delete functions
 * 2. ensure memory is shredded and actually freed, use valgrind
 * 3. Specialize printing for just stdout.
 */

typedef struct _object Object;

#ifndef OOCP_PRINTFUNC
typedef int  (*PrintFunc) (void* stream,
                           const char * format,
                           ...);
#define OOCP_PRINTFUNC
#endif


#ifndef OOCP_PRINTER
typedef void (*Printer)   (Object * o,
                           PrintFunc print_func,
                           void * stream);
#define OOCP_PRINTER
#endif


struct _object {
  Printer printer;
};

#define object_print(o,p,s)   ((Object*)o)->printer ((Object*)o,(PrintFunc)p,s);

typedef struct _thing {
  Object o;
  int value;
} Thing;

Thing *
thing_new() {
  Thing * t = (Thing*)malloc(sizeof(Thing));
  memset((void*)t, 0xda, sizeof(Thing));
  return t;
}

void
thing_printer(Object * o, PrintFunc print, void * stream) {

  Thing * t = (Thing *)o;
  print(stream, "Value from thing_printer: %d\n", t->value);
}

int
main(int atgc, char ** argv) {

  Thing t;
  t.o.printer = thing_printer;
  t.value = 1;

  object_print(&t, fprintf, stdout);

  return 0;
}
