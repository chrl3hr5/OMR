model R_OM

  function interoperate
    input Integer[1] V1;
    input Integer[1] V2;
    output Integer result;
  external "C" annotation(Library={"Interoperate", "R"}, LibraryDirectory="modelica://R_OM");
  end interoperate;

  Integer[1] V1,V2; Integer result;
equation
  V1 = {13};
  V2 = {21};
  result = interoperate(V1,V2);
end R_OM;