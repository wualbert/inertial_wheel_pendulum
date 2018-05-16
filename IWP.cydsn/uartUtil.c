/* ========================================
 *
 * uartUtil.c
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

extern _Bool enableMotor;
#include "uartUtil.h"

void initUART()
{
    UART_Start();
}

void sendValue(int value, _Bool direction)
{
    if(!enableMotor)
    {
        UART_PutChar(0);
        static char hex[3];
        sprintf(hex, "%03d", 0);
        UART_PutString(hex);
        return;
    }
    //Sends a value between 0~255 with direction
    UART_PutChar(direction);
    //convert value to hex and send
    value = min(max(value,1),255);  //cap in range
    static char hex[3];
    sprintf(hex, "%03d", value);
    UART_PutString(hex);
    return;
}
/* [] END OF FILE */
