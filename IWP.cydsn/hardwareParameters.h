/* ========================================
 *
 * hardwareParameters.h
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
#ifndef HARDWARE_PARAMETERS_H
#define HARDWARE_PARAMETERS_H
#include <math.h>


//Encoders
#define SHOULDER_ENC_COUNT 2025                                 //Counts per revolution
#define SHOULDER_DEC_RES 2*CY_M_PI/SHOULDER_ENC_COUNT              //Counts->Rad
#define MOTOR_ENC_COUNT 64                                     //Counts per revolution
#define MOTOR_DEC_RES 2*CY_M_PI/MOTOR_ENC_COUNT                 //Counts->Rad

//Power
//#define MOTOR_V_SUPPLY 18
#define MOTOR_V_SUPPLY 12
    
//Motor Electrical Properties
#define MOTOR_K_T 0.0097
#define MOTOR_R 6.400
#define ACTION_THRESHOLD 0
#define MAX_TORQUE MOTOR_K_T*MOTOR_V_SUPPLY/(MOTOR_R+ARRAY_R)
    
//ADC
//#define ARRAY_R 0.27
#define ADC_V_TO_I 1/0.246
#define ADC_SAMPLES 100

//Mechanical Properties
//MKS units
#define GRAVITY_MOMENT 0.018432700000000
#define INERTIA_ABOUT_SHOULDER 0.001974978760000
#define I_WHEEL 2.429610133333334e-04
#define G 9.81
#endif
/* [] END OF FILE */
