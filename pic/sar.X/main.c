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

#include "system.h"         /* System funct/params, like osc/peripheral config */
#include "user.h"           /* User funct/params, such as InitApp */
#include "dterminal.h"      /*  */
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    unsigned char encoderDxCurrentValue=0, encoderSxCurrentValue=0;

    // Configure the oscillator for the device
    ConfigureOscillator();
    // Initialize I/O and Peripherals for application
    InitApp();
    // Start Timer0 running
    StartTimer0();
    // Initialize LDC
    LcdInit();
    LcdClear();
    LcdHome();
    LcdPuts("SAR");
    __delay_ms(1000);
    LcdPutUChar(0, 0, 4);
    LcdPutUChar(0, 0, 8);
    __delay_ms(1000);
    
    while(1)
    {
        // Il led rosso lampeggia ogni quarto di giro della ruota destra
        if(encoderSxCounter%10 == 0)
        {
            LED_ROSSO=!LED_ROSSO;
        }
        
        // Il led verde lampeggia ogni quarto di giro della ruota destra
        if(encoderDxCounter%10 == 0)
        {
            LED_VERDE=!LED_VERDE;
        }

        // 
        if(Timer0Counter>=10000)
        {
            Timer0Counter=0;
            LED_GIALLO=!LED_GIALLO;
            TEST_OUT=!TEST_OUT;
            encoderDxCurrentValue=encoderDxCounter;
            encoderSxCurrentValue=encoderSxCounter;
            encoderDxCounter=0;
            encoderSxCounter=0;
        }

        LcdPutUChar(encoderDxCurrentValue, 0, 8);
        LcdPutUChar(encoderDxCurrentValue, 0, 4);
    }
}