model R_OM

  function R_Operation
    input Real V1;
	input Real V2;
    output Real result;
  external "C" annotation(Library={"Interoperate","-LC:/PROGRA~1/R/R-3.6.3/bin/x64 -lR -lm"}, LibraryDirectory={"modelica://R_OM"},Include="#include \"Interoperate.h\"");
  end R_Operation;

  Real V1, V2, result;
  algorithm
	V1 := 210;
	V2 := 106;
	result := R_Operation(V1,V2);

end R_OM;