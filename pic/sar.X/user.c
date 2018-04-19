/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    unsigned int dutycycle = 2000;
    
    /* Reset iniziale delle porte */
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    ANSEL0 = 0b00111111;
    ANSEL1 = 0b00000000;

    /* Setup analog functionality and port direction */
    
    /* PORTA tutti input per il convertitore AD */
    TRISA = 0b00111111;
    /* PORTB 
     * PWM (OUT RB0-RB3) 
     * input degli encoder (IN RB4-RB5)
     * programmazione (x RB6-RB7) */
    TRISB = 0b00110000;
    /* TBD */
    TRISC = 0b00000000;
    /* TBD */
    TRISD = 0b00000000;
    /* Impostati come OUT per i 3 LED di monitoraggio della batteria */
    TRISE = 0b11111000;

    /* Initialize peripherals */

    /* Configurazione Modulo AD */
    /*OpenADC(ADC_CONV_SINGLE_SHOT | ADC_MODE_SINGLE_CH | ADC_CONV_SEQ_SEQM1 | ADC_INT_OFF,
            ADC_REF_VDD_VSS | ADC_FIFO_DIS | ADC_TRIG_TMR_5,
            ADC_RIGHT_JUST | ADC_10_TAD | ADC_FOSC_8);  */
    /* CONFIGURAZIONE PWM */
    // Power Timer Control
    PTCON0 = 0b11110000; // 1:16 postscaler, 1:1 prescale, free running
    PTCON1 = 0b10000000; // PWM time base ON, count up
    // Impostazione periodo
    PTPERH = 0x01;
    PTPERL = 0xff;
    // PWM Control
    PWMCON0 = 0b00110000; // PWM0:PWM3 Abilitati
    PWMCON1 = 0b11110000; // 1:16 postscaler, updates abilitati, override asincrono
    DTCON = 0x00; // dead time 0ns
    // Output Override
    OVDCOND = 0b00111111; // L'output � controllato dal DutyCycle e TimeBase
    OVDCONS = 0b00000000; // Tutti i pin sono INACTIVE quando in override
    // Fault Configuration
    FLTCONFIG = 0x00; // Fault A e B disabilitati
    // Impostazione DutyCycle
    PDC0H = dutycycle >> 8;PDC0L = dutycycle;
    PDC1H = dutycycle >> 8;PDC1L = dutycycle;
    
    /*Impostazione Timer0*/
    T0CONbits.T016BIT=1;    // 8 bit mode
    T0CONbits.T0CS=0;       // Use internal clock
    T0CONbits.T0SE=0;       // Not used for internal clock
    T0CONbits.PSA=0;        // Prescaler enabled
    T0CONbits.T0PS0=1;      // Prescaler 1:64
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=1;
    T0CONbits.TMR0ON=0;     // Timer0 OFF

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */
    RCONbits.IPEN=1;        // Abilit� la priorita per gli interrupt
    INTCONbits.GIEH=0;      // Disabilita tutti gli Interrupt (High)
    INTCONbits.GIEL=0;      // Disabilita tutti gli Interrupt (Low)
    INTCONbits.TMR0IF=0;    // Resetta il Flag dell'int del Timer0, va resettato sempre a mano
	PIR1bits.ADIF=0;		// Resetta il Flag dell'int del ADC, va resettato sempre a mano
    INTCONbits.RBIF=0;      // Resetta il Flag dell'int delle RB on change, va resettato sempre a mano
    
    INTCON2bits.TMR0IP=1;   // L'int del Timer0 � definito di High priority
    INTCON2bits.RBIP=1;     // L'int su RB � definito di High priority
    
    IPR1bits.ADIP=0;        // Int ADC definito Low priority

    /* Enable interrupts */
    INTCONbits.TMR0IE=1;    // Abilita l'interrupt sul Timer0
    INTCONbits.RBIE=1;      // Abilita l'interrupt su RB
    PIE1bits.ADIE=1;        // Abilita l'interrupt sul ADC
    INTCONbits.GIEH=1;      // Abilita tutti gli Interrupt (High)
    INTCONbits.GIEL=1;      // Abilita tutti gli Interrupt (Low)
}

void StartTimer0()
{
    Timer0Counter=0;
    TMR0L=TMR0_VALUE;       // Imposta il valore da assegnare al contatore del Timer0
    T0CONbits.TMR0ON=1;
}



