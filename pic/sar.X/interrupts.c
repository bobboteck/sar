/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <xc.h>         /* XC8 General Include File */
#include "user.h"        /* For true/false definition */

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
unsigned int counter_led=0;

/* High-priority service */
void interrupt high_isr(void)
{
    if(INTCONbits.TMR0IF==1)
    {
        counter_led++;
        /*Controlla se è passato il tempo della fine dell'impulso*/
        if(counter_led<10000)
        {
            /*Resetta l'uscita che pilota il LED*/
            LED_GIALLO=1;
        }
        /*Se sono passati 20mS*/
        if(counter_led>=10000 && counter_led < 20000)
        {
            /*Setta l'uscita che pilota il LED*/
            LED_GIALLO=0;
        }
        if(counter_led>=20000)
        {
            counter_led=0;
        }
        
        /*Reimposta il valore del Timer0 ed il Flag dell'interrupt*/
        TMR0L=(unsigned)TMR0_VALUE;
        INTCONbits.TMR0IF=0;
    }


}

/* Low-priority interrupt routine */
void low_priority interrupt low_isr(void)
{
    /* TODO Add Low Priority interrupt routine code here. */

    
}
