#include "Filter.h"
#include "Filter_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is: Biquad
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelABiquadCoefficients Filter_ChannelABiquadCoefficients

/* Number of Biquad sections are: 5 */

const uint8 CYCODE Filter_ChannelABiquadCoefficients[Filter_BIQUAD_A_SIZE] = 
{
 /* Coefficients of Section 0 */
 0x64u, 0xCDu, 0x03u, 0x00u, /* Section(0)_A0, 0.0594110488891602 */

 0xC8u, 0x9Au, 0x07u, 0x00u, /* Section(0)_A1, 0.11882209777832 */

 0x64u, 0xCDu, 0x03u, 0x00u, /* Section(0)_A2, 0.0594110488891602 */

 0xD0u, 0xBEu, 0x0Eu, 0x00u, /* Section(0)_B1, -0.230396270751953 */

 0xF4u, 0x6Au, 0xF4u, 0x00u, /* Section(0)_B2, 0.180972099304199 */

 /* Coefficients of Section 1 */
 0x6Eu, 0xEBu, 0x0Fu, 0x00u, /* Section(1)_A0, 0.248744487762451 */

 0xDCu, 0xD6u, 0x1Fu, 0x00u, /* Section(1)_A1, 0.497488975524902 */

 0x6Eu, 0xEBu, 0x0Fu, 0x00u, /* Section(1)_A2, 0.248744487762451 */

 0x36u, 0x47u, 0x11u, 0x00u, /* Section(1)_B1, -0.269971370697021 */

 0x60u, 0x6Fu, 0xE7u, 0x00u, /* Section(1)_B2, 0.383827209472656 */

 /* Coefficients of Section 2 */
 0x37u, 0x63u, 0x0Fu, 0x00u, /* Section(2)_A0, 0.240430593490601 */

 0x6Du, 0xC6u, 0x1Eu, 0x00u, /* Section(2)_A1, 0.480860948562622 */

 0x37u, 0x63u, 0x0Fu, 0x00u, /* Section(2)_A2, 0.240430593490601 */

 0x7Au, 0x53u, 0x0Du, 0x00u, /* Section(2)_B1, -0.2082200050354 */

 0x58u, 0xB1u, 0xFBu, 0x00u, /* Section(2)_B2, 0.0673007965087891 */

 /* Coefficients of Section 3 */
 0x52u, 0x15u, 0x0Du, 0x00u, /* Section(3)_A0, 0.204426288604736 */

 0xA4u, 0x2Au, 0x1Au, 0x00u, /* Section(3)_A1, 0.408852577209473 */

 0x52u, 0x15u, 0x0Du, 0x00u, /* Section(3)_A2, 0.204426288604736 */

 0x29u, 0xAFu, 0x0Cu, 0x00u, /* Section(3)_B1, -0.198190927505493 */

 0x9Au, 0xFBu, 0xFEu, 0x00u, /* Section(3)_B2, 0.0158934593200684 */

 /* Coefficients of Section 4 */
 0x6Fu, 0x3Cu, 0x3Fu, 0x00u, /* Section(4)_A0, 0.98806357383728 */

 0xDEu, 0x78u, 0x7Eu, 0x00u, /* Section(4)_A1, 1.97612714767456 */

 0x6Fu, 0x3Cu, 0x3Fu, 0x00u, /* Section(4)_A2, 0.98806357383728 */

 0x5Du, 0xA6u, 0x15u, 0x00u, /* Section(4)_B1, -0.338279008865356 */

 0xC9u, 0x06u, 0xD1u, 0x00u, /* Section(4)_B2, 0.733960866928101 */
};

