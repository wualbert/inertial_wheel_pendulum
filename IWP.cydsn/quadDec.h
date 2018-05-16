/* ========================================
 *
 * quadDec.h
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

#ifndef QUAD_DEC_H
#define QUAD_DEC_H
#include<project.h>
#include <device.h>


//Decoder functions
void initQuadDec();
int16 getMotorDecReading();
int16 getShoulderDecReading();
double getMotorAngleReading();
double getShoulderAngleReading();

#endif

/* [] END OF FILE */
