#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "image.h"
#include "tools.h"
#include "dct-idct.h"

/**
  Diallo Alpha Oumar Binta (21007631)
  Groupe 3.2
*/
static const float qMatrix[BLOCK_SIZE*BLOCK_SIZE] = {
    16, 11, 10, 16, 24, 40, 51, 61,
    12, 12, 14, 19, 26, 58, 60, 55,
    14, 13, 16, 24, 40, 57, 69, 56,
    14, 17, 22, 29, 51, 87, 80, 62,
    18, 22, 37, 56, 68, 109, 103, 77,
    24, 35, 55, 64, 81, 104, 113, 92,
    49, 64, 78, 87, 103, 121, 120, 101,
    72, 92, 95, 98, 112, 100, 103, 99
    };

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

/**
    initIterator
    in : an iterator
*/
void initIterator(Iterator* iter){
    iter->i = 0;
    iter->j = 0;
    iter->state = 1;
}
/**
  iteratorHasNext
  in : an iterator
  out :
    1 if next iterator exist else 0
*/
int iteratorHasNext(Iterator iter){
    return (iter.i <= (BLOCK_SIZE - 1) && iter.j <= (BLOCK_SIZE - 1));
}
/**
  blocIteratorNext
  in : an iterator
  set the next iterator with zig zag scheme
*/
void blocIteratorNext(Iterator* iter){
    iter->j += iter->state;
    iter->i -= iter->state;
    if(iter->j > (BLOCK_SIZE - 1)) {
        iter->j = (BLOCK_SIZE - 1);
        iter->i += 2;
    }else if(iter->i > (BLOCK_SIZE - 1)) {
        iter->i = (BLOCK_SIZE - 1);
        iter->j += 2;
    }else if(iter->j < 0){
        //ne pas sortir du bloc
        iter->j = 0;
    }else if(iter->i < 0){
        //ne pas sortir du bloc
        iter->i = 0;
    }else{
        //pas de changement d'etat
        return;
    }
    //changement d'etat
    iter->state *= -1;
}

/**
	put DCT values in image output
*/
void putDCTValues(image *output, float *data, const int xpos, const int ypos){
    float value;

    for (int y = 0; y < BLOCK_SIZE; ++y){
      for (int x = 0; x < BLOCK_SIZE; ++x)
        {
            value = data[y*BLOCK_SIZE+x]/8.f;
            *pixelPtr(output, x+xpos, y+ypos) =  (pixel_t) value;
        }
    }
}
/**
	compute image DCT
*/
void computeImgDCT(image img, image output, s_args args){

    float *data = malloc(sizeof(float)*BLOCK_SIZE*BLOCK_SIZE);
    int i=0,j=0;

    for (i = 0; i < img.h; i += BLOCK_SIZE) 
    { 
        for (j = 0; j < img.w; j+= BLOCK_SIZE) 
        {
            dct(&img, data, i, j);
            putDCTValues(&output, data, i, j);          
        }        
    }

    free(data);
    writePgm(args.outFilename, &output);
}
/**
	Quantize Img
*/
void quantize(float dctData[BLOCK_SIZE*BLOCK_SIZE], int data[BLOCK_SIZE*BLOCK_SIZE]){

    for (int y = 0; y < BLOCK_SIZE; ++y)
    {
        for (int x = 0; x < BLOCK_SIZE; ++x)
        {
            data[y*BLOCK_SIZE+x] = round(dctData[y*BLOCK_SIZE+x]/qMatrix[y*BLOCK_SIZE+x]);
        }
    }

}
/**
	put DCT values in image output
*/
void putQUANTIZEValues(image *output, int *data, const int xpos, const int ypos){

    for (int y = 0; y < BLOCK_SIZE; ++y){
        for (int x = 0; x < BLOCK_SIZE; ++x)
        {
            *pixelPtr(output, x+xpos, y+ypos) =  (pixel_t) data[y*BLOCK_SIZE+x];
        }
    }

}
/**
	quantify image
*/
void quantifyImg(image img, image output, s_args args){

    int *quantizeData = malloc(sizeof(int)*BLOCK_SIZE*BLOCK_SIZE);
    float *dctData = malloc(sizeof(float)*BLOCK_SIZE*BLOCK_SIZE);

    for (int i = 0; i < img.h; i += BLOCK_SIZE) {
      for (int j = 0; j < img.w; j+= BLOCK_SIZE) 
        {
            dct(&img, dctData, i, j);
            quantize(dctData, quantizeData);
            putQUANTIZEValues(&output, quantizeData, i, j);          
        }
    }

    free(quantizeData);
    free(dctData);
    writePgm(args.outFilename, &output);
}
/**
	vectorize quantified values
*/
void vectorize(int quantizeData[BLOCK_SIZE*BLOCK_SIZE], int data[BLOCK_SIZE*BLOCK_SIZE]){

    Iterator iter;
    int i = 0;

    initIterator(&iter);
    do{
        data[i] = quantizeData[iter.i*BLOCK_SIZE+iter.j];        
        blocIteratorNext(&iter);
        i++;
    }while(iteratorHasNext(iter));
}
/**
	Put data in image
*/
void putValues(image *output, int *data, int offset){

  for (int x = 0; x < (BLOCK_SIZE*BLOCK_SIZE); ++x)
  {
    output->data[x+offset] =  (pixel_t) data[x];
  }
}
/**
	vectorize Image
*/
void vectorizeImg(image img, image output, s_args args){

    int *quantizeData = malloc(sizeof(int)*BLOCK_SIZE*BLOCK_SIZE);
    int *vectorizeData = malloc(sizeof(int)*BLOCK_SIZE*BLOCK_SIZE);
    float *dctData = malloc(sizeof(float)*BLOCK_SIZE*BLOCK_SIZE);
    int offset = 0;

    for (int i = 0; i < img.h; i += BLOCK_SIZE){
        for (int j = 0; j < img.w; j+= BLOCK_SIZE) 
        {
            dct(&img, dctData, j, i);
            quantize(dctData, quantizeData);
            vectorize(quantizeData, vectorizeData);
            putValues(&output, vectorizeData, offset);
            offset += BLOCK_SIZE*BLOCK_SIZE;
        }
        
    }

    free(quantizeData);
    free(vectorizeData);
    free(dctData);
    writePgm(args.outFilename, &output);
}
/**
	set values compressed in image
*/
void putCompressedValues(image *output, int *vectorData, int *offset){

  int index = 0, val=0;
  for (int i = 0; i < BLOCK_SIZE*BLOCK_SIZE; ++i)
  {
    if (vectorData[i] != 0)
    {
      index = i;
      val++;
    }
  }
  
  if (val == 0){
    output->data[*offset] =  (pixel_t) 0;
    *offset += 1;
    output->size = *offset;
    return;
  }

  index++;
  output->data[*offset] =  (pixel_t) index;

  for (int i = 1; i <= index; ++i)
  {
    output->data[i+(*offset)] =  (pixel_t) vectorData[i-1];
  }

  *offset += index+1;
  output->size = *offset;
}
/**
	compress Image
*/
void compressImg(image img, image output, s_args args){

    int *quantizeData = malloc(sizeof(int)*BLOCK_SIZE*BLOCK_SIZE);
    int *vectorizeData = malloc(sizeof(int)*BLOCK_SIZE*BLOCK_SIZE);
    float *dctData = malloc(sizeof(float)*BLOCK_SIZE*BLOCK_SIZE);
    int offset = 0;

    for (int i = 0; i < img.h; i += BLOCK_SIZE){
        for (int j = 0; j < img.w; j+= BLOCK_SIZE) 
        {
            dct(&img, dctData, j, i);
            quantize(dctData, quantizeData);
            vectorize(quantizeData, vectorizeData);
            putCompressedValues(&output, vectorizeData, &offset);
        }
        
    }

    writeCompressed(args.outFilename, &output);
    free(quantizeData);
    free(vectorizeData);
    free(dctData);
}

