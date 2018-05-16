/* ========================================
 * 
 * ADC.H
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

#ifndef ADC_H
#define ADC_H
#include<project.h>
#include <device.h>

//ADC functions
void initADC();
int16 getADCReading();
double getCurrent();    
double getTorque();
#endif
/* [] END OF FILE */
