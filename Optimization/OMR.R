args <- commandArgs(trailingOnly = TRUE)

# Arguments
initial_par <- args[1]
method <- args[2]
lower <- args[3]
upper <- args[4]
maxit <- args[5]
hessian <- eval(parse(text=args[6]))

# Replace with "Function.so" for Linux
dyn.load('Function.dll')
fn <- function(x) 
  {
    .Call("fn", x)
  }

# Replace with "Gradient.so" for Linux
dyn.load('Gradient.dll')
gr <- function(x) 
{
  .Call("gr", x)
}

if(method=="Nelder-Mead")
{
  res <- suppressWarnings(optim(par = initial_par, fn = fn, method = method, control = list(maxit = maxit), hessian = hessian))
}
if(method=="BFGS")
{
  res <- suppressWarnings(optim(par = initial_par, fn = fn, gr = gr, method = method, control = list(maxit = maxit), hessian = hessian))
}
if(method=="CG")
{
  res <- suppressWarnings(optim(par = initial_par, fn = fn, gr = gr, method = method, control = list(maxit = maxit), hessian = hessian))
}
if(method=="L-BFGS-B")
{
  res <- suppressWarnings(optim(par = initial_par, fn = fn, gr = gr, method = method, lower = lower, upper = upper, control = list(maxit = maxit), hessian = hessian))
}
if(method=="SANN")
{
  res <- suppressWarnings(optim(par = initial_par, fn = fn, method = method, control = list(maxit = maxit), hessian = hessian))
}
if(method=="Brent")
{
  res <- suppressWarnings(optim(par = initial_par, fn = fn, method = method, lower = lower, upper = upper, control = list(maxit = maxit), hessian = hessian))
}

dyn.unload('Gradient.dll')
dyn.unload('Function.dll')

res_par <- round(res$par,10)
res_value <- round(res$value,10)
res_fn_counts <- as.double(res$counts[1])
res_gr_counts <- if(is.na(res$counts[2])){res$counts[2] <- as.double(0)}else{as.double(res$counts[2])}
res_convergence <- as.double(res$convergence)

cat(res_par,res_value,res_fn_counts,res_gr_counts,res_convergence)

# Storing output to file
# cat(result,file="Output.txt",sep="\n")