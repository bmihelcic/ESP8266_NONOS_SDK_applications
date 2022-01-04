#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#define USE_OPTIMIZE_PRINTF

/*IMPORTANT: the following configuration maybe need modified*/
/***********************************************************************************************************************/
#define CFG_HOLDER    0x00FF55A4    /* Change this value to load default configurations */

/*DEFAULT CONFIGURATIONS*/

#define STA_SSID ""    // your AP/router SSID to config your device networking
#define STA_PASS "" // your AP/router password

/* Configure timezone - uncomment one */
//#define TIMEZONE (-11) // UTC -11
//#define TIMEZONE (-10) // UTC -10
//#define TIMEZONE (-9)  // UTC -9
//#define TIMEZONE (-8)  // UTC -8
//#define TIMEZONE (-7)  // UTC -7
//#define TIMEZONE (-6)  // UTC -6
//#define TIMEZONE (-5)  // UTC -5
//#define TIMEZONE (-4)  // UTC -4
//#define TIMEZONE (-3)  // UTC -3
//#define TIMEZONE (-2)  // UTC -2
//#define TIMEZONE (-1)  // UTC -1
//#define TIMEZONE (0)   // UTC 0
#define TIMEZONE (1)   // UTC +1
//#define TIMEZONE (2)   // UTC +2
//#define TIMEZONE (3)   // UTC +3
//#define TIMEZONE (4)   // UTC +4
//#define TIMEZONE (5)   // UTC +5
//#define TIMEZONE (6)   // UTC +6
//#define TIMEZONE (7)   // UTC +7
//#define TIMEZONE (8)   // UTC +8
//#define TIMEZONE (9)   // UTC +9
//#define TIMEZONE (10)  // UTC +10
//#define TIMEZONE (11)  // UTC +11
//#define TIMEZONE (12)  // UTC +12
//#define TIMEZONE (13)  // UTC +13
/***********************************************************************************************************************/

/*Please Keep the following configuration if you have no very deep understanding of ESP SSL/TLS*/
#define CFG_LOCATION    0x79    /* Please don't change or if you know what you doing */


#endif

