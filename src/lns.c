/*
 * lns.c
 *
 * Subroutine to determine whether two line segments
 * intersect.
 *
 * $Author: doolin $
 * $Date: 2006-07-07 17:36:51 $
 * $Source: /cygdrive/c/Documents and Settings/doolin/My Documents/home/doolin/tmp1/dda/modec/src/lns.c,v $
 * $Revision: 1.13 $
 */

// See also: http://en.wikipedia.org/wiki/Self-balancing_binary_search_tree#Applications

#include <math.h>

// This is brought in only for the __inlines.
#include "geometry.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


/**************************************************/
/* lns: intersection point of two lines           */
/**************************************************/
/* double:  x21 y21 x31 y31 x34 y34 x41 y41      */
/* int: kk3, double: t1, t2;  double:d0, d1,d2, a1, b1 */
/* lns determines whether lines defined by two point
 * sets intersect.  It is called by dc03(), dc04(),
 * dc10() and dc13(). w0 is the domain scale and
 * scales the tolerance values.
 */
int lns_old(double w0,
            double x21, double x31, double x34, double x41,
            double y21, double y31, double y34, double y41,
            double *pt1, double *pt2) {

   double c1;

  /* determinants */
   double d0, d1, d2;

  /* FIXME: What are these for? */
   double b1;
   double a1;

  /* kk3=0 no intersection.
   * kk3=1 output t1 t2 parameters
   */
   int kk3 = 0;

  /* t1 and t2 are parameters in the equation of
   * two lines.  For line segments, 0 <= t1 <= 1
   * and 0 <= t2 <= 1.  These are given as t and T
   * in GHS diss. page 181. or BSM page 148.
   * O'Rourke uses r and s as the parameters, which
   * is probably more standard.
   */
   double t1 = 0;
   double t2 = 0;

  /* d0, d1, d2 are determinants.
   */
   d0 = x21*y34 - x34*y21;   /* equation | |   */
   d1 = x31*y34 - x34*y31;   /* | | for sol t1 */
   d2 = x21*y31 - x31*y21;   /* | | for sol t2 */

  /* p1 p2 p3 p4  4 points co-line   */
   if ((fabs(d0) < (0.000000001*w0*w0)) && (fabs(d1) < (0.000000001*w0*w0))) {
      goto ln02;
   }

  /* p1 p2   p3 p4  are two parallel lines */
   if ( fabs(d0) < (0.000000001*w0*w0) )  {
      goto ln01;  // ie, return;
   }

   goto ln03;

ln02:

  /* p1 p2 p3 p4  4 points in same line. */
   a1=x21;
   b1=x31;
   if ( fabs(x21) > fabs(y21) ) {
      goto ln05;
   }

   a1=y21;
   b1=y31;

ln05:

  /* (x3 y3) lies in p1 p2 segment. */
   t1=b1/a1;
   if ( (t1< -0.0000001) || (t1 > 1.0000001) ) {
      goto ln04;
   }

   t2=0;
   kk3 = 1;

ln04:

   a1=x21;
   b1=x41;
   if ( fabs(x21) > fabs(y21) ) {
     goto ln06;
   }
   a1=y21;
   b1=y41;

ln06:
  /* (x4 y4) lies in p1 p2 segment                  */
  /* both p3 p4   in p1 p2 segment no intersection  */
   c1=b1/a1;

   if ( (c1< -0.0000001) || (c1 > 1.0000001) ) {
      goto ln01;  /* ie. return;  */
   }

   t1=b1/a1;
   t2=1;

   kk3 += 1;
   if (kk3 == 2) {
     kk3 = 0;
   }

   goto ln01;

ln03:

  /* Normal intersection.  */
   t1=d1/d0;
   if ( (t1 < -0.0000001) || (t1 > 1.0000001) ) {
      goto ln01;
   }

   t2=d2/d0;
   if ( (t2 < -0.0000001) || (t2 > 1.0000001) ) {
      goto ln01;
   }

   kk3 = 1;


ln01:

   *pt1 = t1;
   *pt2 = t2;

   return kk3;

}



/**************************************************/
/* lns: intersection point of two lines           */
/**************************************************/
/* double:  x21 y21 x31 y31 x34 y34 x41 y41      */
/* int: kk3, double: t1, t2;  double:d0, d1,d2, a1, b1 */
/* lns determines whether lines defined by two point
 * sets intersect.  It is called by dc03(), dc04(),
 * dc10() and dc13(). w0 is the domain scale and
 * scales the tolerance values.
 */
