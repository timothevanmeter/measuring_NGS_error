
typedef struct error error;

error * init_error( float val );

void free_error( error *trash );

void print_error( error *e );

// -----------------------------------------------------------
// -----------------------------------------------------------

typedef struct list_error list_error;

error * get_head( list_error *lc );

list_error * init_list_errors();
  
void free_list( list_error *lc );
  
void free_list_content( error *head );
  
void set_error( list_error **lc, float val );


void set_head( list_error **lc, error *new_head );

void add_error( list_error **lc, float val );

void print_list( list_error **lc );

void print_dat( list_error **lc, FILE *output );

// -----------------------------------------------------------
// -----------------------------------------------------------

int cmp( error *a, error *b);

error * list_sort( list_error *lc );
