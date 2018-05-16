#include "Filter_1.h"
#include "Filter_1_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is FIR
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelAFirCoefficients Filter_1_ChannelAFirCoefficients

/* Number of FIR filter taps are: 16 */

const uint8 CYCODE Filter_1_ChannelAFirCoefficients[Filter_1_FIR_A_SIZE] = 
{
 0x4Cu, 0x60u, 0x00u, 0x00u, /* Tap(0), 0.00293874740600586 */

 0xC0u, 0xB4u, 0x00u, 0x00u, /* Tap(1), 0.00551605224609375 */

 0xC1u, 0x54u, 0x01u, 0x00u, /* Tap(2), 0.0103989839553833 */

 0xC6u, 0x2Cu, 0x02u, 0x00u, /* Tap(3), 0.0169913768768311 */

 0x62u, 0x1Du, 0x03u, 0x00u, /* Tap(4), 0.024334192276001 */

 0xC0u, 0x00u, 0x04u, 0x00u, /* Tap(5), 0.0312728881835938 */

 0x9Au, 0xB1u, 0x04u, 0x00u, /* Tap(6), 0.0366699695587158 */

 0x3Du, 0x12u, 0x05u, 0x00u, /* Tap(7), 0.0396190881729126 */

 0x3Du, 0x12u, 0x05u, 0x00u, /* Tap(8), 0.0396190881729126 */

 0x9Au, 0xB1u, 0x04u, 0x00u, /* Tap(9), 0.0366699695587158 */

 0xC0u, 0x00u, 0x04u, 0x00u, /* Tap(10), 0.0312728881835938 */

 0x62u, 0x1Du, 0x03u, 0x00u, /* Tap(11), 0.024334192276001 */

 0xC6u, 0x2Cu, 0x02u, 0x00u, /* Tap(12), 0.0169913768768311 */

 0xC1u, 0x54u, 0x01u, 0x00u, /* Tap(13), 0.0103989839553833 */

 0xC0u, 0xB4u, 0x00u, 0x00u, /* Tap(14), 0.00551605224609375 */

 0x4Cu, 0x60u, 0x00u, 0x00u, /* Tap(15), 0.00293874740600586 */
};

