/* ========================================
 *
 * controlParameters.h
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

#ifndef CONTROL_PARAMETERS_H
#define CONTROL_PARAMETERS_H
#include <project.h>
#include <device.h>
    
//Feedback torque controller PID
#define PID_KP 30.
#define PID_KI 0
#define PID_KD 8.

    
//Hand tuned controller
//#define K1 0.12
//#define K3 0.6 //0.09
//#define K4 0.0
    
//#define KI 0.012
#define KSetpoint 0.000216
#define MAX_I_ERR 0.02
//LQR
#define K1 0.4418
#define K3 0.1369
#define K4 0

#define THETA_SHOULDER_DESIRED CY_M_PI    

//Energy shaping controller
#define KE_P 200
#define KE_D 0
#define E_OFFSET 0.011
    
//Decision boundaries for switching to LQR
#define THETA_MAX 0.16
#define THETADOT_MAX 5

#endif
/* [] END OF FILE */
