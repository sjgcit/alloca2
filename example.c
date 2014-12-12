/*
 * example.c
 *
 * $Id: example.c,v 1.4 2014/12/12 09:39:40 sjg Exp $
 *
 * (c) Stephen Geary. Dec 2014
 *
 * And example file for using alloca2.h
 */

#include <stdio.h>
#include <stdlib.h>

#include "alloca2.h"


#define pv( f, x )  printf( #x " = %" #f "\n", (x) )


int main( int argc, char **argv )
{
    int retv = 0 ;
    
    char *p = NULL ;
    
    alloca2_init(1024) ;
    
    pv(p,alloca2_base) ;
    pv(p,alloca2_top) ;
    
    pv(p,p) ;
    
    /* grab alloca2's memory until we run out
     */
    
    int n = 0 ;
    
    do {
        p = alloca2(100) ;
        
        if( p != NULL )
            n++ ;
        
        pv(p,p) ;
        
        } while( p != NULL ) ;
    
    /* we ran out of (alloca2) memory to get here
     *
     * let's release some back and see what happens
     */
    
    alloca2_release( n * 100 ) ;
    
    do {
        p = alloca2(100) ;
        
        if( p != NULL )
            n++ ;
        
        pv(p,p) ;
        
        } while( p != NULL ) ;
    
    /* You should see that not all the memory could be
     * reused.  This is because of alignment issues as
     * alloca2 always keeps addresses aligned to
     * 16 bytes.
     */
    
    return retv ;
}


