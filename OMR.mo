model R_OM

  function R_Operation
    input Integer[1] V1;
    input Integer[1] V2;
    output Integer result;
  external "C" annotation(Library="Interoperate", LibraryDirectory="modelica://R_OM");
  end R_Operation;

  Integer[1] V1,V2; Integer result;
equation
  V1 = {20};
  V2 = {17};
  result = R_Operation(V1,V2);
end R_OM;