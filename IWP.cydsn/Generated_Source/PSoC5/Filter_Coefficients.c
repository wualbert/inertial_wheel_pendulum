#include "Filter.h"
#include "Filter_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is FIR
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelAFirCoefficients Filter_ChannelAFirCoefficients

/* Number of FIR filter taps are: 16 */

const uint8 CYCODE Filter_ChannelAFirCoefficients[Filter_FIR_A_SIZE] = 
{
 0x08u, 0x77u, 0x00u, 0x00u, /* Tap(0), 0.00363254547119141 */

 0xFAu, 0x7Bu, 0x00u, 0x00u, /* Tap(1), 0.0037834644317627 */

 0xB6u, 0xF4u, 0xFEu, 0x00u, /* Tap(2), -0.00815701484680176 */

 0xE8u, 0xF0u, 0xFBu, 0x00u, /* Tap(3), -0.0317106246948242 */

 0x9Eu, 0x57u, 0xFCu, 0x00u, /* Tap(4), -0.028576135635376 */

 0x15u, 0x7Au, 0x06u, 0x00u, /* Tap(5), 0.0506006479263306 */

 0x98u, 0x0Cu, 0x19u, 0x00u, /* Tap(6), 0.195696830749512 */

 0xDCu, 0x61u, 0x28u, 0x00u, /* Tap(7), 0.315486431121826 */

 0xDCu, 0x61u, 0x28u, 0x00u, /* Tap(8), 0.315486431121826 */

 0x98u, 0x0Cu, 0x19u, 0x00u, /* Tap(9), 0.195696830749512 */

 0x15u, 0x7Au, 0x06u, 0x00u, /* Tap(10), 0.0506006479263306 */

 0x9Eu, 0x57u, 0xFCu, 0x00u, /* Tap(11), -0.028576135635376 */

 0xE8u, 0xF0u, 0xFBu, 0x00u, /* Tap(12), -0.0317106246948242 */

 0xB6u, 0xF4u, 0xFEu, 0x00u, /* Tap(13), -0.00815701484680176 */

 0xFAu, 0x7Bu, 0x00u, 0x00u, /* Tap(14), 0.0037834644317627 */

 0x08u, 0x77u, 0x00u, 0x00u, /* Tap(15), 0.00363254547119141 */
};

