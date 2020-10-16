model R_OM

  function R_Operation
    input Integer[1] par;
	input String method;
	input Integer[1] lower;
	input Integer[1] upper;
	input Integer[1] maxit;
	input String hessian;
    output Integer result;
  external "C" annotation(Library={"Interoperate", "Function.dll", "Gradient.dll"}, LibraryDirectory="modelica://R_OM");
  end R_Operation;

  Integer[1] par,lower,upper,maxit; String method,hessian; Integer result;
equation
  par = {20};
  method = "Nelder-Mead";
  lower = {-1000};
  upper = {1000};
  maxit = {10000};
  hessian = "FALSE";
  result = R_Operation(par,method,lower,upper,maxit,hessian);
end R_OM;