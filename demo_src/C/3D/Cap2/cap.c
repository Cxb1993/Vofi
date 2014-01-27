#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cap.h"

typedef const double creal;
typedef const int cint;
typedef double real;


/* -------------------------------------------------------------------------- *
 * DESCRIPTION (reference phase where f(x,y,z) < 0):                          *
 * ellipsoidal cap inside the domain [-1,1]x[0,1]x[0,1]                       *
 * f(x,y) = c1*x^2 + c2*y^2 + c3*x*y + c4*x + c5*y - c6                       *
 * f(x,y,z) = f(x,y) + (z-ZC)^2/C2                                            *
 * INPUT PARAMETERS:                                                          *
 * (XC,YC,ZC) center of the ellipsoid; ALPHA: angle between two axes x' and   *
 * x (in the x-y plane); (A1,B1,C1): semiaxis along the three ellipsoid       *
 * (local) axes: x',y',z'                                                     *
 * -------------------------------------------------------------------------- */

real impl_func(creal xy[])
{
  double x,y,z,A2,B2,C2,ca,sa,c1,c2,c3,c4,c5,c6,f0;

  x = xy[0];
  y = xy[1];
  z = xy[2];

  A2 = A1*A1;
  B2 = B1*B1;
  C2 = C1*C1;
  ca = cos(ALPHA);
  sa = sin(ALPHA);
  c1 = ca*ca/A2 + sa*sa/B2;
  c2 = sa*sa/A2 + ca*ca/B2;
  c3 = 2.*ca*sa*(B2-A2)/(A2*B2);
  c4 = -(2.*c1*XC + c3*YC);
  c5 = -(2.*c2*YC + c3*XC);
  c6 = 1.0 - (c1*XC*XC + c2*YC*YC + c3*XC*YC);
  
  f0 = c1*x*x + c2*y*y + c3*x*y + c4*x + c5*y - c6 + (z - ZC)*(z - ZC)/C2;

  return f0;
}

/* -------------------------------------------------------------------------- */

void check_volume(creal vol_n)
{
  double h0,vol_a;

  h0 = C1 + ZC;
  vol_a = MYPI*A1*B1*h0*h0*(1. - h0/(3.*C1))/C1;

  fprintf (stdout,"-----------------------------------------------------------\n");
  fprintf (stdout,"------------------ C: cap check (2 cells) -----------------\n");
  fprintf (stdout,"analytical volume: %23.16e\n",vol_a);
  fprintf (stdout,"numerical  volume: %23.16e\n\n",vol_n);
  fprintf (stdout,"absolute error   : %23.16e\n",fabs(vol_a-vol_n));
  fprintf (stdout,"relative error   : %23.16e\n",fabs(vol_a-vol_n)/vol_a); 
  fprintf (stdout,"-----------------------------------------------------------\n");
  fprintf (stdout,"with Intel i7 3.4 GHz + Linux openSUSE 13.1 + gcc 4.8.1 -O2\n");
  fprintf (stdout,"-----------------------------------------------------------\n");
  fprintf (stdout,"analytical volume:  9.4090699975015856e-03\n");
  fprintf (stdout,"numerical  volume:  9.4090693179627247e-03\n\n");
  fprintf (stdout,"absolute error   :  6.7953886094540561e-10\n");
  fprintf (stdout,"relative error   :  7.2221681964938654e-08\n");
  fprintf (stdout,"---------------- C: end cap check (2 cells) ---------------\n");
  fprintf (stdout,"-----------------------------------------------------------\n");
  fprintf (stdout,"\n");

  return;
}
