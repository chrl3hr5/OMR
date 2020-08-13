optimization <- function(par,maxit,text) 
{
  cat("method: ",text,"\n");
  cat("par: ",par,"\n");
  cat("maxit: ",maxit,"\n");
  return(sum(par,maxit))
}