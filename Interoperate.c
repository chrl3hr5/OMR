#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Rmath.h>
#include <Rinternals.h>
#include <Rembedded.h>

// C version of R's source() function.
void source(const char *name)
{
  SEXP expr;
  PROTECT(expr = lang2(install("source"), mkString(name)));
  R_tryEval(expr, R_GlobalEnv, NULL);
  UNPROTECT(1);  
  printf("'source()' executed successfully\n");
}

int  R_add(int alen, int a[])
{
    // Allocate an R vector and copy the C array into it.
    SEXP arg;
    PROTECT(arg = allocVector(INTSXP, alen));
    memcpy(INTEGER(arg), a, alen * sizeof(int));

    // Setup a call to the R function
    SEXP add_call;
    PROTECT(add_call = lang2(install("add"), arg));

    // Execute the function
    int errorOccurred;
    SEXP ret = R_tryEval(add_call, R_GlobalEnv, &errorOccurred);
    printf("R returned: ");
    double *val = REAL(ret);
	for (int i = 0; i < LENGTH(ret); i++) printf("%f ", val[i]);
    printf("\n");
	int result = floor(val[0]);
    UNPROTECT(2);
    return result;
}


int interoperate(const int *V1, size_t V1_size, const int *V2, size_t V2_size)
{
    // Intialize the embedded R environment to execute external R script
    int r_argc = 2;
    char *r_argv[] = {"R", "--silent"};
    Rf_initEmbeddedR(r_argc, r_argv);
    source("Sum.R");

	// Getting results from external R script
    int arg[] = {V1[0], V2[0]};
    int result=R_add(2, arg);

    // Release the embedded R environment
	Rf_endEmbeddedR(0);
    printf("\n Exited the R embedded environment");
    exit(0); // force exit from R embedded environment
    return(result);
}
