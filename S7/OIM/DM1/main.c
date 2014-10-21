#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <sys/time.h>
#include <omp.h>
#include "image.h"
#include "tools.h"

/**
  Diallo Alpha Oumar Binta (21007631)
  Groupe 3.2
*/

/**
  put DCT values in image output
*/
void putDCTValues(image *output, float *data, const int xpos, const int ypos);
/**
  compute image DCT
*/
void computeImgDCT(image img, image output, s_args args);
/**
  Quantize Img
*/
void quantize(float dctData[BLOCK_SIZE*BLOCK_SIZE], int data[BLOCK_SIZE*BLOCK_SIZE]);
/**
  put DCT values in image output
*/
void putQUANTIZEValues(image *output, int *data, const int xpos, const int ypos);
/**
  quantify image
*/
void quantifyImg(image img, image output, s_args args);
/**
  vectorize quantified values
*/
void vectorize(int quantizeData[BLOCK_SIZE*BLOCK_SIZE], int data[BLOCK_SIZE*BLOCK_SIZE]);
/**
  Put data in image
*/
void putValues(image *output, int *data, int offset);
/**
  vectorize Image
*/
void vectorizeImg(image img, image output, s_args args);
/**
  set values compressed in image
*/
void putCompressedValues(image *output, int *vectorData, int *offset);
/**
  compress Image
*/
void compressImg(image img, image output, s_args args);
/**
  decompress Image
*/
void decompressImg(image img, image output, s_args args);

double get_time() {

  struct timeval tv;

  gettimeofday(&tv, (void *)0);

  return (double) tv.tv_sec + tv.tv_usec*1e-6;

}


int main(int argc, char *argv[]){

  s_args args;
  if(argc!=4){
    usage(argv[0]);
  }
  else{
    parseArgs(argv, &args);
  }

  image img;
  image output;

  if(args.compress == 0){
    readCompressed(args.inFilename, &img);
  } else {
    readPgm(args.inFilename, &img);
  }
  output.w = img.w;
  output.h = img.h;
  output.data = malloc(sizeof(pixel_t)*output.w*output.h);

  //double computeTime, start, stop;
  //start = get_time();
    
  switch(args.compress) {
    case 0 :
        // decompression
        //decompressImg(img, output, args);
        break;
    case 1 :
        // compression
        compressImg(img, output, args);
        break;
    case 2 :
        // test dct
        computeImgDCT(img, output, args);
        break;
    case 3 :
        // test quantify
        quantifyImg(img, output, args);
        break;
    case 4 :
        // test vectorize
        vectorizeImg(img, output, args);
        break;
    case 5 :
        // compute and print error
        
        break;
    default :
        usage(argv[0]);
  }
 // stop = get_time();
  //computeTime = stop-start;
  //printf("%s\t\t\t%f\n", args.inFilename, computeTime);
  
  free(img.data);
  free(output.data);
  
  return 0;
}

