
/*
 * Include file alloca2.h
 *
 * $Id: alloca2.h,v 1.11 2014/12/12 09:38:34 sjg Exp $
 *
 * (c) Stephen Geary, Dec 2014
 *
 * A safer replacement for alloca() which returns NULL
 * when it cannot fulfil a request for memory.
 *
 * Source file needs to be compiled with gccwrap or processed
 * with cap.
 *
 * cap     - https://github.com/sjgcit/cap
 * gccwrap - https://github.com/sjgcit/gccwrap
 * 
 */


#ifndef __ALLOCA2_H

#  define __ALLOCA2_H



#include <stdlib.h>



#define ALLOCA2_ALIGNMENT   16


#define ALLOCA2_MASK        ( ALLOCA2_ALIGNMENT - 1 )


#define alloca2_adjsize( sz )       ( ( (sz) + ALLOCA2_MASK ) & ~ALLOCA2_MASK )



/* Note that sz should be known at compile time !
 *
 * For example a constant
 */

struct alloca2_s {
        char *top ;
        char *next ;
        } ;

typedef struct alloca2_s alloca2_t ;

#define alloca2_top    (((alloca2_t *)alloca2_base)->top)

#define alloca2_next   (((alloca2_t *)alloca2_base)->next)



#define alloca2_init( sz ) \
    char  alloca2_base[ (sz) ] ; \
     \
    alloca2_next = alloca2_base + alloca2_adjsize( sizeof(alloca2_t) ) ; \
    alloca2_top  = alloca2_base + (sz) ;

 


#define alloca2_get( sz ) \
            ( alloca2_next+alloca2_adjsize((sz)) > alloca2_top \
                ? NULL \
                : ( alloca2_next += alloca2_adjsize((sz)) ) - alloca2_adjsize((sz)) \
            )

 

#define alloca2(sz)     alloca2_get((sz))



#define alloca2_release( sz ) \
    { \
        alloca2_next -= ALLOCA2_ALIGNMENT * ( ((sz)) / ALLOCA2_ALIGNMENT ) ; \
    }

 
#endif /* __ALLOCA2_H */