/*
void getVectorizedData(image img, int *xpos, int *ypos, int nbValue,
 int data[BLOCK_SIZE*BLOCK_SIZE]){
 
 int flag = -1;
 
 for(int y = 0; y < BLOCK_SIZE; ++y){
    for(int x = 0; x < BLOCK_SIZE; ++x){
        if(flag == -1){
            flag = 0;
            continue;
        }
        data[flag] = (int) *pixelPtr(&img, x+(*xpos), y+(*ypos));
        flag++;
        if(flag == nbValue){
            *xpos += x;
            *ypos += y;
            return;
        }
    }
 }
}

void compute(image img, float dctData[BLOCK_SIZE*BLOCK_SIZE], int *offset){

    int vectorizedData[BLOCK_SIZE*BLOCK_SIZE];

        //get significant value
        int nbSignificantValue = (int) img.data[*offset];
        //init array to 0        
        memset(vectorizedData, 0, sizeof(int)*BLOCK_SIZE*BLOCK_SIZE);
        //do we have significant values
        if(nbSignificantValue > 0){
            for(int k = 0; k < nbSignificantValue; ++k){
                vectorizedData[k] = img.data[*offset+k+1];
            }
        }
        //quantified values and dct
        for(int y = 0; y < BLOCK_SIZE; ++y){
            for(int x = 0; x < BLOCK_SIZE; ++x){
                dctData[y*BLOCK_SIZE+x] = vectorizedData[y*BLOCK_SIZE+x]*qMatrix[y*BLOCK_SIZE+x];
            }
        }
        *offset+=nbSignificantValue;

}

void decompressImg(image img, image output, s_args args){

    
   float dctData[BLOCK_SIZE*BLOCK_SIZE];
    


   int offset=0;
   for(int y = 0; y < img.h; y+=8){
       for(int x = 0; x < img.w; x+=8){
        printf("\nsi=%d\n", offset);
           compute(img, dctData, &offset);
           

       }
   }


    printf("size=%d h=%d w=%d name=%s\n", img.size, img.h, img.w, args.inFilename);
    writePgm(args.outFilename, &output);

    
}
*/