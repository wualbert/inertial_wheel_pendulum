/* ========================================
 *
 * mathUtility.c
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
#include "mathUtility.h"
#include <math.h>

double max(double a, double b)
{
    return a>b?a:b;
}
double min(double a, double b)
{
    return a<b?a:b;
}
/*
char* decToHex(int value)
{
    value = min(max(value,0),255);  //cap in range
    static char hex[2];
    sprintf(hex, "%02x", value);
    return hex;
}
*/
/*
double wrapAngle(double angle)
{
    //Not working...
    int mul = floor(angle/(2.*CY_M_PI));
    angle-=2.*CY_M_PI*mul;                  //converts to 0~2*PI
    return angle>CY_M_PI?angle-2.*CY_M_PI:angle;
}
*/
double wrapAngle(double x){
    x = fmod(x + CY_M_PI,2*CY_M_PI);
    if (x < 0)
        x += 2*CY_M_PI;
    return x - CY_M_PI;
}

//Prints double on LCD
void printdouble(double value, int decimalPlaces)
{
    //Known bug: does not print leading before first nonzero decimal digit
    if (value>=0)
    {
        int integer = floor(value);
        int decimal = round((value-integer)*pow(10,decimalPlaces));
        LCD_PrintNumber(integer);
        LCD_PrintString(".");
        LCD_PrintNumber(decimal);
    }
    else
    {
        value = -value;
        int integer = floor(value);
        int decimal = round((value-integer)*pow(10,decimalPlaces));
        LCD_PrintString("-");
        LCD_PrintNumber(integer);
        LCD_PrintString(".");
        LCD_PrintNumber(decimal);
    }
    
}
/* [] END OF FILE */
