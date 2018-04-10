/*
 * File:   main.c
 * Author: bobboteck
 *
 * Created on 5 aprile 2018, 23.06
 */
/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/


void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    /* Initialize I/O and Peripherals for application */
    InitApp();
    StartTimer0();
    
    while(1)
    {
        if(encoderSxCounter<=20)
        {
            LED_ROSSO=0;
        }
        if(encoderSxCounter>20 && encoderSxCounter<40)
        {
            LED_ROSSO=1;
        }
        if(encoderSxCounter>=40)
        {
            encoderSxCounter=0;
        }
        
        
        
        if(encoderDxCounter>5)
        {
            LED_VERDE=!LED_VERDE;
            encoderDxCounter=0;
        }

        
        //__delay_ms(1000);
        
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
    }
}

