/** Statistics Include **/
#include "APP/statistics.h"

float MEAN_FLOAT(float *Buff, uint8_t BufferSize)
{
    /** Local Variables **/
    float *ptr = NULL;
    float result = 0;

    /** Allocate buffer to pointer **/
    ptr = Buff;

    /**  **/
    for(int itr = 0; itr < BufferSize; itr++)
    {
        result += (*ptr);
        ptr++;
    }

    /** Deallocate pointer **/
    ptr = NULL;

    /** Calculate Mean and return value **/
    return result = result/BufferSize;

}

/** MAX Value **/
float MAX_FLOAT(float *Buff, uint8_t BufferSize)
{

    /** Local Variables **/
    float *ptr = NULL;
    float result = 0;

    /** Allocate buffer to pointer **/
    ptr = Buff;

    /** Find MAX Value **/
    for(int itr = 0; itr < BufferSize; itr++)
    {
        if( (*ptr) > result )
        {
            result = (*ptr);
        }

        ptr++;

    }

    /** Deallocate pointer **/
    ptr = NULL;

    /** Return Max Value **/
    return result;

}

/** MIN Value **/
float MIN_FLOAT(float *Buff, uint8_t BufferSize)
{

    /** Local Variables **/
    float *ptr = NULL;
    float result = 0;

    /** Allocate buffer to pointer, and assign first value **/
    ptr = Buff;
    result = (*ptr);

    /** Find MAX Value **/
    for(int itr = 0; itr < BufferSize; itr++)
    {
        if( (*ptr) < result )
        {
            result = (*ptr);
        }

        ptr++;

    }

    /** Deallocate pointer **/
    ptr = NULL;

    /** Return Max Value **/
    return result;
}

