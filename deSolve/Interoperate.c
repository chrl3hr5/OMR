#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int R_Operation(double time_start, double time_end, double time_step, double parameter_r, double parameter_K, double state, double* output, size_t output_size)
{
  char cmd[1000]="";
  strcat(cmd, "Rscript OMR.R ");
  
  char str1[100];
  sprintf(str1, "%g", time_start); // Store the integer value time_start as string representation
  strcat(cmd, str1);
  strcat(cmd, " ");
  
  char str2[100];
  sprintf(str2, "%g", time_end); // Store the integer value time_end as string representation
  strcat(cmd, str2);
  strcat(cmd, " ");
  
  char str3[100];
  sprintf(str3, "%g", time_step); // Store the real value time_step as string representation
  strcat(cmd, str3);
  strcat(cmd, " ");
  
  char str4[100];
  sprintf(str4, "%g", parameter_r); // Store the real value parameter_r as string representation
  strcat(cmd, str4);
  strcat(cmd, " ");
  
  char str5[100];
  sprintf(str5, "%g", parameter_K); // Store the integer value parameter_K as string representation
  strcat(cmd, str5);
  strcat(cmd, " ");
  
  char str6[100];
  sprintf(str6, "%g", state); // Store the real value state as string representation
  strcat(cmd, str6);
  strcat(cmd, " ");

  // printf("\nCheck the input : %s",cmd);

  // Create a buffer to read output from console
  int buffersize = 100000;
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
    char *array[2002];
    int i = 0;
    while (p != NULL)
    {
      array[i++] = p;
      p = strtok (NULL, " ");
    }
    for (int i = 0; i < 2002; ++i)
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