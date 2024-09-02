#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// -----------------------------------------------------------
// Tables holding the phred score symbols and their weights
static const char SYMBOLS[] = {'!', '\"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
static double *WEIGHTS;
// -----------------------------------------------------------
// void bernoulliWeights(static double **weights) {
// }
// -----------------------------------------------------------

typedef enum {
  TRUE,
  FALSE
} bool;

// -----------------------------------------------------------
// -----------------------------------------------------------

const char getQscore() {
  bool B = FALSE;
  int candidate;
  while(B != TRUE) {
    unsigned int r = rand();
    candidate = r % 41;
    double prob = (double)r / RAND_MAX;
    // printf( "\n\tcandidate = %c (probability = %lf)\n", SYMBOLS[candidate], prob );
    if(prob < WEIGHTS[candidate]) {
      B = TRUE;    
    }
  }
  return SYMBOLS[candidate];
}

// -----------------------------------------------------------

char * getQsequence(int length) {
  unsigned int n = 0;
  char * Qseq = malloc((length + 1) * sizeof(char));
  while(n < length) {
    Qseq[n] = getQscore();
    // printf("%c", Qseq[n]);
    n++;
  }
  Qseq[n] = '\0';
  return Qseq;
}

void inverse(bool * B) {  
  if((*B) == TRUE) {
    (*B) = FALSE;
  } else {
    (*B) = TRUE;
  }
}

void reset(bool * B) {  
    (*B) = FALSE;
}
// -----------------------------------------------------------
void bernoulliWeights(double **weights) {
  double *w = (*weights);
  // printf("\n\t: %f\n", w[3]);

  for(unsigned int i=0; i<41; i++) {
    unsigned int r = rand();
    unsigned int sign = r % 2;
    double prob = (double)r / RAND_MAX;
    if(sign) {
      w[i] = 1.0 + prob;
    } else {
      w[i] = 1.0 - prob;
    }
    printf("\n\t: %f", w[i]);
  }
  
}
// -----------------------------------------------------------
// ###########################################################################

int main(int argc, char **argv)
{
  srand(time(NULL));   // Initialization, should only be called once.
  // FILE * input;
  // FILE * out;
  // char ch;
  // bool add = FALSE;
  // bool measure = FALSE;
  // bool new_line = FALSE;
  // bool *a = &add;
  // bool *m = &measure;
  // bool *ne = &new_line;
  // unsigned int SEQUENCE_LENGTH = 0;
  // unsigned int count = 0;
  // double w = 1.0/41;
  WEIGHTS = calloc(41,sizeof(double));
  // printf("\n\t: %f\n", WEIGHTS[3]);
  double **weights = &WEIGHTS;
  // --------------------------------------
  // for(int i=0; i<41; i++) {
  //   WEIGHTS[i]=w;
  // }
  // --------------------------------------

  bernoulliWeights(weights);
    
  // fprintf(stdout,"-----------------------------------------------------\n");
  // input = fopen(argv[1], "r");
  // fprintf(stdout, "\n\tprocessing file %s\n", argv[1]);
  // fflush(stdout);
  // out = fopen(argv[2], "w");
  // // --------------------------------------

  // while((ch = fgetc(input)) != EOF) {
  //   // ch = fgetc(input);    
  //   // Always print the original character to the out file
  //   if(ch != '\f' && ch != '\r') { 
  //     fprintf(out, "%c", ch) ;
  //   } else {
  //     fprintf(stdout,"\n form feed detected!\n");
  //     fflush(stdout);
  //   }
  //   if(ch == '\n' || ch == '\r') {
  //     if(measure == TRUE && new_line == TRUE) {
  // 	reset(m);	
  //     }
  //     inverse(ne);
  //     count++;
  //   }
  //   if(measure == TRUE && new_line == TRUE) {
  //     SEQUENCE_LENGTH++;
  //   }
  //   // If the last line ended and the previous line had
  //   //  the + character we had the Qscore sequence below
  //   if(add == TRUE && new_line == TRUE) {
  //     SEQUENCE_LENGTH--;      
  //     fprintf(out, "%s\n", getQsequence(SEQUENCE_LENGTH));
  //     reset(a);
  //     reset(ne);
  //     SEQUENCE_LENGTH = 0;
  //   }
    
  //   if(ch == '+') {
  //     // Add the Qscore sequence on the next line
  //     inverse(a);
  //   }
  //   if(ch == '@') {
  //     // Measure the sequence's length on the next line
  //     inverse(m);
  //   }
  // }
  // fflush(out);
  
  // fclose(input);
  // fclose(out);
  // fprintf(stdout,"\t%d sequences processed\n", count/4);
  
  // --------------------------------------
  fprintf(stdout,"-----------------------------------------------------\n");
  return 0;
}
