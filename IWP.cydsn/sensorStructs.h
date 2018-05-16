/* ========================================
 *
 * sensorStructs.h
 *
 * Copyright Albert Wu, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF ALBERT WU.
 *
 * ========================================
*/
#ifndef SENSOR_STRUCTS_H
#define SENSOR_STRUCTS_H

#include <device.h>
#include <project.h>
#include "hardware.h"
    
    
#define MEMORY_SIZE 4
#define MIN_SAMPLE_PERIOD 400               //in us
#define COUNTER_FREQUENCY 100000
#define INIT_SAMPLES 15         
#define INIT_SAMPLE_PERIOD 1
typedef struct MemoryVariable{
    double values[MEMORY_SIZE];          //values[n]=value at t-n
    double timeStamps[MEMORY_SIZE];          //seconds
    double offset;
    double (*valueGetter)();                  //getter function
}MemoryVariable;

void initToZero(MemoryVariable *x);
double getValue(MemoryVariable *x);
double getValueWithoutUpdate(MemoryVariable*x);
double getDerivative(MemoryVariable *x);
double getDerivativeWithoutUpdate(MemoryVariable *x);
double getTime(MemoryVariable *x);

#endif

/* [] END OF FILE */
