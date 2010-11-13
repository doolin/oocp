#include <stdio.h>
#include <stdlib.h>
#include "snafu.h"

/** 
 * Compile with:  gcc -I../include snafu.c -o snafu
 */

struct _foo {
  int bar;
  int baz;
};

struct _snafu {
  struct _foo foo;
  int fubar;
};

int 
main(int argc, char ** argv) {

  struct _snafu snafu;
  snafu.foo.bar = 1;

  printf("snafu.foo.bar: %d\n", snafu.foo.bar);

  exit (0);

}
