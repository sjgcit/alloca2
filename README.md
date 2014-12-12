# alloca2()

### A safe replacement for C's alloca()

---

### What is it and how can I use *alloca2* ?

Using alloca2 is easy.  There is a an example provided.  It's a single header file and requires only two "calls".  First to initialize alloca2 and second to get memory.  That's all.

### Why should I use alloca2() anyway ?

The much maligned *alloca()* function is a very handy memory allocation tool in C.  Unlike malloc it allocates from the local stack frame ( in most implementations ) and it is very fast.  Using it to allocate fixed amounts of memory was zero cost as most compilers will simply make that happen when the function's scope is initialized.  Using it for variable amounts of memory was slower, but still way faster than malloc as it simply involved adjusting the stack pointer.  And as an added bonus alloca() memory is zero cost to release as it simply get's returned when the function returns as part of returning the stack frame.

But alloca() had a **huge** drawback : unlike malloc() it does not return NULL when it runs out of memory.  That makes it painful for most developers and potentially a security risk.  In addition you cannot release the memory you used and no longer need.

**Alloca2()** addresses the main problem and *does* return NULL when it runs out of space.  In addition there is a limited capability to release memory back to alloca2().

### Details, details ...

A simple example :

```C
    int myfunction( char *str )
    {
        alloca2_init( 10240 ) ;
        
        char *p = NULL ;
        ....
        p = alloc2( strlen(str) ) ;
        
        if( p == NULL )
            return -1 ;
        
        // otherwise do stuff
    }
```

This is easy to follow.  First we set aside some amount of memory for *alloca2* ( which is declared as a char array ).  Then we want to allocate some part of this to make a copy of the string we received.  In this case we only need the copy while the function scope is active, so we can avoid an expensive call to malloc() and simply use alloca2().  Notice that, unlike alloca() ( but like malloc() ) we can check for a null pointer to indicate that alloca2() could not grant us the memory we want.  No danger of blowing up the stack or SIGSEGV'ing as we might with alloca().

When the function scope is left ( it returns to the caller for any reason ), then just like alloca() the memory we allocated with alloca2() should *not* be addressed at all.  If you try and use it you can expect trouble sooner rather than later.  Of course the memory is accessible to any function called by "myfunction()".

#### Alignment

All memory allocated by *alloca2()* is 16 byte aligned.

#### Releasing memory back

*Alloca2()* does **not** track memory allocations, so all you can do is tell it to reclaim part of the top of the used memeory space.  Be careful when doing this as you may accidentally release space that you still want to use.



