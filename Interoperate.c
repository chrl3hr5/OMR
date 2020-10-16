#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int R_Operation(const int *par, size_t par_size, const char *method, const int *lower, size_t lower_size, const int *upper, size_t upper_size, const int *maxit, size_t maxit_size, const char *hessian)
{
  char cmd[1000]="";
  strcat(cmd, "Rscript OMR.R ");
  char str1[100];
  sprintf(str1, "%d", par[0]); // Store the integer value par[0] as string representation
  strcat(cmd, str1);
  strcat(cmd, " ");
  char str2[100];
  sprintf(str2, "%s", method); // Store the string value method as string representation
  strcat(cmd, str2);
  strcat(cmd, " ");
  char str3[100];
  sprintf(str3, "%d", lower[0]); // Store the integer value lower[0] as string representation
  strcat(cmd, str3);
  strcat(cmd, " ");
  char str4[100];
  sprintf(str4, "%d", upper[0]); // Store the integer value upper[0] as string representation
  strcat(cmd, str4);
  strcat(cmd, " ");
  char str5[100];
  sprintf(str5, "%d", maxit[0]); // Store the integer value maxit[0] as string representation
  strcat(cmd, str5);
  strcat(cmd, " ");
  char str6[100];
  sprintf(str6, "%s", hessian); // Store the string value hessian as string representation
  strcat(cmd, str6);
  printf("\nCheck the command : %s\n ", cmd);

  //Pass inputs as command line arguments
  //char *cmd = "Rscript test.R 5 100"; // Static input 5 and 100 to test.R

  //Create a buffer to read output from console
  int buffersize = 1000;
  char buf[buffersize];
  FILE *fp;

  if ((fp = popen(cmd, "r")) == NULL) {
    printf("Error while opening pipe!\n");
    return -1;
  }
  int finalvalue;
  while (fgets(buf, buffersize, fp) != NULL) {
    //Add optional code for post processing of result
    //printf("%i %s", strlen(buf),buf);
    char str[strlen(buf)];
    strcpy(str, buf);
    //printf("%s",str);
    char final[2];
    //printf("Check char position : %c", str[1]);
    int index=0;
    for (int i =0; i < strlen(buf)-1; i++)
    {
      if (i>3) // R outputs as [1] 100, first four characters must be skipped to read the actual value from R
      {
        //printf("\n Check char position : %c", str[i]);
        final[index] = str[i];
        index = index+1;
      }
    }
    finalvalue =atoi(final); // convert the value to integer as the model expects result as an integer
    printf("\n Final value : %s", final);
    printf("\n The result is : %d ", finalvalue);
    return finalvalue;
  }

  int status = pclose(fp);
  if (status == -1) {
    /* Error reported by pclose() */
    fprintf(stderr, "%s\n", fp);

  }
  return 0;
}