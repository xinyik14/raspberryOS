/*

    Part of the Raspberry-Pi Bare Metal Tutorials
    Copyright (c) 2013, Brian Sidebotham
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
        this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.

*/

/* For more information about this file, please visit:
   https://sourceware.org/newlib/libc.html#Stubs

   These are the newlib C-Library stubs for the valvers Raspberry-Pi bare-metal
   tutorial */

/*
    Graceful failure is permitted by returning an error code. A minor
    complication arises here: the C library must be compatible with development
    environments that supply fully functional versions of these subroutines.
    Such environments usually return error codes in a global errno. However,
    the Red Hat newlib C library provides a macro definition for errno in the
    header file errno.h, as part of its support for reentrant routines (see
    Reentrancy).

    The bridge between these two interpretations of errno is straightforward:
    the C library routines with OS interface calls capture the errno values
    returned globally, and record them in the appropriate field of the
    reentrancy structure (so that you can query them using the errno macro from
    errno.h).

    This mechanism becomes visible when you write stub routines for OS
    interfaces. You must include errno.h, then disable the macro, like this:
*/

#include <sys/stat.h>
/* Prototype for the UART write function */
#include "rpi-aux.h"

/* Increase program data space. As malloc and related functions depend on this,
   it is useful to have a working implementation. The following suffices for a
   standalone system; it exploits the symbol _end automatically defined by the
   GNU linker. */
caddr_t _sbrk( int incr )
{
    extern char _end;
    static char* heap_end = 0;
    char* prev_heap_end;

    if( heap_end == 0 )
        heap_end = &_end;

     prev_heap_end = heap_end;

     heap_end += incr;
     return (caddr_t)prev_heap_end;
}

void outbyte( char b )
{
    RPI_AuxMiniUartWrite(b);
}

int _write( int file, char *ptr, int len )
{
    int todo;

    for( todo = 0; todo < len; todo++ )
      outbyte(*ptr++);

    return len;
}



/* There's currently no implementation of a file system because there's no
   file system! */
int _close( int file )
{
    return -1;
}

/* Status of an open file. For consistency with other minimal implementations
   in these examples, all files are regarded as character special devices. The
   sys/stat.h header file required is distributed in the include subdirectory
   for this C library. */
int _fstat( int file, struct stat *st )
{
    st->st_mode = S_IFCHR;
    return 0;
}

/* Query whether output stream is a terminal. For consistency with the other
   minimal implementations, which only support output to stdout, this minimal
   implementation is suggested: */
int _isatty(int file)
{
    return 1;
}

/* Establish a new name for an existing file. Minimal implementation: */
//int link( char *old, char *new )
//{
//    errno = EMLINK;
//    return -1;
//}

/* Set position in a file. Minimal implementation: */
int _lseek(int file, int ptr, int dir)
{
    return 0;
}


/* Open a file. Minimal implementation: */
int open( const char *name, int flags, int mode )
{
    return -1;
}


/* Read from a file. Minimal implementation: */
int _read( int file, char *ptr, int len )
{
    return 0;
}
/* Status of a file (by name). Minimal implementation: */
int stat( const char *file, struct stat *st )
{
    st->st_mode = S_IFCHR;
    return 0;
}

/* Remove a file's directory entry. Minimal implementation: */
//int unlink( char *name )
//{
//    errno = ENOENT;
//    return -1;
//}


