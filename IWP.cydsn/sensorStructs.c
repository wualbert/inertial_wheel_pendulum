/* ========================================
 *
 * sensorStructs.c
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
#include <project.h>
#include <device.h>
#include "mathUtility.h"
#include "sensorStructs.h"

//helper functions
double getavg(MemoryVariable *x);
double getder(MemoryVariable *x);
void updateMemoryVariable(MemoryVariable *x);

void initToZero(MemoryVariable *x)
{
    //samples initial values
    double readings = 0;
    for(int i = 0; i < INIT_SAMPLES; i++)
    {
        readings += x->valueGetter();
        CyDelay(INIT_SAMPLE_PERIOD);
    }
    x->offset=readings/INIT_SAMPLES;
    updateMemoryVariable(x);
}

double getValue(MemoryVariable *x)
{
    updateMemoryVariable(x);
    return getavg(x);
}

double getValueWithoutUpdate(MemoryVariable*x)
{
    return getavg(x);
}

double getDerivative(MemoryVariable *x)
{
    updateMemoryVariable(x);
    return getder(x);
}
double getDerivativeWithoutUpdate(MemoryVariable *x)
{
    return getder(x);
}

double getTime(MemoryVariable *x)
{
    double sum = 0;
    for(int i = 0; i < MEMORY_SIZE; i++)
    {
        sum+=x->timeStamps[i];
    }
    return sum/MEMORY_SIZE/COUNTER_FREQUENCY;
}
//Helpers implementation
void updateMemoryVariable(MemoryVariable *x)
{
    for(int i = 0; i < MEMORY_SIZE; i++)
    {
        x->values[i] = x->valueGetter()-x->offset;
        x->timeStamps[i] = (Counter_1_ReadCounter()*1.);
        CyDelayUs(MIN_SAMPLE_PERIOD);
    }
}

double getavg(MemoryVariable *x)
{
    //helper function. calculates the average
    double sum = 0;
    for(int i = 0; i < MEMORY_SIZE; i++)
    {
        sum+=x->values[i];
    }
    return sum/MEMORY_SIZE;
}
double getder(MemoryVariable *x)
{
    double vAvg = 0;
    int added = 0;
    for(int i = 0; i < MEMORY_SIZE-1; i++)
    {
        double deltaT = x->timeStamps[i+1]-x->timeStamps[i];
        double deltaX = x->values[i+1]-x->values[i];
        if (deltaT>0 && fabs(deltaX)<500)  //To deal with counter wraparounds
        {
            vAvg+=(x->values[i+1]-x->values[i])/(x->timeStamps[i+1]-x->timeStamps[i])*COUNTER_FREQUENCY;
            added++;
        }
    }
    vAvg/=(added);
//    double vAvg = 0;
//    vAvg=(x->values[MEMORY_SIZE-1]-x->values[0])/(x->timeStamps[MEMORY_SIZE-1]-x->timeStamps[0])*COUNTER_FREQUENCY;
    return vAvg;
}
/* [] END OF FILE */
