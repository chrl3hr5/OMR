# Replace with "fn_optimize.so" for Linux.
if(file.exists('fn_optimize.dll'))
{ 
  dyn.load('fn_optimize.dll')
  fn <- function(x) 
  {
    .Call("fn", x)
  }
}
R_optimize <- function(lower,upper,tol) 
{
  cat("\n# R function: optimize()\n")
  cat("INPUTS: ","\n");
  cat("\tlower: ",lower,"\n");
  cat("\tupper: ",upper,"\n");
  cat("\ttol: ",tol,"\n");
  cat("OUTPUTS: ","\n");
  result <- optimize(fn,lower = lower,upper = upper,tol = tol)
  dyn.unload('fn_optimize.dll')
  return(as.numeric(c(result$minimum,result$objective)))
}