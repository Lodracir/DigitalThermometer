/*******************************************************************
 * Required headers
 *******************************************************************/
#include "Common/CircularBuffer.h"

/*******************************************************************
 * Static Local Variables
 *******************************************************************/
static uint8_t uData = 0;

/*******************************************************************
 * Public Functions
 *******************************************************************/

/************** Circular buffer Create/Delete functions ************/

/***
 * @Name  CircBuffer_Create
 * @Brief Create the circular buffer according with input data
 * @Input 1.- Pointer to Circular buffer structure
 *        2.- Pointer to unsigned 8-bit data
 *        3.- Size of circular buffer
 * @return None (void)
 ***/
CircBuffer_err_t CircBuffer_Create( CircularBuffer_t *Buff, uint8_t *pData, uint32_t DataSize )
{
    if( Buff->pData == NULL && Buff->Init == false )
    {
        Buff->pData = pData;
        Buff->DataSize = DataSize;
        Buff->head = 0;
        Buff->tail = 0;
        Buff->Init = true;
    }
    else
    {
        return BUFFER_ERROR;
    }

    return BUFFER_CREATED;
}

/***
 * @name  CircBuffer_Delete
 * @brief Delete the circular buffer
 * @input Pointer to Circular buffer structure
 * @return None (void)
 ***/
CircBuffer_err_t CircBuffer_Delete(CircularBuffer_t *Buff)
{
    if( Buff->Init == true )
    {
        Buff->pData = NULL;
        Buff->DataSize = 0;
        Buff->head = 0;
        Buff->tail = 0;
        Buff->Init = false;
    }
    else
    {
        return BUFFER_ERROR;
    }

    return BUFFER_DELETED;
}

/**************** Circular buffer Write/Read functions *************/

/***
 * @name  CircBuffer_Delete
 * @brief Delete the circular buffer
 * @input Pointer to Circular buffer structure
 * @return None (void)
 ***/
void CircBuffer_WriteData(CircularBuffer_t *Buff, uint8_t Data)
{
    if( Buff->Init == true && Buff->pData != NULL )
    {
        uint32_t TempPos = (Buff->head + 1) % Buff->DataSize;

        /** If buffer is full, then delete last data and store new one **/
        if (TempPos == Buff->tail)
        {
            CircBuffer_DelByte(Buff);
            CircBuffer_WriteByte(Buff, Data);
        }
        else
        {
            CircBuffer_WriteByte(Buff, Data);
        }
    }
    else
    {
        return;
    }
}

/***
 * @name  CircBuffer_ReadData
 * @brief Delete the circular buffer
 * @input Pointer to Circular buffer structure
 * @return None (void)
 ***/
void CircBuffer_ReadData(CircularBuffer_t *Buff, uint8_t *pData)
{
    /** Local Variables **/
    uint32_t itr;

    for( itr = 0; itr < Buff->DataSize; itr++)
    {
        pData[itr] = CircBuffer_ReadByte(Buff);
        if( Buff->head == Buff->tail )
        {
            break;
        }
    }

    /** When all data was read, flush the buffer **/
    CircBuffer_Flush(Buff);

}

/**************** Circular buffer Write/Read functions *************/

/***
 * @param Buff
 * @param pData
 * @param DataSize
 * @return
 ***/
int CircBuffer_WriteByte( CircularBuffer_t *Buff, uint8_t Data )
{
    if( Buff->Init == true && Buff->pData != NULL )
    {
        uint32_t TempPos = (Buff->head+1)%Buff->DataSize;

        if( TempPos == Buff->tail )
        {
            return -1;
        }
        else
        {
            Buff->pData[Buff->head] = Data;
            Buff->head = TempPos;
        }
    }
    else
    {
        return -1;
    }

    return 0;
}

/***
 * @param Buff
 * @param pData
 * @param DataSize
 * @return
 ***/
uint8_t CircBuffer_ReadByte( CircularBuffer_t *Buff )
{
    if( Buff->Init == true && Buff->pData != NULL )
    {
        /** Assign data from buffer **/
        uData = Buff->pData[Buff->tail];

        /** Due data was read, delete it **/
        CircBuffer_DelByte(Buff);
    }

    return uData;
}

/***
 * @param Buff
 * @param pData
 * @param DataSize
 * @return
 ***/
int CircBuffer_DelByte( CircularBuffer_t *Buff )
{
    if( Buff->head == Buff->tail )
    {
        return -1;
    }
    else
    {
        Buff->tail = (Buff->tail+1)%Buff->DataSize;
    }
    return 0;
}

/***
 * @param Buff
 * @param pData
 * @param DataSize
 * @return
 ***/
int CircBuffer_Flush( CircularBuffer_t *Buff )
{
    /** Clear Buffer **/
    memset(Buff->pData, 0x00, Buff->DataSize);

    /** Reset Head and Tail positions **/
    CircBuffer_Reset(Buff);

    return 0;
}

void CircBuffer_Reset( CircularBuffer_t *Buff )
{
    /** Reset Head and Tail positions **/
    Buff->head = 0;
    Buff->tail = 0;
}