/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <stdlib.h>

#include "dterminal.h"
#include "system.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/**************************************************************************
*** Abilita il display a ricevere il dato inviato		  	  			***
**************************************************************************/
void lcd_strobe(void)
{
	LCD_EN=1;
//	DelayUs(1);
//	Delay10TCYx(1);
    /*__delay_us(1);*/__delay_us(2);
	LCD_EN=0;
}

/**************************************************************************
*** Invia un byte al display in modalita 4 bit				  			***
***									  									***
*** c: byte da inviare al display					  					***
**************************************************************************/
void lcd_write(unsigned char c)
{
	LCD_PORT_DATA=(unsigned char)((LCD_PORT_DATA & 0x0F) | (c & 0xF0));
    __delay_us(2);
	lcd_strobe();
	LCD_PORT_DATA=(unsigned char)((LCD_PORT_DATA & 0x0F) | (c << 4));
    __delay_us(2);
	lcd_strobe();
//	DelayUs(50);
//	Delay10TCYx(50);
    /*__delay_us(50);*/__delay_us(100);
}

/**************************************************************************
*** Invia un comando al display 					  					***
***									  									***
*** c: il comando da inviare al display					  				***
**************************************************************************/
void lcd_command(char c)
{
	LCD_RS=LCD_CMD;
	lcd_write(c);
}

/**************************************************************************
*** Posiziona il cursore alla riga e colonna indicata dai parametri  	***
***									  									***
*** row: indica la righa a cui posizionare il cursore (indice da 0) 	***
*** col: indica la colonna a cui posizionare il	cursore (indice da 0)	***
**************************************************************************/
void lcd_pos_cur(unsigned char row, unsigned char col)
{
unsigned char pos;

	LCD_RS=LCD_CMD;

	// imposta indirizzo base 
	switch(row)
	{
		case 0 : pos=0x00;
			break;
		case 1 : pos=0x40;
			break;
	}

	lcd_write((unsigned char)(LCD_CMD_ADDRESS | (pos+col)));
}

/**************************************************************************
*** Canella il display e posiziona il cursore alla posizione home  	  	***
**************************************************************************/
void lcd_clear(void)
{
	LCD_RS=LCD_CMD;
	lcd_write(LCD_CMD_CLEAR);
//	DelayMs(3);
//	Delay10KTCYx(3);
    __delay_ms(3);
}

/**************************************************************************
*** Posiziona il cursore alla posizione home  	  						***
**************************************************************************/
void lcd_home(void)
{
	LCD_RS=LCD_CMD;
	lcd_write(LCD_CMD_HOME);
//	DelayMs(3);
//	Delay10KTCYx(3);
    __delay_ms(3);
}

/**************************************************************************
*** Scrive un carattere sul display					  					***
***									  									***
*** c: carattere da visualizzare sul display	 			  			***
**************************************************************************/
void lcd_putch(unsigned char c)  // Modificata da char a unsigned
{
	LCD_RS=LCD_DATA;
	lcd_write(c);
}

/**************************************************************************
*** Scrive una stringa di caratteri sul display				  			***
***									  									***
*** s: stringa da visualizzare sul display				  				***
**************************************************************************/
void lcd_puts(const char *s)
{
	LCD_RS=LCD_DATA;
	while(*s)
		lcd_write(*s++);
}

/**************************************************************************
*** Scrive sul display il numero passato come parametro in forma di		***
*** striga, posizionandolo nella possizione indicata					***
***																		***
*** numero: numero da visualizzare sul display							***
*** riga: indica la righa a cui posizionare il cursore (indice da 0) 	***
*** colonna: indica la colonna a cui posizionare il cursore (indice da 0)**
**************************************************************************/
void lcd_put_uchar(unsigned char numero, unsigned char riga, unsigned char colonna)
{
	// Posizionamento del cursore 
	lcd_pos_cur(riga,colonna);
	/***** Estrazione centinaia *****/
    unsigned char NumeroCentinaia=(unsigned char)numero/100;
	// Verifica se presente un numero per le centinaia da visualizzare
    if((NumeroCentinaia)>0)
    {
		lcd_putch('0'+(NumeroCentinaia));
    }
	else
    {
		lcd_putch('0');
    }
    // Rimuove dal numero le centinaia per l'elaborazione successiva
	numero-=(NumeroCentinaia)*100;
	/***** Estrazione decine *****/
	if((numero/10)>0)
		lcd_putch('0'+(numero/10));
	else
		lcd_putch('0');
	numero-=(numero/10)*10;

	/***** Estrazione unità *****/
	if(numero!=0)
		lcd_putch('0'+numero);
	else
		lcd_putch('0');
}

