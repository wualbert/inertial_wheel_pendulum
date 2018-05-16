/* ========================================
 *
 * controllers.c
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
#include <math.h>
#include "mathUtility.h"
#include "hardwareParameters.h"
#include "controlParameters.h"
#include "hardware.h"
#include "sensorStructs.h"


// variables from main.c
extern MemoryVariable thetaShoulder;
extern MemoryVariable thetaWheel;
extern MemoryVariable torque;
extern double iError;
//double prevTimeStamp = 0;

//currently unused
//extern double positiveFreeTorque;
//extern double negativeFreeTorque;

double lqrController()
{   
    //returns the target torque
    double thetaShoulderValue = getValue(&thetaShoulder);
    double thetaShoulderDot = getDerivativeWithoutUpdate(&thetaShoulder);
    double thetaWheelDot = getDerivativeWithoutUpdate(&thetaWheel);//cw+ when wheel facing out
    //printdouble(thetaShoulderDot*1e2,0);
    //Offset gain
    double offset = KSetpoint*thetaWheelDot;
    
    double wrappedTheta = wrapAngle(thetaShoulderValue-(THETA_SHOULDER_DESIRED+offset));
    //double timeDiff = getTime(&thetaShoulder)-prevTimeStamp;    
    //iError+=wrappedTheta*timeDiff;
    //prevent windup
    //iError=max(min(iError,MAX_I_ERR),-MAX_I_ERR);
    
    double u = K1*wrappedTheta+K3*thetaShoulderDot+K4*thetaWheelDot;//+KI*iError;
    //prevTimeStamp = getTime(&thetaShoulder);
    
    //double u = K3*thetaShoulderDot;
    return -u;
}
double temp=0;
double energyController()
{

    double thetaShoulderValue = wrapAngle(getValue(&thetaShoulder));
    double thetaShoulderDot = getDerivativeWithoutUpdate(&thetaShoulder);
    //Compensation term for gravity 
    
    //Calculate current energy
    double kineticE = 0.5*INERTIA_ABOUT_SHOULDER*pow(thetaShoulderDot,2);
    double potentialE = -GRAVITY_MOMENT*G*cos(thetaShoulderValue);
    double totalE = kineticE + potentialE;    
    double energyDiff = totalE-(GRAVITY_MOMENT*G+E_OFFSET);
/*
    temp = max(temp,totalE);

    double b = GRAVITY_MOMENT*G*sin(thetaShoulderValue);
    
    double u = -b-INERTIA_ABOUT_SHOULDER*b/(INERTIA_ABOUT_SHOULDER+I_WHEEL)*Ke*thetaShoulderDot/2*energyDiff;
    //return u;

*/
    //PD energy shaping
    int direction = thetaShoulderDot>0?-1:1;
    int magnitude = KE_P*energyDiff;
    //LCD_ClearDisplay();
    //printdouble(direction*magnitude,3);
    
    return direction*magnitude;
    //return u;
}

_Bool inLQRRange()
{    
    double thetaShoulderValue = wrapAngle(getValue(&thetaShoulder));
    double thetaShoulderDot = getDerivativeWithoutUpdate(&thetaShoulder);
    double wrappedTheta = wrapAngle(thetaShoulderValue-THETA_SHOULDER_DESIRED);
    if (fabs(wrappedTheta)<THETA_MAX&&fabs(thetaShoulderDot)<THETADOT_MAX)
    {
        //Switch to LQR
        return 1;
    }
    
    return 0;
}

void setTorque(double goalTorque, _Bool feedBack, _Bool feedForward)
{
    //calculate feedfoward component
    double omegaM = getDerivative(&thetaWheel);
    double uFeedForward = (goalTorque+MOTOR_K_T*MOTOR_K_T*omegaM/MOTOR_R)*MOTOR_R/MOTOR_K_T;
    
    //calculate feedback comoponent
    double measuredTorque = getValue(&torque);
    double measuredTorqueDeri = getDerivativeWithoutUpdate(&torque);
    
    //TODO: I and D
    double uFeedBack = PID_KP*(goalTorque-measuredTorque)-PID_KD*measuredTorqueDeri;
    double totalU = 0;
    if(feedForward)
    {
        totalU += uFeedForward;
    }
    if(feedBack) 
    {
        totalU += uFeedBack;
    }
    
    //double totalU = uFeedForward;
    //send torque command
    int pwm = round(totalU/MOTOR_V_SUPPLY*256);
    //Threshold for control action
    pwm = abs(pwm)>10?pwm:0;
    _Bool direction = pwm>0?1:0;
    //Debug
    //printdouble(pwm,0);
    sendValue(max(min(abs(pwm),255),0),direction);
    return;
}
/* [] END OF FILE */
