#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "get_error.h"
#include "getlines.h"

// USAGE:
// COMPILATION: 
// gcc -Wall -pedantic -o er.o get_error.c getlines.c -lm 
// EXECUTION: 
// ./er.o <fastq_file> <output_file_name> <number_of_lines_in_fastq_file> 

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

typedef struct error {
  float val;
  error *next;
}error;

error * init_error( float val ) {
  error *e = malloc( sizeof( error ));
  e->val = val;
  e->next = NULL;
  return e;
}

void free_error( error *trash ) {
  if( trash != NULL ) {    
    free( trash );
    trash = NULL;
  }
}

void print_error( error *e ) {
  if( e != NULL ) {
    printf( " %f\n", e->val );
  }
}

// -----------------------------------------------------------
// -----------------------------------------------------------

typedef struct list_error {
  error *head;
  error *tail;
}list_error;

error * get_head( list_error *lc ) {
  return lc->head;
}

list_error * init_list_errors() {
  list_error *lc;
  lc = malloc( sizeof( list_error ));
  lc->head = NULL;
  lc->tail = NULL;
  return lc;
}

void free_list( list_error *lc ) {
  free( lc );
  lc = NULL;
}

void free_list_content( error *head ) {
  while( head != NULL ){
    error *temp = head;
    head = head->next;    
    free_error( temp );
  }
}


// USED IN THE TRANSPOSE_HASH FUNCTION 
// No need to compare the sequences here, which are already 
//   collapsed in the hash table. 
//   To be more efficient the head of the list is not past, but 
//   the last added unit instead.  
void set_error( list_error **lc, float val ) {
  if( !(*lc)->head ) {
    (*lc)->head= init_error( val );
    (*lc)->tail = (*lc)->head;
  } else {
    error *temp = (*lc)->tail;
    error *new = init_error( val );
    // temp = (*lc)->head; 
    while( temp->next != NULL ) {
      temp = temp->next;
    }
    temp->next = new;
    (*lc)->tail = temp->next;
  }
}


void set_head( list_error **lc, error *new_head ) {
  (*lc)->head = new_head;
}

void add_error( list_error **lc, float val ) {
  if( !(*lc)->head ) {
    (*lc)->head= init_error( 1 );    
  } else {
    error *temp = (*lc)->head;
    error *new = init_error( val );
    int add = 0;
    temp = (*lc)->head;
    while( temp->next != NULL ) {
      temp = temp->next;
    }
    if( add == 0 ){
      temp->next = new;
    }
  }
}

void print_list( list_error **lc ) {
  error *temp = (*lc)->head;
  while( temp != NULL ) {
    print_error( temp );
    temp=temp->next;
  }
}

void print_dat( list_error **lc, FILE *output ) {
  error *temp = (*lc)->head;
  while( temp != NULL ) {
    fprintf( output, "%f\n", temp->val );
    temp=temp->next;
  }
}

void count_intervals( list_error **lc, float max, float step, FILE *output) {
  int counts = 0;
  int total = 0;
  error *temp = (*lc)->head;  
  while( temp != NULL ) {
    if( temp->val > (max - step) ){
      counts++;
      total++;
    } else {
      fprintf( output, "%.2f %.2f %d\n", max, (max-step), counts );
      max = max - step;
      counts = 1;
      total++;
    }    
    temp=temp->next;
    printProgress(total/(double)fileSize);
  }
  fprintf( output, "%.2f %.2f %d\n", max, (max-step), counts );
  printf( "\n\n\tTOTAL COUNTS = %d", total );
}

// -----------------------------------------------------------
// -----------------------------------------------------------

int cmp( error *a, error *b) {
  if (a->val < b->val)
    return -1;
  if (a->val > b->val)
    return +1;
  return 0;
}

