// Including header files.
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Rinternals.h>
#include <Rembedded.h>

// C version of R's source() function.
void source(const char *name)
{
    SEXP expr;
    PROTECT(expr = lang2(install("source"), mkString(name)));
    R_tryEval(expr, R_GlobalEnv, NULL);
    UNPROTECT(1);
}

// Wrapper for R function "optimization," defined in optim.R file.
void R_optimization(int size1, double par[], int size2,  int maxit[], int size3, char *method)
{
    // Allocate an R vector of numeric values and copy a C double array into it.
    SEXP v1;
    PROTECT(v1 = allocVector(REALSXP, size1));
    memcpy(REAL(v1), par, size1 * sizeof(double));

    // Allocate an R vector of integer values and copy a C integer array into it.
    SEXP v2;
    PROTECT(v2 = allocVector(INTSXP, size2));
    memcpy(INTEGER(v2), maxit, size2 * sizeof(int));

    // Allocate an R vector and set a C character string into it.
    SEXP v3;
    PROTECT(v3 = allocVector(STRSXP, 1));
    SET_STRING_ELT( v3, 0, mkChar(method) );
    UNPROTECT(1);

    // Setup a call to the R function.
    SEXP optimization_call;
    PROTECT(optimization_call = lang4(install("optimization"), v1, v2, v3));

    // Execute the function.
    int errorOccurred;
    SEXP ret = R_tryEval(optimization_call, R_GlobalEnv, &errorOccurred);
    
    // Output when no error occur.
    if (!errorOccurred)
    {
        printf("R returned: ");
        double *val = REAL(ret);
        for (int i = 0; i < LENGTH(ret); i++) printf("%0.1f ", val[i]);
        printf("\n");
    }

    // Output when error occur.
    else
    {
        printf("Error occurred calling R\n");
    }
    
    UNPROTECT(2);
}

int main(int argc, char *argv[])
{
    // Intialize the embedded R environment.
    int r_argc = 2;
    char *r_argv[] = { "R", "--silent" };
    Rf_initEmbeddedR(r_argc, r_argv);
    double v1[] = {1.2};
    int v2[] = {1000};
    char *method = "Nelder-Mead";

    // Invoke a function in R
    source("optim.R");
    R_optimization(1, v1, 1, v2, 3, method);

    // Release R environment
    Rf_endEmbeddedR(0);
    getch();
    return(0);
}