args <- commandArgs(trailingOnly = TRUE)

# Arguments
time_start <- args[1]
time_end <- args[2]
time_step <- args[3]
parameter_r <- args[4]
parameter_K <- args[5]
state <- args[6]

# Creating required R objects
# 1) Time sequence
time <- seq(from=as.numeric(time_start), to=as.numeric(time_end), by=as.numeric(time_step))
time <- as.numeric(time)
# 2) Parameters
parameters <- c(r = as.numeric(parameter_r), K = as.numeric(parameter_K))
# 3) Initial conditions
state <- c(x = as.numeric(state))

# Loading package
if(!("deSolve" %in% rownames(installed.packages()))){install.packages("deSolve",lib = .libPaths()[1],repos = "http://cran.us.r-project.org")}
library(deSolve)

# Creating logistic equation
logistic <- function(t, state, parameters){
  with(
    as.list(c(state, parameters)),{
      dx <- r*x*(1-x/K)
      return(list(dx))
    }
  )
}

# Solving Ordinary Differential Equation
out <- ode(y = state, times = time, func = logistic, parms = parameters)
out <- as.data.frame(out)

# Results
result <- c(out$time,out$x)

cat(result)

# Storing output to file
# cat(result,file="Output.txt",sep="\n")