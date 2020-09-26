#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int R_Operation(const int *V1, size_t V1_size, const int *V2, size_t V2_size)
{
  char cmd[100]="";
  strcat(cmd, "Rscript OMR.R ");
  char str1[2];
  sprintf(str1, "%d", V1[0]); // store the integer value V1[0] as string representation
  strcat(cmd, str1);
  char str2[2];
  sprintf(str2, " %d", V2[0]); // store the integer value V2[0] as string representation
  strcat(cmd, str2);
  printf("\nCheck the command : %s\n ", cmd);

  // pass inputs as command line arguments
  // char *cmd = "Rscript test.R 5 100"; // static input 5 and 100 to add.R

  //create a buffer to read output from console
  int buffersize = 100;
  char buf[buffersize];
  FILE *fp;

  if ((fp = popen(cmd, "r")) == NULL) {
    printf("Error opening pipe!\n");
    return -1;
  }
  int finalvalue;
  while (fgets(buf, buffersize, fp) != NULL) {
    // Do whatever you want here... // post proceess the result
    //printf("%i %s", strlen(buf),buf);
    char str[strlen(buf)];
    strcpy(str, buf);
    //printf("%s",str);
    char final[2];
    //printf("check char pos : %c", str[1]);
    int index=0;
    for (int i =0; i < strlen(buf)-1; i++)
    {
      if (i>3) // R outputs as [1] 100, we must skip the first 4 characters to read the actual value from R
      {
        //printf("\n check char pos : %c", str[i]);
        final[index] = str[i];
        index= index+1;
      }
    }
    finalvalue =atoi(final); // convert the value to integer as the model expects result as integer
    //printf("\n final value : %s", final);
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
