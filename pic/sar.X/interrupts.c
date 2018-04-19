/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <xc.h>         /* XC8 General Include File */
#include "user.h"
#include <stdbool.h>    /* For true/false definition */

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
unsigned char prevEncoderDxValue=0;
unsigned char prevEncoderSxValue=0;

/* High-priority service */
void interrupt high_isr(void)
{
    if(INTCONbits.TMR0IF==1)
    {
        Timer0Counter++;
        /*Reimposta il valore del Timer0 ed il Flag dell'interrupt*/
        TMR0L=(unsigned)TMR0_VALUE;
        INTCONbits.TMR0IF=0;
    }

    if(INTCONbits.RBIF==1)
    {
        if(ENCODER_DX!=prevEncoderDxValue)
        {
            encoderDxCounter++;
            prevEncoderDxValue=ENCODER_DX;
        }
        
        if(ENCODER_SX!=prevEncoderSxValue)
        {
            encoderSxCounter++;
            prevEncoderSxValue=ENCODER_SX;
        }
        
        INTCONbits.RBIF=0;
    }
}

/* Low-priority interrupt routine */
void low_priority interrupt low_isr(void)
{
    /* TODO Add Low Priority interrupt routine code here. */

    
}