int lns_new(double w0,
            double j1x1, double j1y1, double j1x2, double j1y2,
            double j2x1, double j2y1, double j2x2, double j2y2,
            double * pt1, double * pt2) {

   double c1;

  /* determinants */
   double d0, d1, d2;

  /* FIXME: What are these for? */
   double b1;
   double a1;

  /* kk3=0 no intersection.
   * kk3=1 output t1 t2 parameters.
   */
   int kk3 = 0;

  /* t1 and t2 are parameters in the equation of
   * two lines.  For line segments, 0 <= t1 <= 1
   * and 0 <= t2 <= 1.  These are given as t and T
   * in GHS diss. page 181. or BSM page 148.
   * O'Rourke uses r and s as the parameters, which
   * is probably more standard.
   */
   double t1 = 0;
   double t2 = 0;
   double x21, y21, x34, y34, x31, y31, x41, y41;

   // Joint 1
   //x21 = joints[i][3] - joints[i][1]; /* coefficient a11 */
   x21 = j1x2 - j1x1;
   //y21 = joints[i][4] - joints[i][2]; /* coefficient a21 */
   y21 = j1y2 - j1y1;

   // Joint 2
   //x34 = joints[j][1] - joints[j][3]; /* coefficient a12 */
   x34 = j2x1 - j2x2;
   //y34 = joints[j][2] - joints[j][4]; /* coefficient a22 */
   y34 = j2y1 - j2y2;

//x31 = joints[j][1] - joints[i][1]; /* free terms  f1  */
   x31 = j2x1 - j1x1;
   //y31 = joints[j][2] - joints[i][2]; /* free terms  f2  */
   y31 = j2y1 - j1y1;

//x41 = joints[j][3] - joints[i][1]; /* co-line case    */
   x41 = j2x2 - j1x1;
   //y41 = joints[j][4] - joints[i][2];
   y41 = j2y2 - j1y1;

  /* d0, d1, d2 are determinants.
   */
   d0 = x21*y34 - x34*y21;   /* equation | |   */
   d1 = x31*y34 - x34*y31;   /* | | for sol t1 */
   d2 = x21*y31 - x31*y21;   /* | | for sol t2 */

  /* p1 p2 p3 p4  4 points co-line   */
   if ((fabs(d0) < (0.000000001*w0*w0)) && (fabs(d1) < (0.000000001*w0*w0))) {
      goto ln02;
   }

  /* p1 p2   p3 p4  are two parallel lines */
   if ( fabs(d0) < (0.000000001*w0*w0) )  {
     goto ln01;  // ie, return;
   }

   goto ln03;

ln02:

  /* p1 p2 p3 p4  4 points in same line. */
   a1=x21;
   b1=x31;
   if ( fabs(x21) > fabs(y21) ) {
      goto ln05;
   }

   a1=y21;
   b1=y31;

ln05:

  /* (x3 y3) lies in p1 p2 segment. */
   t1=b1/a1;
   if ( (t1< -0.0000001) || (t1 > 1.0000001) ) {
      goto ln04;
   }

   t2=0;
   kk3 = 1;

ln04:

   a1=x21;
   b1=x41;
   if ( fabs(x21) > fabs(y21) ) {
    goto ln06;
   }
   a1=y21;
   b1=y41;

ln06:
  /* (x4 y4) lies in p1 p2 segment                  */
  /* both p3 p4   in p1 p2 segment no intersection  */
   c1=b1/a1;

   if ( (c1< -0.0000001) || (c1 > 1.0000001) ) {
      goto ln01;  /* ie. return;  */
   }

   t1=b1/a1;
   t2=1;

   kk3 += 1;
   if (kk3 == 2) {
     kk3 = 0;
   }

   goto ln01;

ln03:

  /* Normal intersection.  */
   t1 = d1/d0;
   if ( (t1 < -0.0000001) || (t1 > 1.0000001) ) {
      goto ln01;
   }

   t2 = d2/d0;
   if ( (t2 < -0.0000001) || (t2 > 1.0000001) ) {
      goto ln01;
   }

   kk3 = 1;


ln01:

   *pt1 = t1;
   *pt2 = t2;

   return kk3;
}



