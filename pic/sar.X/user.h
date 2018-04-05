/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef USER_H
#define	USER_H

#include <xc.h> // include processor files - each processor file is guarded.  

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define LED_ROSSO   LATEbits.LATE2
#define LED_GIALLO  LATEbits.LATE1
#define LED_VERDE   LATEbits.LATE0

/* Encoder Destro collegato a RB5 */
#define ENCODER_SX  PORTBbits.RB4
/* Encoder Destro collegato a RB5 */
#define ENCODER_DX  PORTBbits.RB5

#define TMR0_VALUE      241

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */

void StartTimer0(void);

#endif	/* USER_H */

