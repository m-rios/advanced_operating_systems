#include <stdio.h>
#include <stdlib.h>

#include "dynamic_mem.h"

int k;

void dynamic_mem(void)
{
    
int * p;
// "p is a pointer to integer ", or more literally :
// "* p is an integer " ( declaration resembles use )
char * q , * r , * s;
// More ( and yes : we need to repeat the *)
printf ("\n\ tFunction dynamic_mem (): %p\n" , & dynamic_mem );
printf
printf
printf
printf
printf
("\n\ tLocal variables ( addr ., name , value ):\ n" );
("\t\t%p p %p\n" , &p , p );
("\t\t%p q %p\n" , &q , q );
("\t\t%p r %p\n" , &r , r );
("\t\t%p s %p\n" , &s , s );
// Ask for dynamic memory ( malloc ==" allocate memory "):
p = ( int *) malloc (7 * sizeof ( int ));
q
r
s
//
//
//
//



( char *) malloc (5 * sizeof ( char ));
( char *) malloc ( sizeof ( char ));

( int *) and ( char *) are type conversions , needed
cause malloc reserves bytes in bulk , and returns a
generic pointer ( void *) , so we convert it to the
right type before making the assignment
if (p == NULL || q == NULL || r == NULL || s == NULL )
{
if (p != NULL ) free (p );
// If any reservation failed ,
if (q != NULL ) free (q );
// undo the others , and
if (r != NULL ) free (r );
// get out of this function
if (s != NULL ) free (s );
return ;
}
