#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "image.h"
#include "dct-idct.h"

typedef struct{
  int compress;
  char inFilename[256];
  char outFilename[256];
} s_args;

#define BLOCK_SIZE 8

void parseArgs(char *argv[], s_args* args){
  args->compress = atoi(argv[1]);
  strncpy(args->inFilename, argv[2], 256);
  strncpy(args->outFilename, argv[3], 256);
}

void usage(char * progname) {
    printf("usage : %s mode in out\n", progname);
    printf("mode \t 0 : decompression, 1 : compression, 2 : save dct (pgm format),\n\t 3 : save quantize (pgm format), 4 : save vectorize (xxx format), 5 output compression loss\n");
    printf("in : input filename, pgm if compression, save dct or save quantize, xxx if decompression\n");
    printf("out : output filename, xxx if compression, pgm if decompression, save dct or save quantize\n");
    exit(EXIT_FAILURE);
	
}

void putInVect(image *output, float *data, const int xpos, const int ypos){
    int i,j;
    float value;
	for (i = 0; i < BLOCK_SIZE; ++i)
		for (j = 0; j < BLOCK_SIZE; ++j)
		{
			value = data[i*BLOCK_SIZE+j]/8.f;
			output->data[(i+xpos)*output->w+(j+ypos)] =  (pixel_t)value;
		}
}

void getData(image *tga, float data[BLOCK_SIZE*BLOCK_SIZE], const int xpos, const int ypos)
{
	int u,v;
	for (v=0; v<BLOCK_SIZE; v++)
		for (u=0; u<BLOCK_SIZE; u++)
		{

			data[v*BLOCK_SIZE+u] = tga->data[(v+xpos)*tga->w+(u+ypos)];
		}
}

void computeDCT(s_args args){
	image img;
	image output;

	readPgm(args.inFilename, &img);
	output.w = img.w;
	output.h = img.h;

	float *data = malloc(sizeof(float)*BLOCK_SIZE*BLOCK_SIZE);
	output.data = malloc(sizeof(pixel_t)*output.w*output.h);

	int i = 0,j = 0;

    for (i = 0; i < img.h; i += BLOCK_SIZE) 
    { 
        for (j = 0; j < img.w; j+= BLOCK_SIZE) 
        {
            dct(&img, data, i, j);
            putInVect(&output, data, i, j);            
        }        
    }
	writePgm(args.outFilename, &output);
	free(output.data);
	free(img.data);
	free(data);
}


int main(int argc, char *argv[]){
  s_args args;
  if(argc!=4){
    usage(argv[0]);
  }
  else{
    parseArgs(argv, &args);
  }

  // image img;
  // image output;
	
  switch(args.compress) {
	case 0 :
		// decompression
		
		break;
	case 1 :
		// compression
		
		break;
	case 2 :
		// test dct
		computeDCT(args);
		break;
	case 3 :
		// test quantify
		
		break;
	case 4 :
		// test vectorize
		
		break;
	case 5 :
		// compute and print error
		
		break;
	default :
		usage(argv[0]);
  }
  return 0;
}
