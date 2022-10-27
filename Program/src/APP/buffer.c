/****
 * @file   buffer.c
 * @author Ricardo Escarcega (you@domain.com)
 * @brief  
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 ****/

/**
 * Required files
 **/
#include "APP\buffer.h"

void CreateBuffer( void *pvBuffer , uint8_t buffSize )
{
    pvBuffer = malloc( buffSize );
}

void BufferAddElement( void *pvBuffer , uint8_t buffPosition, void *pvData );