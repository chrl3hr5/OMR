#include <stdio.h>
#include <Rmath.h>

int R_Operation(double V1, double V2)
{
	// Find minimum
	double result = imin2(V1,V2);
	// Apply gamma function
	double result=gammafn(result);
	printf("%lf\n",result);
	return result;
}