/**************************************************/
/* lns: intersection point of two lines           */
/**************************************************/
/* int: kk3, double: t1, t2;  double:d0, d1,d2, a1, b1 */
/* lns determines whether lines defined by two point
 * sets intersect.  It is called by dc03(), dc04(),
 * dc10() and dc13(). w0 is the domain scale and
 * scales the tolerance values.
 */
int lns_new_no_goto(double w0,
                    double j1x1, double j1y1, double j1x2, double j1y2,
                    double j2x1, double j2y1, double j2x2, double j2y2,
                    double * pt1, double * pt2) {

   double c1;

  /* determinants */
   double d0, d1, d2;

  /* FIXME: What are these for? */
   double b1;
   double a1;

  /* kk3=0 no intersection.
   * kk3=1 output t1 t2 parameters.
   */
   int kk3 = 0;

   double x21, y21, x34, y34, x31, y31, x41, y41;

  /* t1 and t2 are parameters in the equation of
   * two lines.  For line segments, 0 <= t1 <= 1
   * and 0 <= t2 <= 1.  These are given as t and T
   * in GHS diss. page 181. or BSM page 148.
   * O'Rourke uses r and s as the parameters, which
   * is probably more standard.
   */
   double t1 = 0;
   double t2 = 0;

   // Joint 1
   x21 = j1x2 - j1x1;
   y21 = j1y2 - j1y1;

   // Joint 2
   x34 = j2x1 - j2x2;
   y34 = j2y1 - j2y2;

   x31 = j2x1 - j1x1;
   y31 = j2y1 - j1y1;

   x41 = j2x2 - j1x1;
   y41 = j2y2 - j1y1;

  /* d0, d1, d2 are determinants.
   */
   d0 = x21*y34 - x34*y21;   /* equation | |   */
   d1 = x31*y34 - x34*y31;   /* | | for sol t1 */
   d2 = x21*y31 - x31*y21;   /* | | for sol t2 */



  /* p1 p2 p3 p4  4 points co-line   */
   if ( ( fabs(d0) < (0.000000001*w0*w0) ) ) {

      if ( fabs(d1) < (0.000000001*w0*w0) ) {

        /* p1 p2 p3 p4  4 points in same line. */
         if ( fabs(x21) > fabs(y21) ) {
            a1 = x21;
            b1 = x31;
         } else {
            a1 = y21;
            b1 = y31;
         }

        /* (x3 y3) lies in p1 p2 segment. */
         t1 = b1/a1;

         if ( (t1 >= -0.0000001) && (t1 <= 1.0000001) ) {
            t2 = 0;
            kk3 = 1;
         }

         if ( fabs(x21) > fabs(y21) ) {
            a1 = x21;
            b1 = x41;
         } else {
            a1 = y21;
            b1 = y41;
         }


        /* (x4 y4) lies in p1 p2 segment                  */
        /* both p3 p4   in p1 p2 segment no intersection  */
         c1 = b1/a1;
         if ( (c1< -0.0000001) || (c1 > 1.0000001) ) {
            goto ln01;  /* ie. return;  */
         }

         t1 = b1/a1;
         t2 = 1;

         kk3 += 1;
         if (kk3 == 2) {
           kk3 = 0;
         }

         goto ln01;
      } else {
         return 0;
      }
   }


  /* Normal intersection.  */
   t1 = d1/d0;
   if ( (t1 < -0.0000001) || (t1 > 1.0000001) ) {
      goto ln01;
   }

   t2 = d2/d0;
   if ( (t2 < -0.0000001) || (t2 > 1.0000001) ) {
      goto ln01;
   }

   kk3 = 1;


ln01:

   *pt1 = t1;
   *pt2 = t2;

   return kk3;
}


