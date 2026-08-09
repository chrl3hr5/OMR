<h1 align="center">OMR: Interoperability between R and OpenModelica</h1>

[![DOI](https://zenodo.org/badge/287344008.svg)](https://doi.org/10.5281/zenodo.21607359)

---

# Introduction

<div align="justify">
OpenModelica is a free and open-source environment for modeling, simulating, optimizing and analyzing complex dynamic systems. It is based on the Modelica modeling language [1]. When this project began, it had limited statistical capabilities.
</div>
<br/>

<div align="justify">
The motivation behind this project was to enhance OpenModelica's statistical functionalities. It was achieved by developing interoperability between it and another open-source programming language known as R. R is a language and environment for statistical computing and graphics [2].
</div>
<br/>

<div align="justify">
It was a challenging problem. At the time of development, there was no interface available for public use, which enables OpenModelica to pass instructions to R in the form of values (numeric, string, etc.) and commands, and obtain back required results. However, it is possible to run external C, Python, Matlab and Julia code in OpenModelica [3].
</div>
<br/>

---

# System Specifications

This interface was developed and tested under the following configuration:
- Windows 10 (64-bit operating system) machine
- OpenModelica v1.16.0-dev-371-geb234c072 (64-bit)
- R 3.6.3 (64-bit)

---

# How it Works

As it is possible to run external C code in OpenModelica, we took advantage of this feature to connect with R using two different methods -
1. Applying the R API.
2. Running external R script.

## Applying the R API

The R API allows a user access to entry points in the R executable/DLL (Dynamic Link Library) that can be called from C code. These entry points are declared in the installed header files associated with R [4]. [Writing R Extensions](https://cran.r-project.org/doc/manuals/r-release/R-exts.html#The-R-API), is a manual for R written by the R Core Team [2] which provides information to access the most stable entry points [4].

The R API makes it possible to utilize various R functions from C by adding appropriate header files to the C code. Following is the procedure to implement interoperability between R and OpenModelica using the R API -
1. Creating an OpenModelica model.
2. Simulating the model and executing the external C code.
3. Running R program from the external C code.
4. Ending the simulation after obtaining results back into the OpenModelica model.

While the R API offers broad functionality, its scope was limited at the time of this project's development and it did not support access to functions from user-installed R packages.

## Running external R script

In this method we run an external R script from OpenModelica via C. The external R script contains functions which are needed to be implemented depending upon the problem statement and it receives inputs from OpenModelica. The functions can be from base R or form a user-installed R package. This method overcomes the limitations of R API by giving the user option to work with functions from any package in R. Except for minor adjustments, the procedure to implement interoperability is the same as shown in the previous method -
1. Creating an OpenModelica model.
2. Simulating the model and executing the external C code.
3. Running R program from the external C code.
4. Ending the simulation after obtaining results back into the OpenModelica model.

---

# Demonstration

The following subsections shall explain each interoperability step in detail by making use of the below mentioned statistical computation examples -
1. General-purpose Optimization
2. Solving Ordinary Differential Equations

For the implementation of any operation other than the ones shown in the examples, changes need to be made to the code files.

*Note: For the "external R script" method of interoperability between R and OpenModelica, it is necessary to know in advance the data type and count of outputs to be obtained from the R program.*

### General-purpose Optimization

#### Creating an OpenModelica model

The model contains a function, an algorithm with input and output variables and a call to external C code, [Interoperate.c](Optimization/Interoperate.c) and DLL (Dynamic Link Library) files. The input variables, namely `initial_par`, `method`, `lower`, `upper`, `maxit` and `hessian`, are in association with the parameters used in the `optim()` function of R that performs function optimization. Each input variable is given some value which is later passed to the external C code. The output variables include `par`, `value`, `fn_counts`, `gr_counts` and `convergence`. Their values are obtained from the external C code [Interoperate.c](Optimization/Interoperate.c). The DLL files are associated with two additional C code files required by the R program for its optimization operation.

The code for OpenModelica model is given in the [OMR.mo](Optimization/OMR.mo) file.

#### Simulating the model and executing the external C code

The simulation begins by executing the OpenModelica model and is followed by running the external C code ([Interoperate.c](Optimization/Interoperate.c)). The C code passes all input values from the OpenModelica model to the R program and runs it via the command line. Once the processing is done, the C code reads the output printed to the console by the R program and delivers it to the OpenModelica model.

The external C code is given in the [Interoperate.c](Optimization/Interoperate.c) file. The `R_Operation` function in the C code takes in all the input values provided by the OpenModelica model, stores them as string values, and then passes them to the R program for processing via command line. It later reads the output, which is generated and printed to the console by the R program as a single string value. Then the string is split into multiple strings using a single space as the delimiter. Finally, the obtained values are stored in a character array. For this operation, it is necessary to know the desired number of outputs in advance. Later, each value of the character array is converted into a floating-point number and then passed to the OpenModelica model.

#### Running R program from the external C code

The R program optimizes a mathematical function using a variety of methods. Some methods also require the presence of a gradient. Therefore, two additional C code files were created, one containing the function to be optimized, [Function.c](Optimization/Function.c) and the other containing the gradient, [Gradient.c](Optimization/Gradient.c). Both files include a simple mathematical function. Later, the DLLs for these two C files were created so that their content becomes accessible to the R program. The [Function.c](Optimization/Function.c) file's code represents the following equation -

```math
y = 10 * \sin(0.3 * x) * \sin(1.3 * x^2) + 0.00001 * x^4 + 0.2 * x + 80
```

And the [Gradient.c](Optimization/Gradient.c) file's code represents the following equation -

```math
y = 10 * (\sin(0.3 * x) * (2.6 * (x * \cos(1.3 * x^2)))) + 0.3 * (\cos(0.3 * x) * \sin(1.3 * x^2))) + 0.00004 * x^3 + 0.2
```

At the C-level, all R objects are stored in a common datatype, the `SEXP`, or `S-expression`. All R objects are S-expressions so every C function that is created must return a SEXP as output and take SEXPs as inputs. A SEXP is a variant type, with subtypes for all R's data structures. `REALSXP` type is for a numeric vector. `allocVector()` is a function which creates an R-level object. It takes two arguments, the type of SEXP (or SEXPTYPE) to create, and the length of the vector. `PROTECT()` function is used to inform R that an object is in use and should not be deleted if the garbage collector gets activated. It is necessary to make sure that every protected object is unprotected. The function `UNPROTECT()` unprotects protected objects. It takes a single integer argument, `n`, and unprotects the last `n` objects that were protected. The number of protects and unprotects must match [5]. To use the above mentioned types and functions, `R.h` and `Rinternals.h` header files were included in the code.

When the R code gets executed, it first access the values passed to it via command-line by making use of the `commandArgs()` function and stores them in separate variables. It then reads the content of the additional C files ([Function.c](Optimization/Function.c) and [Gradient.c](Optimization/Gradient.c)) by loading their associated DLLs with the help of the `dyn.load()` function. After obtaining all necessary input data, depending upon the method of optimization (`Nelder-Mead`, `BFGS`, `CG`, `L-BFGS-B`, `SANN` or `Brent`) passed to it, it performs the required optimization operation. Once the operation ends successfully, it unloads all DLLs using the `dyn.unload()` function and prints the final output to the console. The complete R code is given in the [OMR.R](Optimization/OMR.R) file.

#### Ending the simulation after obtaining results back into the OpenModelica model

The results printed to the console by R were later read by the C code ([Interoperate.c](Optimization/Interoperate.c)) and the obtained values were stored in a single character array. The size of the character array must be declared in advance and it depends upon the expected number of output values to be obtained from R. Each element of the character array is then passed as a numeric value back to the OpenModelica model. These numeric values were then stored in the output variables, namely `par`, `value`, `fn_counts`, `gr_counts` and `convergence`. Following is a plot of the obtained values -

<p align="center">
  <img width="641" height="383" alt="Plotting results obtained after simulating the OpenModelica model." src="https://github.com/user-attachments/assets/db7bb147-aa6d-4ea0-a501-85775b48a8a7" />
</p>

The simulation ends after returning a CSV file containing values of the output variables with the name `R_OM_res.csv`.

### Solving Ordinary Differential Equations

#### Creating an OpenModelica model

Similar to the previous section, the OpenModelica model contains a function, an algorithm with input and output variables and a call to external C code, [Interoperate.c](deSolve/Interoperate.c). But this time, no DLL files are required because the ordinary differential equations are written in R itself. It is optional for the user to define the mathematical functions to operate upon either in C or R depending on their preference. The input variables, namely `time_start`, `time_end`, `time_step`, `parameter_r`, `parameter_K` and `state`, are in association with the parameters used in the `ode()` function of the `deSolve` package of R. The `ode()` function solves a system of ordinary differential equations in R. Each input variable is given some value which is later passed to the external C code. The output variables are `time_value` and `output_value`. Their values are obtained from the external C code [Interoperate.c](deSolve/Interoperate.c).

The code for OpenModelica model is given in the [OMR.mo](deSolve/OMR.mo) file.

#### Simulating the model and executing the external C code

The simulation begins in the exact same manner as described previously. However, some changes were made to the [Interoperate.c](Optimization/Interoperate.c) file's code. Specifically, the parameters associated with the `R_Operation` function were changed according to the variables defined in the OpenModelica model. The size of the character array, which stores the result obtained from R, was changed from 5 to 2002. This increase in size is due to the expectation of obtaining 2002 output values from R.

#### Running R program from the external C code

The R program defines and solves a differential equation (logistic equation) by making use of the `ode()` function from `deSolve` package. The example equation used is shown below - 

```math
\frac{\partial x}{\partial t} = rx\left(1 - \frac{x}{K}\right)
```

The complete R code used to solve the above mentioned differential equation is given in the [OMR.R](deSolve/OMR.R) file.

When the R code gets executed, it first checks for the availability of `deSolve` package among the installed packages and if found absent installs it. Similar to the R code mentioned in the previous section, it also stores the values passed to it via command-line. It then creates the time sequence for which the output is required, combines the input parameters `r` and `K` into a single vector and setup the initial (state) value to be solved for the associated ordinary differential equation. Finally it makes use of the `ode()` function to solve the equation stored in the variable `logistic` and prints the final output to the console.

#### Ending the simulation after obtaining results back into the OpenModelica model

As described previously, the results printed to the console by R were passed as numeric values back to the OpenModelica model. These numeric values were then stored in the output variables, namely `time_value` and `output_value`. Following is a plot of some of the obtained values -

<p align="center">
  <img width="641" height="383" alt="Plotting results obtained after simulating the OpenModelica model." src="https://github.com/user-attachments/assets/205843c7-3e45-4e92-b4df-7ecaa6b60f8c" />
</p>

The simulation ends after returning a CSV file containing values of the output variables with the name `R_OM_res.csv`.

---

# How to Use

1. Download and unzip the OMR GitHub repository files present [here](https://github.com/chrl3hr5/OMR).
<p align="center">
  <img width="955" height="489" alt="OMR GitHub repository." src="https://github.com/user-attachments/assets/fa6c84eb-b078-4810-9fea-b12d6b787a32" />
</p>

2. Run `msys2_shell` as administrator which is present in the OpenModelica installation directory, as shown in the figure below. `msys2` is a software distribution and building platform for Windows which provides a UNIX-like interface [6].
<p align="center">
  <img width="693" height="475" alt="Running 'msys2_shell' from the OpenModelica installation directory." src="https://github.com/user-attachments/assets/fd612d95-8176-4b79-86cc-753684d06aa4" />
</p>

3. (Application Example 1) **Performing General-purpose Optimization** - Using the built-in `optim()` function of R.
 - Open the `Instructions.txt` file present in the unzipped OMR GitHub repository (OMR-master) folder and follow the instructions written in it.
<p align="center">
  <img width="618" height="191" alt="'Instructions.txt' file present in the directory containing the downloaded OMR files." src="https://github.com/user-attachments/assets/2bfab69c-96d2-4d3c-ad9f-98bbd74176d4" />
</p>

 - Set the directory containing those downloaded OMR files which are required to perform general-purpose optimization as the current working directory.
<p align="center">
  <img width="456" height="240" alt="Changing the current working directory." src="https://github.com/user-attachments/assets/7deaf589-332d-47d5-927f-775ff739aae6" />
</p>

 - Add PATH values associated with the installed OpenModelica and R versions to the system PATH. *Note: Make necessary changes (if required) to the PATH values before executing the commands.*
<p align="center">
  <img width="455" height="240" alt="Adding PATH values." src="https://github.com/user-attachments/assets/b7c23ea2-7df6-48e5-88c0-f5d3d910c3ad" />
</p>

 - Create DLLs for the `Function.c` and `Gradient.c` files. *Note: Commands to generate the required DLL files were added to the main program file `OMR.mos`. Hence, there is no need to generate them separately.*

 - Run the main program file `OMR.mos` by executing the command `omc OMR.mos`. It simulates the OpenModelica model and provides results in the form of a CSV file.
<p align="center">
  <img width="641" height="383" alt="Simulation results." src="https://github.com/user-attachments/assets/0c0c847f-c599-4536-a639-47c1bdf1e866" />
</p>
<p align="center">
  <img width="740" height="74" alt="Results stored in the 'R_OM_res.csv' file." src="https://github.com/user-attachments/assets/81308ceb-e310-4156-a28c-65d3d26ffcd6" />
</p>

*Note: Change the R version in the code of the `OMR.mos` file if it does not matches with the one present on your local machine.*
<br/>

 - (OPTIONAL) Run `make clean` command to delete all files which were generated during simulation except for the `R_OM_res.csv` file.
<p align="center">
  <img width="455" height="241" alt="Removing files which were generated during simulation." src="https://github.com/user-attachments/assets/41907c18-a33e-47ce-8e83-509ad6cb5b5e" />
</p>

4. (Application Example 2) **Solving Ordinary Differential Equations** - Using the `ode()` function from `deSolve` package of R.
 - The procedure is similar to the one mentioned in the item 3. The instructions written in the `Instructions.txt` file must be followed, beginning with setting the directory containing all files associated with the process of solving ordinary differential equations as the current working directory.
<p align="center">
  <img width="455" height="240" alt="Changing the current working directory." src="https://github.com/user-attachments/assets/5ab33893-78ed-4f93-a416-4d999f9d12d9" />
</p>

 - Add PATH values associated with the installed OpenModelica and R versions to the system PATH. *Note: Make necessary changes (if required) to the PATH values before executing the commands.*
<p align="center">
  <img width="455" height="240" alt="Adding PATH values." src="https://github.com/user-attachments/assets/816b8dbe-517e-41c3-ae06-83f1efeabd02" />
</p>

 - As the code to solve the ordinary differential equation was written in R, there is no need to create a DLL file.

 - Run the main program file `OMR.mos` by executing the command `omc OMR.mos`. It simulates the OpenModelica model and provides results in the form of a CSV file.
<p align="center">
  <img width="641" height="383" alt="Simulation results." src="https://github.com/user-attachments/assets/a1073f8c-b3b5-407c-a37f-4c89c0fb2179" />
</p>
<p align="center">
  <img width="821" height="73" alt="Results stored in the 'R_OM_res.csv' file." src="https://github.com/user-attachments/assets/9f67e650-6c07-4065-896b-316f09f55181" />
</p>

*Note: Change the R version in the code of the `OMR.mos` file if it does not matches with the one present on your local machine.*
<br/>

 - (OPTIONAL) Run `make clean` command to delete all files which were generated during simulation except for the `R_OM_res.csv` file.
<p align="center">
  <img width="455" height="240" alt="Removing les which were generated during simulation." src="https://github.com/user-attachments/assets/75fea337-d95c-4d80-a24b-c369635633f2" />
</p>

---

# Workshop Presentation

This work was presented at the OpenModelica Annual Workshop 2022; complete details regarding the event, presentation date, and organizers are provided in the table below.

| Attribute | Details |
| :--- | :--- |
| **Title** | Interoperability between R and OpenModelica |
| **Event** | [OpenModelica Annual Workshop 2022](https://openmodelica.org/events/openmodelica-workshop/openmodelica-program-2022-a/) |
| **Date** | January 31, 2022 |
| **Organizers** | Open Source Modelica Consortium (OSMC) and Linköping  University (LIU)|
| **Presentation** | [Slides / Access Link](https://openmodelica.org/images/M_images/OpenModelicaWorkshop_2022/1420_OMR_Interoperability.pdf) |

---

# Citation

If you use this interface or build upon this project in your research, please cite the repository:

## Plain Text
> Singh, D., Moudgalya, K., & Palanisamy, A. (2026). OMR: Interoperability between R and OpenModelica (Version 1.0.0) [Computer software]. https://doi.org/10.5281/zenodo.21607360

## BibTeX
```bibtex
@software{Singh_OMR_Interoperability_between_2026,
author = {Singh, Digvijay and Moudgalya, Kannan and Palanisamy, Arunkumar},
doi = {10.5281/zenodo.21607360},
month = jul,
title = {{OMR: Interoperability between R and OpenModelica}},
url = {https://github.com/chrl3hr5/OMR},
version = {1.0.0},
year = {2026}
}
```

---

# References

[1] P. Fritzson et al., “The OpenModelica Integrated Environment for Modeling, Simulation, and Model-Based Development,” Model. Identif. Control, vol. 41, no. 4, pp. 241–295, 2020, doi: 10.4173/mic.2020.4.1.  
[2] R Core Team, R: A Language and Environment for Statistical Computing. Vienna, Austria: R Foundation for Statistical Computing, 2021. [Online]. Available: https://www.R-project.org/  
[3] Open Source Modelica Consortium, “OpenModelica User’s Guide.” Open Source Modelica Consortium (OSMC), c/o Linköpings universitet, Department of Computer and Information Science, SE-58183 Linköping, Sweden, Linköping, Sweden, Apr. 06, 2021. [Online]. Available: https://openmodelica.org/doc/OpenModelicaUsersGuide/1.16/  
[4] R Core Team, “Writing R Extensions.” R Foundation for Statistical Computing, Vienna, Austria, 2021. [Online]. Available: https://cran.r-project.org/doc/manuals/r-release/R-exts.html  
[5] H. Wickham, Advanced R. in Chapman &Hall/CRC the R Series. Boca Raton: Chapman & Hall, 2015.  
[6] MSYS2 Software Distribution and Building Platform for Windows. [Online]. Available: https://www.msys2.org/
