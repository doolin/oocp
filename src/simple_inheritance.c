
#include <stdio.h>

typedef struct _object {
  int foo;
} Object;

typedef struct _thing {
   Object o;
   double bar;
} Thing;


void
print_foo(Object * o) {

  printf("o->foo: %d\n", o->foo);
}

int
main (int argc, char ** argv) {


  Thing t;
  
  t.o.foo = 1;

  printf("t.o.foo: %d\n", t.o.foo);

  print_foo(&t.o);

  return 0;
}
