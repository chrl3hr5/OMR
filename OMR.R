args <- commandArgs(trailingOnly = TRUE)

# Replace with "Function.so" for Linux.
dyn.load('Function.dll')
fn <- function(x) 
  {
    .Call("fn", x)
  }

res <- optim(as.numeric(args[1])+as.numeric(args[2]), fn, method = "SANN",control = list(maxit = 20000, temp = 20, parscale = 20))
print(round(res$par))

dyn.unload('Function.dll')

# Storing output to file.
# cat(result,file="Output.txt",sep="\n")