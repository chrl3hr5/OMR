<h1 align="center">OMR</h1>
<h3 align="center">
Interoperability between R and OpenModelica
</h3>

[![DOI](https://zenodo.org/badge/287344008.svg)](https://doi.org/10.5281/zenodo.21607359)

---

## Introduction

<div align="justify">
OpenModelica is a free and open-source environment for modeling, simulating, optimizing and analyzing complex dynamic systems. It is based on the Modelica modeling language [1]. It has limited statistical capabilities. The motivation behind this project is to enhance OpenModelica's statistical functionalities. It was achieved by developing interoperability between it and another open-source programming language known as R. R is a language and environment for statistical computing and graphics [2].
</div>
<br/>

<div align="justify">
It was a challenging problem. At the time of development, there was no interface available for public use, which enables OpenModelica to pass instructions to R in the form of values (numeric, string, etc.) and commands, and obtain back required results. However, it is possible to run external C, Python, Matlab and Julia code in OpenModelica [3].
</div>
<br/>

---

## System Specifications

The interface was developed and tested under the following configuration:
- Windows 10 (64-bit operating system) machine
- R 3.6.3 (64-bit) 
- OpenModelica v1.16.0-dev-371-geb234c072 (64-bit)

---

## How to Use

1. Download and unzip the OMR GitHub repository files present [here](https://github.com/chrl3hr5/OMR).
<p align="center">
  <img width="955" height="489" alt="OMR GitHub repository." src="https://github.com/user-attachments/assets/fa6c84eb-b078-4810-9fea-b12d6b787a32" />
</p>

2. Run "msys2_shell" as administrator which is present in the OpenModelica installation directory, as shown in the figure below. "msys2" is a software distribution and building platform for Windows which provides a UNIX-like interface [4].
<p align="center">
  <img width="693" height="475" alt="Running 'msys2_shell' from the OpenModelica installation directory." src="https://github.com/user-attachments/assets/fd612d95-8176-4b79-86cc-753684d06aa4" />
</p>

3. (Application Example 1) **Performing general-purpose optimization** - Using the built-in *optim()* function of R.
 - Open the "Instructions.txt" file present in the unzipped OMR GitHub repository (OMR-master) folder and follow the instructions written in it.
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

 - Create the required DLL files associated with the "Function.c" and "Gradient.c" files. *Note: Commands to generate the required DLL files were added to the main program file "OMR.mos". Hence, there is no need to run them separately.*

 - Run the main program file "OMR.mos" by executing the command "omc OMR.mos". It simulates the OpenModelica model and provides results in the form of a CSV file.
<p align="center">
  <img width="641" height="383" alt="Simulation results." src="https://github.com/user-attachments/assets/0c0c847f-c599-4536-a639-47c1bdf1e866" />
</p>
<p align="center">
  <img width="740" height="74" alt="Results stored in the 'R_OM_res.csv' file." src="https://github.com/user-attachments/assets/81308ceb-e310-4156-a28c-65d3d26ffcd6" />
</p>

*Note: Change the R version in the code of the "OMR.mos" file if it does not matches with the one present on your local machine.*
<br/>

 - (OPTIONAL) Run "make clean" command to delete all files which were generated during simulation except for "R_OM_res.csv".
<p align="center">
  <img width="455" height="241" alt="Removing les which were generated during simulation." src="https://github.com/user-attachments/assets/41907c18-a33e-47ce-8e83-509ad6cb5b5e" />
</p>

4. (Application Example 2) **Solving ordinary differential equations** - Using the *ode()* function from *deSolve* package of R .
 - The procedure is similar to the one mentioned in the item 3. The instructions written in the "Instructions.txt" file must be followed, beginning with setting the directory containing all files associated with the process of solving ordinary differential equations as the current working directory.
<p align="center">
  <img width="455" height="240" alt="Changing the current working directory." src="https://github.com/user-attachments/assets/5ab33893-78ed-4f93-a416-4d999f9d12d9" />
</p>

 - Add PATH values associated with the installed OpenModelica and R versions to the system PATH. *Note: Make necessary changes (if required) to the PATH values
before executing the commands.*
<p align="center">
  <img width="455" height="240" alt="Adding PATH values." src="https://github.com/user-attachments/assets/816b8dbe-517e-41c3-ae06-83f1efeabd02" />
</p>

 - As the code associated with the ordinary differential equation to be solved was present in the R file. Therefore, there is no need to create any DLL file.

 - Run the main program file "OMR.mos" by executing the command "omc OMR.mos". It simulates the OpenModelica model and provides results in the form of a CSV file.
<p align="center">
  <img width="641" height="383" alt="Simulation results." src="https://github.com/user-attachments/assets/a1073f8c-b3b5-407c-a37f-4c89c0fb2179" />
</p>
<p align="center">
  <img width="821" height="73" alt="Results stored in the 'R_OM_res.csv'file." src="https://github.com/user-attachments/assets/9f67e650-6c07-4065-896b-316f09f55181" />
</p>

*Note: Change the R version in the code of the "OMR.mos" file if it does not matches with the one present on your local machine.*
<br/>

 - (OPTIONAL) Run "make clean" command to delete all files which were generated during simulation except for "R_OM_res.csv".
<p align="center">
  <img width="455" height="240" alt="Removing les which were generated during simulation." src="https://github.com/user-attachments/assets/75fea337-d95c-4d80-a24b-c369635633f2" />
</p>

---

## Publication Details

| Attribute | Details |
| :--- | :--- |
| **Title** | Interoperability between R and OpenModelica |
| **Event** | [OpenModelica Annual Workshop 2022](https://openmodelica.org/events/openmodelica-workshop/openmodelica-program-2022-a/) |
| **Date** | January 31, 2022 |
| **Organizers** | Open Source Modelica Consortium (OSMC) and Linköping  University (LIU)|
| **Presentation** | [Slides / Access Link](https://openmodelica.org/images/M_images/OpenModelicaWorkshop_2022/1420_OMR_Interoperability.pdf) |

---

## Citation

If you use this interface or build upon this project in your research, please cite the workshop presentation:

### Plain Text
> 

### BibTeX
```bibtex

```

---

## References

[1] P. Fritzson et al., “The OpenModelica Integrated Environment for Modeling, Simulation, and Model-Based Development,” Model. Identif. Control, vol. 41, no. 4, pp. 241–295, 2020, doi: 10.4173/mic.2020.4.1.  
[2] R Core Team, R: A Language and Environment for Statistical Computing. Vienna, Austria: R Foundation for Statistical Computing, 2021. [Online]. Available: https://www.R-project.org/  
[3] Open Source Modelica Consortium, “OpenModelica User’s Guide.” Open Source Modelica Consortium (OSMC), c/o Linköpings universitet, Department of Computer and Information Science, SE-58183 Linköping, Sweden, Linköping, Sweden, Apr. 06, 2021. [Online]. Available: https://openmodelica.org/doc/OpenModelicaUsersGuide/1.16/  
[4] MSYS2 Software Distribution and Building Platform for Windows. [Online]. Available: https://www.msys2.org/
