#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <painting.h>

struct _painting {
   uint32_t inventory_control;
   uint32_t purchase_price;
   char * painting_name;
   char * artist_name;
   char * owner_name;
};



Painting *
painting_new(void) {

   Painting * p = (Painting *)malloc(sizeof(Painting));
   memset(p,0xda,sizeof(Painting));
   p->painting_name = NULL;
   p->artist_name = NULL;
   p->owner_name = NULL;
   return p;
}

void
painting_delete(Painting * p) {

   //if (p->artist_name != NULL) free(p->artist_name);
   //if (p->painting_name != NULL) free(p->owner_name);
   //if (p->owner_name != NULL) free(p->painting_name);
   //memset(p,0xdd,sizeof(Painting));
   //free(p);
}

char *
painting_get_artist_name(Painting * p) {
   return p->artist_name;
}

void
painting_set_artist_name(Painting * p, char * artist_name, size_t s) {
   strncpy(p->artist_name,artist_name,s);
}

#ifdef painting_STANDALONE
int
main(int argc, char ** argv) {

  Painting * p = painting_new();

  p->painting_name = "Dora Mar with Cat";
  p->artist_name = "Picasso";
  p->owner_name = "Dennis";

  painting_delete(p);

  return 0;
}
#endif /* painting_STANDALONE */