error * list_sort( list_error *lc ) {
  // list_error *list = *lc; 
  error *list_head = lc->head;
  error *p, *q, *e, *tail; //, *oldhead;
  int insize, nmerges, psize, qsize, i;

  // Silly special case: if `list' was passed in as NULL, return
  // NULL immediately.
   
  if( !list_head )
    return NULL;

  insize = 1;

  while( 1 ) {
    p = list_head;
    list_head = NULL;
    tail = NULL;

    nmerges = 0;  // error number of merges we do in this pass 

    while( p ) {
      nmerges++;  // there exists a merge to be done 
      // step `insize' places along from p 
      q = p;
      psize = 0;
      for( i = 0; i < insize; i++ ) {
	psize++;
	q = q->next;
	if( !q ) break;
      }

      // if q hasn't fallen off end, we have two list_heads to merge 
      qsize = insize;

      // now we have two list_heads; merge them 
      while( psize > 0 || (qsize > 0 && q) ) {

	// decide whether next element of merge comes from p or q 
	if( psize == 0 ) {
	  // p is empty; e must come from q. 
	  e = q; q = q->next; qsize--;
	} else if (qsize == 0 || !q) {
	  // q is empty; e must come from p. 
	  e = p; p = p->next; psize--;
	} else if (cmp(p,q) <= 0) {
	  // First element of p is lower (or same);
	  // e must come from p. 
	  e = q; q = q->next; qsize--;
	} else {
	  // First element of q is lower; e must come from q. 
	  e = p; p = p->next; psize--;
	}

	// add the next element to the merged list_head 
	if (tail) {
	  tail->next = e;
	} else {
	  list_head = e;
	}
	tail = e;
      }

      // now p has stepped `insize' places along, and q has too 
      p = q;
    }
    tail->next = NULL;

    // If we have done only one merge, we're finished. 
    if (nmerges <= 1)   // allow for nmerges==0, the empty list_head case 
      return list_head;

    // Otherwise repeat, merging list_heads twice the size 
    insize *= 2;
  }
}

// ###########################################################################
// ###########################################################################
// ###########################################################################
// ###########################################################################

int main(int argc, char **argv)
{
  FILE *fp;
  FILE *output;
  char line[256];
  float num;
  fileSize = getlines(argv[1]);
  
  fprintf( stdout, "-----------------------------------------------------\n\n");

  fprintf( stdout, "\tProgram called with: %s\n", argv[1] );
	
  fp = fopen(argv[1], "r");

  // INITIALISING A LINKED LIST ; THE ASSOCIATED 
  // STRUCTURE IS DEFINED IN LIST_ERRORS.C 
  list_error *le = init_list_errors();
  list_error **lst_err = &le;

  double i = 0.0;
  fprintf( stdout, "\n-----------------------------------------------------\n");
  fprintf( stdout, "\tLoading in the file:\n" );

  while (fgets(line, sizeof(line), fp)) {
    // if( i == 2000 ) {
    //   break;
    // }
    printProgress(i/(double)fileSize);
    // Convert the line to a float
    num = strtof(line, NULL);
    set_error(lst_err, num);
    // printf( "%.4f\n", num );
    i++;
  }
  fclose(fp);

  fprintf( stdout, "\n\n\tSorting the errors array:\n" );
  // SORTING THE LINKED LIST CONTAINING THE 
  // SEQUENCES AND THE ASSOCIATED ERRORS. 
  set_head( lst_err, list_sort( le ) );
  
  // fprintf( stdout, "\n-----------------------------------------------------\n");
  // print_list( lst_err );
  
  // fprintf( stdout, "\n-----------------------------------------------------\n");

  output = fopen(argv[2], "w+");
  fprintf( stdout, "\n\tPrinting results to dat file\n");
  print_dat( lst_err, output );

  // Writing the counts within intervals to file
  // fprintf( stdout, "\n\tCounting the number of occurences in each interval:\n" );
  // count_intervals( lst_err, 33.0, 0.1, output );

  fclose(output);
  
  // FREEING ALL THE MEMORY 
  // FOR THE LINKED LIST: 
  free_list_content( get_head( le ));
  free_list( le );
  printf("\n-----------------------------------------------------\n");
  return 0;
}
