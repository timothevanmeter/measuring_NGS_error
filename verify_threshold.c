#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "getlines.h"

// USAGE:
// COMPILATION: 
// gcc -Wall -pedantic -o ver.o verify_threshold.c getlines.c -lm 
// EXECUTION: 
// ./ver.o <eeout.dat file> <original fastq file> 

// ###########################################################################
// ###########################################################################
// ###########################################################################
// ###########################################################################

// -----------------------------------------------------------

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\t\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

// -----------------------------------------------------------

int fileSize = 0;

// ###########################################################################
// ###########################################################################
// ###########################################################################
// ###########################################################################

int main(int argc, char **argv)
{
  FILE *file;
  char line[256];
  float num;
  fileSize = getlines(argv[2]);
  fileSize = fileSize/4;
  
  fprintf( stdout, "-----------------------------------------------------\n");

  fprintf( stdout, "\tProgram called with: %s AND %s\n", argv[1], argv[2] );
	
  file = fopen(argv[1], "r");

  double i = 0.0;
  fprintf( stdout, "-----------------------------------------------------\n");
  fprintf( stdout, "\tReading in the file:\n\tNumber of lines: %d", fileSize );

  while (fgets(line, sizeof(line), file)) {
    // printProgress(i/(double)fileSize);
    // Convert the line to a float
    num = strtof(line, NULL);
    if(num < 0.1) {
      i++;
    }    
  }
  printf( "\n\tENTRIES OF DATASET SATISFYING THE THRESHOLD: %d\n", (int)i );
  // printf( "\tPERCENTAGE OF DATASET SATISFYING THE THRESHOLD: %.4f\n\n", i/(double)fileSize );
  printf( "\tPERCENTAGE OF DATASET SATISFYING THE THRESHOLD: %.4f\n\n", i/fileSize );
  fclose(file);

  printf("-----------------------------------------------------\n");
  return 0;
}
