/* ========================================
 *
 * adc.c
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
#include "adc.h"
#include "mathUtility.h"
#include "hardwareParameters.h"

extern _Bool sampleADC;

void initADC()
{
    //Initalizes ADCs
    ADC1_Start();
    ADC1_StartConvert();
    int offSet = getADCReading();
    ADC1_SetOffset(offSet);
}

int16 getADCReading()
{   
    int sum = 0;
    int i = 0;
    while(i<ADC_SAMPLES)
    {
        if(sampleADC)
        {
            sum+=ADC1_GetResult16();
            i++;
            sampleADC=0;
        }
    }
    sum/=ADC_SAMPLES;
    return sum;
}

double getCurrent()
{   
    //Order to be confirmed
    return ADC1_CountsTo_Volts(getADCReading())*ADC_V_TO_I;
}

double getTorque()
{
    return getCurrent()*MOTOR_K_T;
}


/* [] END OF FILE */
