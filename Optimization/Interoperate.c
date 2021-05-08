#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int R_Operation(double initial_par, const char *method, double lower, double upper, double maxit, const char *hessian, double* output, size_t output_size)
{
  char cmd[1000]="";
  strcat(cmd, "Rscript OMR.R ");
  
  char str1[100];
  sprintf(str1, "%g", initial_par); // Store the integer value initial_par as string representation
  strcat(cmd, str1);
  strcat(cmd, " ");
  
  char str2[100];
  sprintf(str2, "%s", method); // Store the string value method
  strcat(cmd, str2);
  strcat(cmd, " ");
  
  char str3[100];
  sprintf(str3, "%g", lower); // Store the integer value lower as string representation
  strcat(cmd, str3);
  strcat(cmd, " ");
  
  char str4[100];
  sprintf(str4, "%g", upper); // Store the integer value upper as string representation
  strcat(cmd, str4);
  strcat(cmd, " ");
  
  char str5[100];
  sprintf(str5, "%g", maxit); // Store the integer value maxit as string representation
  strcat(cmd, str5);
  strcat(cmd, " ");
  
  char str6[100];
  sprintf(str6, "%s", hessian); // Store the string value hessian
  strcat(cmd, str6);

  // printf("\nCheck the input : %s",cmd);

  // Create a buffer to read output from console
  int buffersize = 100;
  char buf[buffersize];
  FILE *fp;

  if ((fp = popen(cmd, "r")) == NULL) {
    printf("Error while opening pipe!\n");
  }
  
  while (fgets(buf, buffersize, fp) != NULL) {
    // printf("\nOutput value : %s", buf);
    char str[strlen(buf)];
    strcpy(str, buf);

    // printf("\n Copied Output value : %s", str);

    // Split the string and store it in char array
    char *p = strtok(str, " ");
    char *array[5];
    int i = 0;
    while (p != NULL)
    {
      array[i++] = p;
      p = strtok (NULL, " ");
    }
    for (int i = 0; i < 5; ++i)
    {
      // printf("%s\n", array[i]);
      // Copy the output
      output[i] = atof(array[i]);
	  // printf("%f\n", output[i]);
    }
    return 0;
  }
  pclose(fp);
  return 0;
}