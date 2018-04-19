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

/* Encoder Sinistro collegato a RB5 */
#define ENCODER_SX  PORTBbits.RB5
/* Encoder Destro collegato a RB4 */
#define ENCODER_DX  PORTBbits.RB4

#define TEST_OUT    LATCbits.LATC0

#define TMR0_VALUE      241

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

unsigned int Timer0Counter=0;
unsigned int encoderDxCounter=0;
unsigned int encoderSxCounter=0;

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */

void StartTimer0(void);

#endif	/* USER_H */

