#ifndef INC_001_CIRCULARBUFFER_CIRCULARBUFFER_H
#define INC_001_CIRCULARBUFFER_CIRCULARBUFFER_H

/*******************************************************************
 * ANSI C Libraries
 *******************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************
 * Typedef enumeration
 *******************************************************************/
typedef enum
{
    BUFFER_CREATED = 0,
    BUFFER_DELETED,
    BUFFER_EMPTY,
    BUFFER_FULL,
    BUFFER_NOT_FULL,
    BUFFER_ERROR
}CircBuffer_err_t;

/*******************************************************************
 * Typedef structures
 *******************************************************************/
/** **/
typedef struct
{
    uint8_t     *pData;
    uint32_t    DataSize;
    uint32_t    head;
    uint32_t    tail;
    bool        Init;
}CircularBuffer_t;

/*******************************************************************
 * ANSI C Libraries
 *******************************************************************/

/** Circular buffer Create/Delete functions **/
CircBuffer_err_t CircBuffer_Create( CircularBuffer_t *Buff, uint8_t *pData, uint32_t DataSize );
CircBuffer_err_t CircBuffer_Delete(CircularBuffer_t *Buff);

/** Circular buffer Write/Read functions **/
void CircBuffer_WriteData(CircularBuffer_t *Buff, uint8_t Data);
void CircBuffer_ReadData(CircularBuffer_t *Buff, uint8_t *pData);

/** Circular buffer byte operations **/
int CircBuffer_DelByte( CircularBuffer_t *Buff );
int CircBuffer_WriteByte( CircularBuffer_t *Buff, uint8_t Data );
uint8_t CircBuffer_ReadByte( CircularBuffer_t *Buff );

/** Circular buffer flush/reset functions **/
int CircBuffer_Flush( CircularBuffer_t *Buff );
void CircBuffer_Reset( CircularBuffer_t *Buff );

#endif //INC_001_CIRCULARBUFFER_CIRCULARBUFFER_H
