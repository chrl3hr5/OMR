#include <R.h>
#include <Rinternals.h>
#include <math.h>

SEXP fn(SEXP x) 
{
  SEXP result = PROTECT(allocVector(REALSXP, 1));
  REAL(result)[0] = 10*sin(0.3*asReal(x))*sin(1.3*pow(asReal(x),2)) + 0.00001*pow(asReal(x),4) + 0.2*asReal(x) + 80;
  UNPROTECT(1);
  return result;
}