unsigned int
check_segment_overlap(double * t1, double * t2, double x21, double y21, double x31, double y31,
                      double x41, double y41) {

   int kk3 = 0;
   double a1, b1, c1;

  /* p1 p2 p3 p4  4 points in same line. */
   if ( fabs(x21) > fabs(y21) ) {
      a1 = x21;
      b1 = x31;
   } else {
      a1 = y21;
      b1 = y31;
   }

  /* (x3 y3) lies in p1 p2 segment. */
  *t1 = b1/a1;

   if ( (*t1 >= -0.0000001) && (*t1 <= 1.0000001) ) {
     *t2 = 0;
      kk3 = 1;
   }

   if ( fabs(x21) > fabs(y21) ) {
      a1 = x21;
      b1 = x41;
   } else {
      a1 = y21;
      b1 = y41;
   }

  /* (x4 y4) lies in p1 p2 segment                  */
  /* both p3 p4   in p1 p2 segment no intersection  */
   c1 = b1/a1;
   if ( (c1< -0.0000001) || (c1 > 1.0000001) ) {
      return kk3;
   }

  *t1 = b1/a1;
  *t2 = 1;

   kk3 += 1;
   if (kk3 == 2) {
      kk3 = 0;
   }

   return kk3;

}


int
lns_new_no_goto_no_t(double w0,
                double j1x1, double j1y1, double j1x2, double j1y2,
                double j2x1, double j2y1, double j2x2, double j2y2,
                double * t1, double * t2) {


  /* determinants */
   double d0, d1, d2;

  /* kk3=0 no intersection.
   * kk3=1 output t1 t2 parameters.
   */
   int kk3 = 0;

   double x21, y21, x34, y34, x31, y31, x41, y41;

  /* t1 and t2 are parameters in the equation of
   * two lines.  For line segments, 0 <= t1 <= 1
   * and 0 <= t2 <= 1.  These are given as t and T
   * in GHS diss. page 181. or BSM page 148.
   * O'Rourke uses r and s as the parameters, which
   * is probably more standard.
   */
  *t1 = 0;
  *t2 = 0;

   // Joint 1
   x21 = j1x2 - j1x1;
   y21 = j1y2 - j1y1;
   // Joint 2
   x34 = j2x1 - j2x2;
   y34 = j2y1 - j2y2;
   x31 = j2x1 - j1x1;
   y31 = j2y1 - j1y1;
   x41 = j2x2 - j1x1;
   y41 = j2y2 - j1y1;


  /* d0, d1, d2 are cross products. */
   d0 = cross_product(x21,y21,x34,y34);
   d1 = cross_product(x31,y31,x34,y34);
   d2 = cross_product(x21,y21,x31,y31);

  /* p1 p2 p3 p4  4 points co-line   */
   if ( ( fabs(d0) < (0.000000001*w0*w0) ) ) {

      if ( fabs(d1) < (0.000000001*w0*w0) ) {

         return check_segment_overlap(t1,t2,x21,y21,x31,y31,x41,y41);
#if 0
         double a1, b1, c1;

        /* p1 p2 p3 p4  4 points in same line. */
         if ( fabs(x21) > fabs(y21) ) {
            a1 = x21;
            b1 = x31;
         } else {
            a1 = y21;
            b1 = y31;
         }

        /* (x3 y3) lies in p1 p2 segment. */
        *t1 = b1/a1;

         if ( (*t1 >= -0.0000001) && (*t1 <= 1.0000001) ) {
           *t2 = 0;
            kk3 = 1;
         }

         if ( fabs(x21) > fabs(y21) ) {
            a1 = x21;
            b1 = x41;
         } else {
            a1 = y21;
            b1 = y41;
         }

        /* (x4 y4) lies in p1 p2 segment                  */
        /* both p3 p4   in p1 p2 segment no intersection  */
         c1 = b1/a1;
         if ( (c1< -0.0000001) || (c1 > 1.0000001) ) {
            return kk3;
         }

        *t1 = b1/a1;
        *t2 = 1;

         kk3 += 1;
         if (kk3 == 2) {
           kk3 = 0;
         }

         return kk3;
#endif

      } else {

        /* Parallel, no intersection. */
         return 0;
      }
   }


  /* Normal intersection.  */
  *t1 = d1/d0;
   if ( (*t1 < -0.0000001) || (*t1 > 1.0000001) ) {
      return 0;
   }

  *t2 = d2/d0;
   if ( (*t2 < -0.0000001) || (*t2 > 1.0000001) ) {
      return 0;
   }

   return 1;
}



int
dc_line_intersection(double w0, double * j1, double * j2, double * t1, double * t2) {

     return lns_new_no_goto_no_t(w0,j1[1],j1[2],j1[3],j1[4],j2[1],j2[2],j2[3],j2[4],t1,t2);
}


#ifdef __cplusplus
}
#endif
