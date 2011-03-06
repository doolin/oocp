#include<stdio.h>

// Use ~/DDA/modec/trunk/include/object.h

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


#define OBJECT_PRINT (p) ( (Object

typedef struct _object {
  Printer printer;
} Object;

typedef struct _thing {
  Object o;
  int value;
} Thing;

int
main(int atgc, char ** argv) {

  Thing t;
  t.o.printer = (PrintFunc)fprintf;
  t.value = 1;

  t.o.printer(stdout, "Value: %d\n",t.value);
  

  return 0;
}
