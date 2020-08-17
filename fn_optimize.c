#include <R.h>
#include <Rinternals.h>
#include <math.h>

SEXP fn(SEXP x) 
{
  SEXP result = PROTECT(allocVector(REALSXP, 1));
  REAL(result)[0] = pow(asReal(x),2)-asReal(x);
  UNPROTECT(1);
  return result;
}