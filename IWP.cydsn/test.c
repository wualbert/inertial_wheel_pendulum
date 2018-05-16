/* ========================================
 *
 * test.c
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

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "hardware.h"
#include "hardwareParameters.h"
#include "controllers.h"
#include "mathUtility.h"
#include "sensorStructs.h"

extern MemoryVariable thetaShoulder;
extern MemoryVariable thetaWheel;
extern MemoryVariable torque; 

void initTests()
{
    srand(time(NULL));   
}
void testDec()
{
    LCD_ClearDisplay();
    LCD_PrintString("Mtr Dec: ");
    printdouble(getMotorDecReading(),3);
    LCD_Position(1, 0);  //line feed
    LCD_PrintString("Shdr Dec: ");
    printdouble(getShoulderDecReading(),3);    
}
void testThetaWheel()
{
    LCD_ClearDisplay();
    LCD_PrintString("ThetaW: ");
    printdouble(getValue(&thetaWheel),3);
    LCD_Position(1, 0);  //line feed
    LCD_PrintString("OmegaW: ");
    printdouble(getDerivative(&thetaWheel),3);       
}
void testThetaShoulder()
{
    LCD_ClearDisplay();
    LCD_PrintString("ThetaS: ");
    printdouble(getValue(&thetaShoulder),3);
    LCD_Position(1, 0);  //line feed
    LCD_PrintString("OmegaS: ");
    printdouble(getDerivative(&thetaShoulder),3);       
}
void testADC()
{
    LCD_ClearDisplay();
    LCD_PrintString("ADC ");
    LCD_PrintString(": ");
    LCD_PrintNumber(getADCReading());
}
void testComm()
{
    LCD_ClearDisplay();
    LCD_PrintString("Sending ");
    int randNum = rand()%256;
    LCD_PrintNumber(randNum);
    LCD_Position(1, 0);  //line feed
    LCD_PrintString("Dir ");
    int randDir = rand()%2;
    LCD_PrintNumber(randDir);
    sendValue(randNum,randDir);
}
void testPrintdouble()
{
    LCD_ClearDisplay();
    printdouble(1.2346,3);
    LCD_Position(1, 0);  //line feed
    printdouble(-1.2344,3);
}
void testISensing()
{
    LCD_ClearDisplay();
    sendValue(70,1);
    LCD_PrintString("I:");
    printdouble(getCurrent()*1e3,0);
    LCD_Position(1, 0);  //line feed
    printdouble(getADCReading(1),0);
    LCD_PrintString(",");
    printdouble(getADCReading(2),0);
}
void testTorqueController()
{    
    //double goalTorque = fmod(rand(),1.8*MAX_TORQUE);
    //goalTorque-=0.9*MAX_TORQUE;
    //setTorque(randTorque,0);
    double goalTorque = 0.02;
    int i=0;
    while(1)
    {
        setTorque(goalTorque,1,1);
        i++;
        if(i==1)
        {
            LCD_ClearDisplay();
            LCD_PrintString("Meas Tau:");
            printdouble(getValue(&torque)*1e3,3);
            LCD_Position(1, 0);  //line feed
            LCD_PrintString("OmegaWheel:");
            printdouble(getDerivative(&thetaWheel),3);
            i=0;
        }
    }
}
/* [] END OF FILE */
