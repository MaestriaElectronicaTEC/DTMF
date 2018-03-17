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

/* Number of FIR filter taps are: 30 */

const uint8 CYCODE Filter_ChannelAFirCoefficients[Filter_FIR_A_SIZE] = 
{
 0x01u, 0x00u, 0x00u, 0x00u, /* Tap(0), 1.19209289550781E-07 */

 0x0Au, 0x00u, 0x00u, 0x00u, /* Tap(1), 1.19209289550781E-06 */

 0x3Fu, 0x00u, 0x00u, 0x00u, /* Tap(2), 7.51018524169922E-06 */

 0x17u, 0x01u, 0x00u, 0x00u, /* Tap(3), 3.3259391784668E-05 */

 0xC1u, 0x03u, 0x00u, 0x00u, /* Tap(4), 0.000114560127258301 */

 0xB7u, 0x0Au, 0x00u, 0x00u, /* Tap(5), 0.000326991081237793 */

 0x2Cu, 0x1Au, 0x00u, 0x00u, /* Tap(6), 0.000798702239990234 */

 0xEFu, 0x37u, 0x00u, 0x00u, /* Tap(7), 0.00170695781707764 */

 0x36u, 0x6Au, 0x00u, 0x00u, /* Tap(8), 0.00324130058288574 */

 0x2Bu, 0xB5u, 0x00u, 0x00u, /* Tap(9), 0.00552880764007568 */

 0xD9u, 0x17u, 0x01u, 0x00u, /* Tap(10), 0.00854027271270752 */

 0xCFu, 0x89u, 0x01u, 0x00u, /* Tap(11), 0.012018084526062 */

 0x0Du, 0xFBu, 0x01u, 0x00u, /* Tap(12), 0.0154739618301392 */

 0x28u, 0x57u, 0x02u, 0x00u, /* Tap(13), 0.018284797668457 */

 0x00u, 0x8Bu, 0x02u, 0x00u, /* Tap(14), 0.019866943359375 */

 0x00u, 0x8Bu, 0x02u, 0x00u, /* Tap(15), 0.019866943359375 */

 0x28u, 0x57u, 0x02u, 0x00u, /* Tap(16), 0.018284797668457 */

 0x0Du, 0xFBu, 0x01u, 0x00u, /* Tap(17), 0.0154739618301392 */

 0xCFu, 0x89u, 0x01u, 0x00u, /* Tap(18), 0.012018084526062 */

 0xD9u, 0x17u, 0x01u, 0x00u, /* Tap(19), 0.00854027271270752 */

 0x2Bu, 0xB5u, 0x00u, 0x00u, /* Tap(20), 0.00552880764007568 */

 0x36u, 0x6Au, 0x00u, 0x00u, /* Tap(21), 0.00324130058288574 */

 0xEFu, 0x37u, 0x00u, 0x00u, /* Tap(22), 0.00170695781707764 */

 0x2Cu, 0x1Au, 0x00u, 0x00u, /* Tap(23), 0.000798702239990234 */

 0xB7u, 0x0Au, 0x00u, 0x00u, /* Tap(24), 0.000326991081237793 */

 0xC1u, 0x03u, 0x00u, 0x00u, /* Tap(25), 0.000114560127258301 */

 0x17u, 0x01u, 0x00u, 0x00u, /* Tap(26), 3.3259391784668E-05 */

 0x3Fu, 0x00u, 0x00u, 0x00u, /* Tap(27), 7.51018524169922E-06 */

 0x0Au, 0x00u, 0x00u, 0x00u, /* Tap(28), 1.19209289550781E-06 */

 0x01u, 0x00u, 0x00u, 0x00u, /* Tap(29), 1.19209289550781E-07 */
};

