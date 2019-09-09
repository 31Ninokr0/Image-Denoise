#include<sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter.h"

double getTime(int flag) {
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  struct timeval user_time, sys_time;
  user_time = usage.ru_utime;
  sys_time  = usage.ru_stime;
  if (flag==1)
    return user_time.tv_sec+user_time.tv_usec/1e6;
  if (flag==2)
    {
      return user_time.tv_sec+sys_time.tv_sec + (user_time.tv_usec+sys_time.tv_sec)/1e6;
    }
  return -1;
};

int main(int argc, char *argv[]) {

  if (argc < 5){
      printf("\n Wrong number of command line arguments\n");
      printf("./denoise [IMAGE path] [IMAGE dst] [Change Value] [M for median or A for mean filter]\n");
      return 1;
  };

  int width, height, max;
  int a = 1;
  int b = 2;

  double time0 = getTime(a);
  RGB *ptr = readPPM(argv[1], &width, &height, &max);;
  time0 = getTime(b)-time0;
  printf("\nReading file %s\n", argv[1]);
  printf("***   %s read   %.1e seconds\n\n", argv[1], time0);

  double time1 = getTime(a);
  if(   strcmp(argv[4], "A") == 0  )  {
    RGB *ptr2 = denoiseImage(width, height, ptr, atoi(argv[3]), MEAN);
    time1 = getTime(b)-time1;
    printf("\nProcessing %d x %d image using %d x %d window and mean filter\n", width, height, atoi(argv[3]), atoi(argv[3]));
    printf("***   image processed in %.1e seconds\n\n", time1);

    double time2 = getTime(a);
    writePPM(argv[2], width, height, max, ptr2);
    time2 = getTime(b)-time2;
    printf("\nWriting file %s\n", argv[2]);
    printf("***   %s written in %.1e seconds\n\n", argv[2], time2);

  }else if (  strcmp(argv[4], "M") == 0  ) {
    RGB *ptr2 = denoiseImage(width, width, ptr, atoi(argv[3]), MEDIAN);
    time1 = getTime(b)-time1;
    printf("\nProcessing %d x %d image using %d x %d window and median filter\n", width, height, atoi(argv[3]), atoi(argv[3]));
    printf("***   image processed in %.1e seconds\n\n", time1);

    double time2 = getTime(a);
    writePPM(argv[2], width, height, max, ptr2);
    time2 = getTime(b)-time2;
    printf("\nWriting file %s\n", argv[2]);
    printf("***   %s written in %.1e seconds\n\n", argv[2], time2);
  };

  return 0;
};
