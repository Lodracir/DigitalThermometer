#ifndef P001_MEDICIONTEMPERATURA_STATISTICS_H
#define P001_MEDICIONTEMPERATURA_STATISTICS_H

/** ANSI C Includes **/
#include <stdio.h>
#include <stdint.h>

/**
 * Prototype Functions
 **/

/** Averages **/
float MEAN_FLOAT(float *Buffer, uint8_t BufferSize);

/** MAX Value **/
float MAX_FLOAT(float *Buff, uint8_t BufferSize);

/** MIN Value **/
float MIN_FLOAT(float *Buff, uint8_t BufferSize);

#endif //P001_MEDICIONTEMPERATURA_STATISTICS_H
