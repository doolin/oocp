#include<stdio.h>


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


#define object_print(o,p,s)   ((Object*)o)->print ((Object*)o,(PrintFunc)p,s);

struct _object {
  Printer print;
};

typedef struct _thing {
  Object o;
  int value;
} Thing;

void
thing_printer(Object * o, PrintFunc print, void * stream) {

  Thing * t = (Thing *)o;
  print(stream, "Value from thing_printer: %d\n", t->value);
}

int
main(int atgc, char ** argv) {

  Thing t;
  t.o.print = thing_printer;
  t.value = 1;

  object_print(&t, fprintf, stdout);

  return 0;
}
