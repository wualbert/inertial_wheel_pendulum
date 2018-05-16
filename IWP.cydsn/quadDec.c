/* ========================================
 *
 * quadDec.c
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
#include "quadDec.h"
#include <math.h>
#include "mathUtility.h"
#include "hardwareParameters.h"

void initQuadDec()
{
    Clock_Enc_Motor_Start();                //starts clock
    Clock_Enc_Shoulder_Start();                //starts clock
    QuadDec_Motor_Start();
    QuadDec_Shoulder_Start();
    
    //Zero the decoders
    QuadDec_Motor_SetCounter(16384u);
    QuadDec_Shoulder_SetCounter(16384u);
}

int16 getMotorDecReading()
{
    return QuadDec_Motor_GetCounter();
}
int16 getShoulderDecReading()
{
    return QuadDec_Shoulder_GetCounter();
}
double getMotorAngleReading()
{
    return (getMotorDecReading()*MOTOR_DEC_RES);
}
double getShoulderAngleReading()
{   
    return (getShoulderDecReading()*SHOULDER_DEC_RES);
}
/* [] END OF FILE */
