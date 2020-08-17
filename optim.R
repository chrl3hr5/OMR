if(file.exists('fn.dll'))
{ 
  dyn.load('fn.dll')
  fn <- function(x) 
  {
    .Call("fn", x)
  }
}
optimization <- function(par,maxit,method) 
{
  cat("INPUTS: ","\n");
  cat("\tpar: ",par,"\n");
  cat("\tmaxit: ",maxit,"\n");
  cat("\tmethod: ",method,"\n");
  cat("OUTPUTS: ","\n");
  result <- optim(par,fn,method = method,control = list(maxit = maxit))
  return(c(result$par,result$value,result$counts['function'],result$convergence))
}