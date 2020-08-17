// Including header files.
#include <stdio.h>
#include <string.h>
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

// Wrapper for R function "R_optim," defined in optim.R file.
void optim(int size1, double par[], int size2,  int maxit[], int size3, char *method)
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
    SET_STRING_ELT(v3, 0, mkChar(method));
    UNPROTECT(3);

    // Setup a call to the R function.
    SEXP optim_call;
    PROTECT(optim_call = lang4(install("R_optim"), v1, v2, v3));
    UNPROTECT(1);

    // Execute the function.
    int errorOccurred;
    SEXP ret_optim = R_tryEval(optim_call, R_GlobalEnv, &errorOccurred);
    
    // Output when no error occur.
    if (!errorOccurred)
    {
        printf("R returned: ");
        double *val = REAL(ret_optim);
        for (int i = 0; i < LENGTH(ret_optim); i++) printf("%f ", val[i]);
        printf("\n");
    }

    // Output when error occur.
    else
    {
        printf("Error occurred calling R\n");
    }
}

// Wrapper for R function "R_optimize," defined in optimize.R file.
void optimize(int size4, double lower[], int size5, double upper[], int size6,  double tol[])
{
    // Allocate an R vector of numeric values and copy a C double array into it.
    SEXP v4;
    PROTECT(v4 = allocVector(REALSXP, size4));
    memcpy(REAL(v4), lower, size4 * sizeof(double));

    // Allocate an R vector of numeric values and copy a C double array into it.
    SEXP v5;
    PROTECT(v5 = allocVector(REALSXP, size5));
    memcpy(REAL(v5), upper, size5 * sizeof(double));

    // Allocate an R vector of numeric values and copy a C double array into it.
    SEXP v6;
    PROTECT(v6 = allocVector(REALSXP, size6));
    memcpy(REAL(v6), tol, size6 * sizeof(double));
    UNPROTECT(3);

    // Setup a call to the R function.
    SEXP optimize_call;
    PROTECT(optimize_call = lang4(install("R_optimize"), v4, v5, v6));
    UNPROTECT(1);

    // Execute the function.
    int errorOccurred;
    SEXP ret_optimize = R_tryEval(optimize_call, R_GlobalEnv, &errorOccurred);
    
    // Output when no error occur.
    if (!errorOccurred)
    {
        printf("R returned: ");
        double *val = REAL(ret_optimize);
        for (int i = 0; i < LENGTH(ret_optimize); i++) printf("%f ", val[i]);
        printf("\n");
    }

    // Output when error occur.
    else
    {
        printf("Error occurred calling R\n");
    }
}

int main(int argc, char *argv[])
{
    // Intialize the embedded R environment.
    int r_argc = 2;
    char *r_argv[] = { "R", "--silent" };
    Rf_initEmbeddedR(r_argc, r_argv);

    // Provide input values.
    double v1[] = {1.2};
    int v2[] = {1000};
    char *method = "Nelder-Mead";
    double v4[] = {-10};
    double v5[] = {10};
    double v6[] = {0.001};

    // Invoke functions in R.
    source("optim.R");
    optim(1, v1, 1, v2, 1, method);
    source("optimize.R");
    optimize(1, v4, 1, v5, 1, v6);

    // Release R environment.
    Rf_endEmbeddedR(0);

    return(0);
}