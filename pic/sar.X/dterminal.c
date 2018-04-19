/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>		/* For uint8_t definition */
#include <stdbool.h>	/* For true/false definition */
#include <stdlib.h>

#include "dterminal.h"
#include "system.h"
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/**************************************************************************
*** Abilita il display a leggere il dato inviato		  	  			***
**************************************************************************/
void LcdStrobe(void)
{
	LCD_EN=1;
	__delay_us(2);
	LCD_EN=0;
}

/**************************************************************************
*** Invia un byte al display in modalita 4 bit				  			***
***									  									***
*** c: byte da inviare al display					  					***
**************************************************************************/
void LcdWrite(unsigned char c)
{
	LCD_PORT_DATA=(unsigned char)((LCD_PORT_DATA & 0x0F) | (c & 0xF0));
    __delay_us(2);
	LcdStrobe();
	LCD_PORT_DATA=(unsigned char)((LCD_PORT_DATA & 0x0F) | (c << 4));
    __delay_us(2);
	LcdStrobe();
	__delay_us(100);
}

/**************************************************************************
*** Invia un comando al display 					  					***
***									  									***
*** c: il comando da inviare al display					  				***
**************************************************************************/
void LcdCommand(char c)
{
	LCD_RS=LCD_CMD;
	LcdWrite(c);
}

/**************************************************************************
*** Posiziona il cursore alla riga e colonna indicata dai parametri  	***
***									  									***
*** row: indica la righa a cui posizionare il cursore (indice da 0) 	***
*** col: indica la colonna a cui posizionare il	cursore (indice da 0)	***
**************************************************************************/
void LcdCursorPosition(unsigned char row, unsigned char col)
{
	unsigned char pos;

	LCD_RS=LCD_CMD;

	// imposta indirizzo base 
	switch(row)
	{
		case 0 : 
			pos=0x00;
			break;
		case 1 : 
			pos=0x40;
			break;
	}

	LcdWrite((unsigned char)(LCD_CMD_ADDRESS | (pos+col)));
}

/**************************************************************************
*** Canella il display e posiziona il cursore alla posizione home  	  	***
**************************************************************************/
void LcdClear(void)
{
	LCD_RS=LCD_CMD;
	LcdWrite(LCD_CMD_CLEAR);
    __delay_ms(3);
}

/**************************************************************************
*** Posiziona il cursore alla posizione home  	  						***
**************************************************************************/
void LcdHome(void)
{
	LCD_RS=LCD_CMD;
	LcdWrite(LCD_CMD_HOME);
    __delay_ms(3);
}

/**************************************************************************
*** Scrive un carattere sul display					  					***
***									  									***
*** c: carattere da visualizzare sul display	 			  			***
**************************************************************************/
void LcdPutch(unsigned char c)
{
	LCD_RS=LCD_DATA;
	LcdWrite(c);
}

/**************************************************************************
*** Scrive una stringa di caratteri sul display				  			***
***									  									***
*** s: stringa da visualizzare sul display				  				***
**************************************************************************/
void LcdPuts(const char *s)
{
	LCD_RS=LCD_DATA;
	while(*s)
		LcdWrite(*s++);
}

/**************************************************************************
*** Scrive sul display il numero passato come parametro in forma di		***
*** striga, posizionandolo nella possizione indicata					***
***																		***
*** numero: numero da visualizzare sul display							***
*** riga: indica la righa a cui posizionare il cursore (indice da 0) 	***
*** colonna: indica la colonna a cui posizionare il cursore (indice da 0)**
**************************************************************************/
void LcdPutUChar(unsigned char number, unsigned char row, unsigned char col)
{
	/***** Posizionamento del cursore *****/
	LcdCursorPosition(row,col);
	/***** Estrazione centinaia *****/
    unsigned char numeroCentinaia=(unsigned char)number/100;
	// Verifica se presente un numero per le centinaia da visualizzare
    if(numeroCentinaia>0)
    {
		LcdPutch('0'+numeroCentinaia);
    }
	else
    {
		LcdPutch('0');
    }
    // Rimuove dal numero le centinaia per l'elaborazione successiva
	number-=numeroCentinaia*100;
	/***** Estrazione decine *****/
	unsigned char numeroDecine=(unsigned char)number/10;

	if(numeroDecine>0)
		LcdPutch('0'+numeroDecine);
	else
		LcdPutch('0');
	
	number-=numeroDecine*10;
	/***** Estrazione unità *****/
	if(number!=0)
		LcdPutch('0'+number);
	else
		LcdPutch('0');
}

