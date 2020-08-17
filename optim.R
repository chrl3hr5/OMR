# Replace with "fn_optim.so" for Linux.
if(file.exists('fn_optim.dll'))
{ 
  dyn.load('fn_optim.dll')
  fn <- function(x) 
  {
    .Call("fn", x)
  }
}
R_optim <- function(par,maxit,method) 
{
  cat("\n# R function: optim()\n")
  cat("INPUTS: ","\n");
  cat("\tpar: ",par,"\n");
  cat("\tmethod: ",method,"\n");
  cat("\tmaxit: ",maxit,"\n");
  cat("OUTPUTS: ","\n");
  result <- suppressWarnings(optim(par,fn,method = method,control = list(maxit = maxit)))
  dyn.unload('fn_optim.dll')
  return(as.numeric(c(result$par,result$value,result$counts['function'],result$convergence)))
}