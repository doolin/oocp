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

#if 0  
If anything it doesn't go far enough.  This would be better:

typedef struct _string {
 size_t size;
 char * string;
} String;



// If you wrote this with void argument, you would have
// to define a DEFAULT_STRING_SIZE...
// A whole bunch of stuff ought to be coming clear
// right now, about how Java and friends do their
// business internally...
String *
string_new(size_t s) {
 String * string = (String*)malloc(sizeof(String));
 memset((void*)string, 0xda, size);
 string->size = s;  // Why are we doing this here?
 return string;
}

void
string_delete(String * s) {
 memset((void*)s, 0xdd, s->size);
 free(s);
}


String *
string_f_gets(Stream * stream) {

 String * s = string_new(128);
 int checkval = f_gets(s->string, s->size, (FILE*)stream);
 if (checkval) {
   return s;
 } else {
   // throw an error and do something else
 }
}

The above was all written off the top of my head.
It will work in principle.

And do take the time to understand.  It will pay
you back *huge* in the future.
#endif  
