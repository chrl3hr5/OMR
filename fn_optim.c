#include <R.h>
#include <Rinternals.h>
#include <math.h>

SEXP fn(SEXP x) 
{
  SEXP result = PROTECT(allocVector(REALSXP, 1));
  REAL(result)[0] = pow(asReal(x),-1)*100 + pow(asReal(x),-3)*exp(asReal(x));
  UNPROTECT(1);
  return result;
}