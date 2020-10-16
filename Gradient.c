#include <R.h>
#include <Rinternals.h>
#include <math.h>

SEXP gr(SEXP x) 
{
  SEXP result = PROTECT(allocVector(REALSXP, 1));
  REAL(result)[0] = 10*(sin(0.3*asReal(x))*(2.6*(asReal(x)*cos(1.3*pow(asReal(x),2)))) + 0.3*(cos(0.3*asReal(x))*sin(1.3*pow(asReal(x),2)))) + 0.00004*pow(asReal(x),3) + 0.2;
  UNPROTECT(1);
  return result;
}