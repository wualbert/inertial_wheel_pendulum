/* ========================================
 *
 * uartUtil.h
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

#ifndef UART_UTIL_H
#define UART_UTIL_H
#include <project.h>
#include <device.h>
    
#include "mathUtility.h"
void initUART();
void sendValue(int value, _Bool direction);
    
#endif
/* [] END OF FILE */
