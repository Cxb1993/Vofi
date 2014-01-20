#include <stdio.h>
#include <math.h>
#include "sine_line.h"

typedef const double creal;
typedef const int cint;
typedef double real;

/* -------------------------------------------------------------------------- *
 * DESCRIPTION (reference phase where f(x,y) < 0):                            *
 * sinusoidal line in the square [0,1]x[0,1]                                  *
 * f(x,y) = y - B0*sin(C0 pi x+ pi/D0) - A0                                   *
 * -------------------------------------------------------------------------- */

real impl_func(creal xy[]) 
{
  double x,y,f0;

  x = xy[0];
  y = xy[1];

  f0 = y - A0 - B0*sin(C0*MYPI*x + MYPI/D0);

  return f0;
}

/* -------------------------------------------------------------------------- */

void check_area(creal area_n)
{
  real area_a;

  /* analytical integration with x in [0,1]  */
  area_a = A0 + B0*(-cos((C0 + 1./D0)*MYPI) + cos(MYPI/D0))/(C0*MYPI);

  fprintf (stdout,"-----------------------------------------------------------\n");
  fprintf (stdout,"-------------------- C: sine line check -------------------\n");
  fprintf (stdout,"analytical area : %23.16e\n",area_a);
  fprintf (stdout,"numerical  area : %23.16e\n\n",area_n);
  fprintf (stdout,"absolute error  : %23.16e\n",fabs(area_a-area_n));
  fprintf (stdout,"relative error  : %23.16e\n",fabs(area_a-area_n)/area_a); 
  fprintf (stdout,"-----------------------------------------------------------\n");
  fprintf (stdout,"with Intel i7 3.4 GHz + Linux openSUSE 12.3 + gcc 4.7.2 -O3 \n");
  fprintf (stdout,"-----------------------------------------------------------\n");
  fprintf (stdout,"analytical area :  5.0000000000000000e-01\n");
  fprintf (stdout,"numerical  area :  4.9999999999993749e-01\n\n");
  fprintf (stdout,"absolute error  :  6.2505556286396313e-14\n");
  fprintf (stdout,"relative error  :  1.2501111257279263e-13\n");
  fprintf (stdout,"----------------- C: end sine line check ------------------\n");
  fprintf (stdout,"-----------------------------------------------------------\n");
  fprintf (stdout,"\n");

  return;
}