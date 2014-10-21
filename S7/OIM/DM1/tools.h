#ifndef TOOLS_H
#define TOOLS_H

#define BLOCK_SIZE 8

/**
  Diallo Alpha Oumar Binta (21007631)
  Groupe 3.2
*/
/**
	Args data struct
*/
typedef struct{
  int compress;
  char inFilename[256];
  char outFilename[256];
} s_args;

void usage(char * progname);
void parseArgs(char *argv[], s_args* args);

/**
	Iterator data struct
*/
typedef struct{
    int i; //row index
    int j; //col index
    int state; //state
}Iterator;
/**
  iteratorHasNext
  in : an iterator
  out :
    1 if next iterator exist else 0
*/
int iteratorHasNext(Iterator iter);
/**
    initIterator
    in : an iterator
*/
void initIterator(Iterator* iter);
/**
  blocIteratorNext
  in : an iterator
  set the next iterator with zig zag scheme
*/
void blocIteratorNext(Iterator* iter);

#endif
