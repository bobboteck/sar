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

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    StartTimer0();

    while(1)
    {
        if(ENCODER_SX==1)
        {
            LED_ROSSO=1;
        }
        else
        {
            LED_ROSSO=0;
        }

        
        if(ENCODER_DX==1)
        {
            LED_VERDE=1;
        }
        else
        {
            LED_VERDE=0;    
        }
        
        //__delay_ms(1000);
    }
}

