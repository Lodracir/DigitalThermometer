#ifndef PROGRAM_VALUE_H
#define PROGRAM_VALUE_H

/** ANSI C Headers **/
#include <stdio.h>
#include <stdint.h>

/** **/
typedef struct
{
    float value;
    float aver;
    float max;
    float min;
}Value_t;

#endif //PROGRAM_VALUE_H
