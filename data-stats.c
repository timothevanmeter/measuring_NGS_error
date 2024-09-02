#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ###########################################################################

int main(int argc, char **argv)
{
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  char *end;

  int N = 0;
  double sum = 0;
  double sumsq = 0;
  double mean = 0;
  double var = 0;
  // --------------------------------------

  // fprintf(stdout,"-----------------------------------------------------\n");
  stream = fopen(argv[1], "r");
  // fprintf(stdout, "\n\tProcessing file %s\n", argv[1]);
  // fflush(stdout);
  // --------------------------------------

  while ((nread = getline(&line, &len, stream)) != -1) {
    line[nread - 1] = '\0';
    // fprintf(stdout,"%s\n",line);
    double temp = strtof(line, &end);
    sum += temp;
    sumsq += pow(temp, 2.0);
    // fprintf(stdout,"%s %f %f\n",line,sum,sumsq);
    N++;
  }    
  free(line);
  fclose(stream);
  // --------------------------------------

  mean = sum / N;
  var = (sumsq - N * pow(mean, 2.0)) / (N - 1);
  fprintf(stdout,"%f %f",mean,var);
  fflush(stdout);
  // --------------------------------------  
  
  // fprintf(stdout,"-----------------------------------------------------\n");
  return 0;
}
