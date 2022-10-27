#ifndef _BUFFER_H_
#define _BUFFER_H_

/* ANSI C Libraries */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/**
 * Prototype Functions
 **/

void CreateBuffer( void *pvBuffer , uint8_t buffSize );
void BufferAddElement( void *pvBuffer , uint8_t buffPosition, void *pvData );

#endif // _BUFFER_H_