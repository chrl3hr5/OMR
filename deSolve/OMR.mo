model R_OM

  function R_Operation
    input Real time_start;
	input Real time_end;
	input Real time_step;
	input Real parameter_r;
	input Real parameter_K;
	input Real state;
	output Real[1001] result;
  external "C" annotation(Library={"Interoperate"}, LibraryDirectory="modelica://R_OM");
  end R_Operation;

  Real time_start,time_end,time_step,parameter_r,parameter_K,state; Real[1001] result; Real value;
algorithm
  time_start := 0;
  time_end := 10;
  time_step := 0.01;
  parameter_r := 1.5;
  parameter_K := 10;
  state := 0.1;
  result := R_Operation(time_start,time_end,time_step,parameter_r,parameter_K,state);
  value := result[400];
  
end R_OM;