/**************************************************************************
*** Scrive sul display il numero passato come parametro in forma di		***
*** striga, posizionandolo nella possizione indicata					***
***																		***
*** numero: numero da visualizzare sul display							***
*** riga: indica la righa a cui posizionare il cursore (indice da 0) 	***
*** colonna: indica la colonna a cui posizionare il cursore (indice da 0)**
**************************************************************************/
void LcdPutUInt(unsigned int number, unsigned char row, unsigned char col)
{
	/***** Posiziona il cursore *****/
	LcdCursorPosition(riga, colonna);
	//***** Estrazione decine di migliaia *****
	unsigned int numeroDecineMigliaia=(unsigned int)number/10000;

	if(numeroDecineMigliaia>0)
	{
		LcdPutch('0'+numeroDecineMigliaia);
	}
	else
	{
		LcdPutch('0');
	}

	numero-=numeroDecineMigliaia*10000;
	//***** Estrazione migliaia *****
	unsigned int numeroMigliaia=(unsigned int)number/1000;

	if(numeroMigliaia>0)
	{
		LcdPutch('0'+numeroMigliaia);
	}
	else
	{
		LcdPutch('0');
	}

	numero-=numeroMigliaia*1000;
	/***** Estrazione centinaia *****/
    unsigned int numeroCentinaia=(unsigned int)number/100;
	// Verifica se presente un numero per le centinaia da visualizzare
    if(numeroCentinaia>0)
    {
		LcdPutch('0'+numeroCentinaia);
    }
	else
    {
		LcdPutch('0');
    }
    // Rimuove dal numero le centinaia per l'elaborazione successiva
	number-=numeroCentinaia*100;
	/***** Estrazione decine *****/
	unsigned int numeroDecine=(unsigned int)number/10;
	// Verifica se presente un numero per le decine da visualizzare
	if(numeroDecine>0)
	{
		LcdPutch('0'+numeroDecine);
	}
	else
	{
		LcdPutch('0');
	}
	// Rimuove dal numero le decine per l'elaborazione successiva
	number-=numeroDecine*10;
	/***** Estrazione unità *****/
	if(number!=0)
	{
		LcdPutch('0'+number);
	}
	else
	{
		LcdPutch('0');
	}
}

/**************************************************************************
*** Inizializza il display in modalita 4 bit il cursore � OFF, per	  	***
*** attivare il cursore cambiare il commento				  			***
**************************************************************************/
void lcd_init(void)
{
    LCD_RS=0;//LCD_CMD;
    LCD_EN=0;
    __delay_ms(20);
    
    LCD_PORT_DATA=(LCD_PORT_DATA & 0x0F) | 0x30;
    LcdStrobe();
    __delay_ms(10);
    
    //LCD_PORT_DATA=(LCD_PORT_DATA & 0x0F) | 0x30;
    LcdStrobe();
    __delay_us(300);
    
    //LCD_PORT_DATA=(LCD_PORT_DATA & 0x0F) | 0x30;
    LcdStrobe();
    __delay_ms(2);
    
    LCD_PORT_DATA=(LCD_PORT_DATA & 0x2F) | 0x20;	// set 4 bit mode
    LcdStrobe();
    __delay_ms(2);
    
    // 4 bit mode, 2 or more lines, 5x8 font
	LcdWrite(LCD_CMD_FS | LCD_FS_DL4 | LCD_FS_NRM | LCD_FS_F5X7);
	// display off
	LcdWrite(LCD_CMD_DC | LCD_DC_DISPLAY_OFF | LCD_DC_CURSOR_OFF | LCD_DC_CURBLINK_OFF);
	// display on, curson off, blink off
	LcdWrite(LCD_CMD_DC | LCD_DC_DISPLAY_ON | LCD_DC_CURSOR_OFF | LCD_DC_CURBLINK_OFF);
	// shift entry mode, display not shifted
	LcdWrite(LCD_CMD_EMS | LCD_EMS_INCREASE | LCD_EMS_SHIFT_OFF);
}