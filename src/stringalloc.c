#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** gcc -Wall -g stringalloc.c */

char * 
string_new(size_t size) {

  char * s = (char*)malloc(size);
  memset((void*)s, 0xda, size);
  return s;
}

void
string_delete(char * s) {
  
  // We don't have a size for s, 
  // so we stick a nastygram in 
  // it's first byte.
  *s = 0xdd;
  free(s);
}


int
main(int argc, char ** argv) {

  char * s = string_new(10);
  string_delete(s);
 
  return 0;
}

  
  
