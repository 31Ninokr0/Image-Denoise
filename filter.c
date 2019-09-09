#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

// Bubblesort
void sort(int size, int array[]){
  for(int i=0; i<size; i++){
    for(int j=i+1; j<size; j++){
        if(array[i] > array[j]){
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        };
    };
  };
};

int average(int size, int array[]){
  int result= 0;
  for(int i = 0; i < size; i++){
    result += array[i];
  };
  return result/size;
};

RGB *readPPM(const  char *file, int *width, int *height, int *max){
  FILE *fp; fp = fopen(file, "rb");
  if (!fp) { printf("Can't open %s\n", file); return 0; };
  fscanf(fp, "P3 %d %d %d", width, height, max);
  RGB *ppmArray = malloc((* width) * (* height)*sizeof(RGB));
  int i = 0;
  while(i < (* width) * (* height)){
    fscanf(fp, "%hhd %hhd %hhd ", &ppmArray[i].r, &ppmArray[i].g, &ppmArray[i].b);
    i++;
  };
  fclose(fp);
  return ppmArray;
};

void writePPM(const  char *file, int width, int height, int max, const RGB *image){
  FILE *fp; fp = fopen (file, "wb");
  int i = 0;
  fprintf(fp, "P3 %d %d %d ", width, height, max);
  while(i < (width * height)){
    fprintf(fp, "%d %d %d ", image[i].r, image[i].g, image[i].b);
    i++;
  };
  fclose(fp);
};

RGB *denoiseImage(int width, int height, const RGB *image, int n, filter f){

  RGB *ppmArray = malloc(width*height * sizeof(RGB));
  RGB *temp = malloc(n*n * sizeof(RGB));
  int a = n/2;
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      int tot = 0;
      int red[n*n], green[n*n], blue[n*n];
      for (int s = (y-a); s <= (y+a); s++){
        for(int k = (x-a); k <= (x+a); k++){
          if( k >= 0 && k < width && s >= 0 && s < height){
            red[tot]   = image[(s*width) + k].r;
            green[tot] = image[(s*width) + k].g;
            blue[tot]  = image[(s*width) + k].b;
            tot++;
          };
        };
      };
      if (f == MEDIAN){
        sort(tot, red);
        sort(tot, green);
        sort(tot, blue);
        temp->r = red[tot/2];
        temp->g = green[tot/2];
        temp->b = blue[tot/2];
        ppmArray[(y*width) + x] = *temp;
      }else if (f == MEAN){
        temp->r = average(tot, red);
        temp->g = average(tot, green);
        temp->b = average(tot, blue);
        ppmArray[(y*width) + x] = *temp;
      };
    };
  };
  return ppmArray;
};
