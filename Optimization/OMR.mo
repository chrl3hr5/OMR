model R_OM

  function R_Operation
    input Real initial_par;
	input String method;
	input Real lower;
	input Real upper;
	input Real maxit;
	input String hessian;
    output Real[5] result;
  external "C" annotation(Library={"Interoperate", "Function.dll", "Gradient.dll"}, LibraryDirectory="modelica://R_OM");
  end R_Operation;

  Real initial_par,lower,upper,maxit; String method,hessian; Real[5] result; Real par,value,fn_counts,gr_counts,convergence;
algorithm
  initial_par := 20;
  method := "Nelder-Mead";
  lower := -1000;
  upper := 1000;
  maxit := 10000;
  hessian := "FALSE";
  result := R_Operation(initial_par,method,lower,upper,maxit,hessian);
  par := result[1];
  value := result[2];
  fn_counts := result[3];
  gr_counts := result[4];
  convergence := result[5];
  
end R_OM;