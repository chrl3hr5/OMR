args <- commandArgs(trailingOnly = TRUE)

# Arguments
par <- args[1]
method <- args[2]
lower <- args[3]
upper <- args[4]
maxit <- args[5]
hessian <- eval(parse(text=args[6]))

# Replace with "Function.so" for Linux.
dyn.load('Function.dll')
fn <- function(x) 
  {
    .Call("fn", x)
  }

# Replace with "Gradient.so" for Linux.
dyn.load('Gradient.dll')
gr <- function(x) 
{
  .Call("gr", x)
}

if(method=="Nelder-Mead")
{
  res <- suppressWarnings(optim(par = par, fn = fn, method = method, control = list(maxit = maxit), hessian = hessian))
  print(round(res$par))
}
if(method=="BFGS")
{
  res <- suppressWarnings(optim(par = par, fn = fn, gr = gr, method = method, control = list(maxit = maxit), hessian = hessian))
  print(round(res$par))
}
if(method=="CG")
{
  res <- suppressWarnings(optim(par = par, fn = fn, gr = gr, method = method, control = list(maxit = maxit), hessian = hessian))
  print(round(res$par))
}
if(method=="L-BFGS-B")
{
  res <- suppressWarnings(optim(par = par, fn = fn, gr = gr, method = method, lower = lower, upper = upper, control = list(maxit = maxit), hessian = hessian))
  print(round(res$par))
}
if(method=="SANN")
{
  res <- suppressWarnings(optim(par = par, fn = fn, method = method, control = list(maxit = maxit), hessian = hessian))
  print(round(res$par))
}
if(method=="Brent")
{
  res <- suppressWarnings(optim(par = par, fn = fn, method = method, lower = lower, upper = upper, control = list(maxit = maxit), hessian = hessian))
  print(round(res$par))
}

dyn.unload('Gradient.dll')
dyn.unload('Function.dll')

# Storing output to file.
# cat(result,file="Output.txt",sep="\n")