#include <stdio.h>

/**
 * function definition serves as prototype.
 * No need to define prototype as long as the
 * function invocation follows the definition of
 * the function. This is a good way to enforce
 * "private" functions: this definition of foo
 * cannot be called from a function in another
 * file, the name won't resolve.
 *
 * However, there can still be only one function
 * named foo in the entire program, as the linker
 * will not overwrite an existing symbol.
 */
void
foo(void) {
  printf("From foo...\n");
}

int
main(int argc, char ** argv) {

   foo();
   return 0;
}
