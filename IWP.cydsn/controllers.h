/* ========================================
 *
 * Controllers.h
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
#ifndef CONTROLLERS_H
#define CONTROLLERS_H
#include<project.h>
#include <device.h>

void setTorque(double goalTorque, _Bool feedBack, _Bool feedForward);
double lqrController();
double energyController();
_Bool inLQRRange();

#endif

/* [] END OF FILE */
