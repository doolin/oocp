#include <stdio.h>

/**
 * This program will not compile when linked with
 * the foo function in foo2.c as the symbol _foo
 * is already defined.
 */
void
foo(void) {
  printf("From foo1...\n");
}

int
main(int argc, char ** argv) {

   foo();
   return 0;
}