/**************************************************************************
*** Scrive sul display il numero passato come parametro in forma di		***
*** striga, posizionandolo nella possizione indicata					***
***																		***
*** numero: numero da visualizzare sul display							***
*** riga: indica la righa a cui posizionare il cursore (indice da 0) 	***
*** colonna: indica la colonna a cui posizionare il cursore (indice da 0)**
**************************************************************************/
void lcd_put_uint(unsigned int numero, unsigned char riga, unsigned char colonna)
{
	char buffer[10];

    //lcd_clear();
    
	/***** Posiziona il cursore *****/
//	lcd_pos_cur(riga, colonna);
//
//	utoa(buffer, numero, 10);	//uint conv to buffer
//	lcd_puts(buffer);			//outputs to LCD


	//***** Estrazione decine di migliaia *****
	if((numero/10000)>0)
		lcd_putch('0'+(numero/10000));
	else
		lcd_putch('0');
	numero-=(numero/10000)*10000;

	//***** Estrazione migliaia *****
	if((numero/1000)>0)
		lcd_putch('0'+(numero/1000));
	else
		lcd_putch('0');
	numero-=(numero/1000)*1000;

	//***** Estrazione centinaia *****
	if((numero/100)>0)
		lcd_putch('0'+(numero/100));
	else
		lcd_putch('0');
	numero-=(numero/100)*100;
	
	//***** Estrazione decine *****
	if((numero/10)>0)
		lcd_putch('0'+(numero/10));
	else
		lcd_putch('0');
	numero-=(numero/10)*10;

	//***** Estrazione decine *****
	if(numero!=0)
		lcd_putch('0'+numero);
	else
		lcd_putch('0');

}

/**************************************************************************
*** Inizializza il display in modalita 4 bit il cursore ï¿½ OFF, per	  	***
*** attivare il cursore cambiare il commento				  			***
**************************************************************************/

void lcd_init(void)
{
    LCD_RS=0;//LCD_CMD;
    LCD_EN=0;
    __delay_ms(20);
    
    //LCD_PORT_DATA=(LCD_PORT_DATA & 0x0F) | 0x30;
    LATDbits.LATD4=1;
    LATDbits.LATD5=1;
    lcd_strobe();
    __delay_ms(10);//(>4.1ms)6++
    
    //LCD_PORT_DATA=(LCD_PORT_DATA & 0x0F) | 0x30;
    lcd_strobe();
    __delay_us(300);//(>100us)++
    
    //LCD_PORT_DATA=(LCD_PORT_DATA & 0x0F) | 0x30;
    lcd_strobe();
    __delay_ms(2);//++
    
    //LCD_PORT_DATA=(LCD_PORT_DATA & 0x2F) | 0x20;	// set 4 bit mode
    LATDbits.LATD4=0;
    lcd_strobe();
    __delay_ms(2);//2++
    
    // 4 bit mode, 2 or more lines, 5x8 font
	lcd_write(LCD_CMD_FS | LCD_FS_DL4 | LCD_FS_NRM | LCD_FS_F5X7);
	// display off
	lcd_write(LCD_CMD_DC | LCD_DC_DISPLAY_OFF | LCD_DC_CURSOR_OFF | LCD_DC_CURBLINK_OFF);
	// display on, curson off, blink off
	lcd_write(LCD_CMD_DC | LCD_DC_DISPLAY_ON | LCD_DC_CURSOR_OFF | LCD_DC_CURBLINK_OFF);
	// shift entry mode, display not shifted
	lcd_write(LCD_CMD_EMS | LCD_EMS_INCREASE | LCD_EMS_SHIFT_OFF);

}

void lcd_init_prec(void)
{
	LCD_RS=LCD_CMD;
//	DelayMs(15);		// Ritardo per l'accensione del display
//	Delay10KTCYx(15);
    /*__delay_ms(15);*/__delay_ms(20);

	LCD_PORT_DATA=(LCD_PORT_DATA & 0x0F) | 0x30;

	lcd_strobe();
//	DelayMs(5);
//	Delay10KTCYx(5);
    __delay_ms(5);
	lcd_strobe();
//	DelayUs(100);
//	Delay10TCYx(100);
    /*__delay_us(100);*/__delay_ms(5);
    
	lcd_strobe();
//	DelayMs(5);
//	Delay10KTCYx(5);
    __delay_ms(5);

	LCD_PORT_DATA=(LCD_PORT_DATA & 0x2F) | 0x20;	// set 4 bit mode

	lcd_strobe();
//	DelayUs(40);
//	Delay10TCYx(40);
    __delay_us(40);

	// 4 bit mode, 2 or more lines, 5x8 font
	lcd_write(LCD_CMD_FS | LCD_FS_DL4 | LCD_FS_NRM | LCD_FS_F5X7);
	// display off
	lcd_write(LCD_CMD_DC | LCD_DC_DISPLAY_OFF | LCD_DC_CURSOR_OFF | LCD_DC_CURBLINK_OFF);
	// display on, curson off, blink off
	lcd_write(LCD_CMD_DC | LCD_DC_DISPLAY_ON | LCD_DC_CURSOR_OFF | LCD_DC_CURBLINK_OFF);
	// shift entry mode, display not shifted
	lcd_write(LCD_CMD_EMS | LCD_EMS_INCREASE | LCD_EMS_SHIFT_OFF);
}