/* ========================================
 *
 * main.c
 *
 * Copyright Albert Wu, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF ALBERT WU.
 *
 * This file is necessary for your project to build.
 * Please do not delete it.
 *
 * ========================================
*/

//#define TEST
//#define TEST_DEC
//#define TEST_THETA_WHEEL
//#define TEST_THETA_SHOULDER
//#define TEST_COMM
//#define TEST_ADC
//#define TEST_PRINT_double
//#define TEST_I_SENSING
//#define TEST_TORQUE_CONTROLLER
//#define TEST_STRUCT
//#define TEST_TORQUE_SENSING
//#define TESE_TORQUE_TRACKING
//#define TEST_RUNNING_AVG
//#define TEST_KT
//#define TEST_TIME
//end


#include <device.h>
#include "sensorStructs.h"
#include "hardware.h"
#include "controllers.h"
#include "controlParameters.h"
#ifdef TEST
    #include "test.h"
#endif

//Initialize global sensor variables
MemoryVariable thetaShoulder;
MemoryVariable thetaWheel;
MemoryVariable torque;
MemoryVariable thetaWheelDot;
MemoryVariable thetaShoulderDot;

double iError =0;

double positiveFreeTorque;
double negativeFreeTorque;
//On-off switch
_Bool enableMotor;
_Bool sampleADC;
/*
int RUNNING_AVG_SAMPLES=500.0;
double adcRunningAvg;
*/
CY_ISR(isr_1_ISR)
{
    enableMotor = !enableMotor; //toggle motor
}
CY_ISR(isr_2_ISR)
{
    sampleADC = 1;
}


void main()
{	
    //Enable interrupts
    CYGlobalIntEnable;
    isr_1_StartEx(isr_1_ISR);    
    isr_2_StartEx(isr_2_ISR);    
    //Initialize LCD
    LCD_Start();					    
    LCD_ClearDisplay();
    LCD_PrintString("Init HW...");
    //Initialize hardware
    Clock_1_Start();
    Clock_2_Start();
    Clock_3_Start();
    Clock_Enc_Motor_Start();
    Clock_Enc_Shoulder_Start();
    Counter_1_Start();
    initADC();
    initQuadDec();
    initUART();
    
    CyDelay(50);
    LCD_ClearDisplay();
    LCD_PrintString("Calibrating");
    LCD_Position(1, 0);  //line feed
    LCD_PrintString("Don't move...");
    //set getter
    thetaShoulder.valueGetter = &getShoulderAngleReading;
    thetaWheel.valueGetter = &getMotorAngleReading;
    torque.valueGetter = &getTorque;
    MemoryVariable freeTorque;
    freeTorque.valueGetter = &getTorque;
    //zero variables
    initToZero(&thetaShoulder);
    initToZero(&thetaWheel);
    initToZero(&torque);
    enableMotor=0;
    //Set positive and negative null current
    sendValue(0,1);
    CyDelay(100);
    initToZero(&freeTorque);
    positiveFreeTorque = freeTorque.offset;
    CyDelay(100);
    sendValue(0,0);
    initToZero(&freeTorque);
    negativeFreeTorque = freeTorque.offset;
    
    
    LCD_ClearDisplay();
    LCD_PrintString("Ready!");
    while(!enableMotor)
    {
    }
    LCD_ClearDisplay();
    LCD_PrintString("Starting...");
    
    #ifdef TEST
        //sensor testing mode
        //initialize sensors
        initTests();
        int pause = 50;
        while(1)
        {
            #ifdef TEST_DEC
            testDec();
            CyDelay(pause);
            #endif
            #ifdef TEST_THETA_WHEEL
            testThetaWheel();
            CyDelay(pause);
            #endif
            #ifdef TEST_THETA_SHOULDER
            testThetaShoulder();
            CyDelay(pause);
            #endif
            #ifdef TEST_ADC
            testADC();
            CyDelay(pause);
            #endif
            #ifdef TEST_COMM
            testComm();
            CyDelay(pause);
            #endif
            #ifdef TEST_PRINT_double
            testPrintdouble();
            #endif
            #ifdef TEST_I_SENSING
            testISensing();
            CyDelay(pause);
            #endif
            #ifdef TEST_TORQUE_CONTROLLER
            testTorqueController();
            CyDelay(pause);
            #endif
            #ifdef TEST_STRUCT
                LCD_ClearDisplay();
                printdouble(getValue(&thetaWheel),3);
                LCD_Position(1, 0);  //line feed
                printdouble(getDerivative(&thetaWheel),3);
                CyDelay(50);
            #endif
            #ifdef TEST_TORQUE_SENSING
                LCD_ClearDisplay();
                printdouble(getValue(&torque),3);
                CyDelay(50);
            #endif
            #ifdef TEST_RUNNING_AVG
                LCD_ClearDisplay();
                printdouble(adcRunningAvg,0);
                CyDelay(50);
            #endif
            #ifdef TEST_KT
                LCD_ClearDisplay();
                printdouble(getValue(&thetaWheel),3);
                LCD_Position(1, 0);  //line feed
                printdouble(getDerivativeWithoutUpdate(&thetaWheel),3);
                CyDelay(50);
            #endif
            #ifdef TEST_TIME
                LCD_ClearDisplay();
                getValue(&thetaShoulder);
                printdouble(getTime(&thetaShoulder),3);
                CyDelay(200);
            #endif
        }
        
    #endif
    
    #ifndef TEST
    //regular operation
    double u = 0;
    int i = 0;
    while(1)
    {
        i++;
        if(inLQRRange())
        {
            if(i==3)
            {
                LCD_ClearDisplay();
                LCD_PrintString("LQR");
                LCD_Position(1, 0);  //line feed
            }
            u = lqrController();
        }
        else
        {
            if(i==3)
            {
                LCD_ClearDisplay();
                LCD_PrintString("Energy");
                LCD_Position(1, 0);  //line feed
            }
            u = energyController();
            iError = 0;
        }
        if(i==3)
        {
            LCD_PrintString("mTheta:");
            printdouble(wrapAngle(getValueWithoutUpdate(&thetaShoulder))*1e3,0);
            i=0;
        }
        setTorque(u,1,1);
    }
    #endif
}



/* [] END OF FILE */