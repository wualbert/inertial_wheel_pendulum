/* ========================================
 *
 * mathUtility.h
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

#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include<project.h>
#include <device.h>
#include <math.h>
double max(double a, double b);
double min(double a, double b);
double wrapAngle(double angle);         //maps angle to (-pi*pi)
void printdouble(double value, int decimalPlaces);
//char* decToHex(int x);          //takes a DEC integer between 0~255, convert to HEX


#endif

/* [] END OF FILE */
