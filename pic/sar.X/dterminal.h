/* ----------------------------------------------------------------------------
 * 
 * 	Libreria per la gestione della scheda terminale con:
 *  - Display a matrice di punti su 2 righe
 *  - 3 Led (possibilità di un quarto Led)
 *  - 4 pulsanti
 *  Versione per il compilatore XC8 
 * 
 *	File  : dterminal.h	Ver.: 1.0.0	- Data creazione: 09/04/2018
 *		
 *	Autore: Roberto D'Amico (@bobboteck)
 *
 *	Dipendenze: delays.h - Ricordarsi di includerlo nel progamma pricipale
 * 
 *	Porte usate per default:
 *	PORTD bit 0 collegato al pin LCD RS
 *	PORTD bit 1 collegato al pin LCD EN
 *  PORTD bit 2 collegato al pin di Enable del 74574
 *  PORTD bit 3 collegato ai pulsanti
 *	PORTD bit 4-7 collegato ai pin LCD data bit 4-7
 *	
**	Per usare queste routine:
**	- settare le porte di I/O (TRISx) in funzione delle porte
**	  che state usando;
**	- modificare le impostazioni di lcd_init() se volete usare il display
**	  in modalit� diversa da quella di default;
**	- modificare le DEFINE (in questo file) LCD_RS, LCD_EN e 
**	  LCD_PORT_DATA, se volete usare porte del PIC diverse da quelle di
**	  default;
**	- la funzione lcd_write() usa i 4 bit pi� significativi della porta
**	  indicata da LCD_PORT_DATA.
**
**      NOTE
**	
**	La configurazione è scritta per funzionare con la RoboBoard 2.1 e il
**	display collgato sula porta D
**
** ----------------------------------------------------------------------- */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DTERMINAL_H
#define	DTERMINAL_H

#include <xc.h> // include processor files - each processor file is guarded.  

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* ========================================================================================= */
/* Modificare questi paramentri per cambiare le porte utilizzate per la gestione del display */
/* !!!ATTENZIONE!!! - Per i dati vengono utilizzati i 4 bit pi� significativi della porta    */
/* indicata da LCD_PORT_DATA								     							 */
/* ----------------------------------------------------------------------------------------- */
#define LCD_RS			PORTDbits.RD0	// Register select
#define LCD_EN			PORTDbits.RD1	// Enable
#define	LCD_PORT_DATA	PORTD	        // Porta di connesione per le linee Data

#define	LCD_CMD			0		        // Definisce modalit� Comando
#define	LCD_DATA		1		        // Definisce modalit� Data 
/* ========================================================================================= */

/* ========================================================================================= */
/* Comandi da inviare al display per la gestione di alcune funzioni			     			 */
/* !!!ATTENZIONE!!! - Per ogni comando devono essere usati in OR un elemento per ogni coppia */
/* di settaggi.										     									 */
/* ----------------------------------------------------------------------------------------- */

#define	LCD_CMD_CLEAR		0b00000001	// Comando Clear, per la cancellazione del display
#define	LCD_CMD_HOME		0b00000010	// Comando Home, porta il cursore nella posizione Home
#define LCD_CMD_ADDRESS		0b10000000	// Per posizionare il cursore all'indirizzo stabilito

// ---------------
// Entry Mode Set
// ---------------
#define LCD_CMD_EMS			0b00000100	// Comando per Entry Mode Set, da mettere in OR con i seguenti

#define LCD_EMS_INCREASE	0b00000010	// Imposta la scrittura da sinistra a destra
#define LCD_EMS_DECREASE	0b00000000	// Imposta la scrittura da destra a sinistra

#define LCD_EMS_SHIFT_ON	0b00000001	// Consente al testo di scorrere
#define LCD_EMS_SHIFT_OFF	0b00000000	// Impedisce al testo di scorrere
/* ----------------------------------------------------------------------------------------- */

// ------------------------
// Display On/Off Controll
// ------------------------
#define LCD_CMD_DC			0b00001000	// Comando per Display On/Off Controll da mettere in OR con i seguenti

#define LCD_DC_DISPLAY_ON	0b00000100	// Imposta la modalit� Display On
#define LCD_DC_DISPLAY_OFF	0b00000000	// Imposta la modalit� Display Off, i dati visalizzati restano comunque in memoria

#define LCD_DC_CURSOR_ON	0b00000010	// Imposta la modalit� Cursore On
#define LCD_DC_CURSOR_OFF	0b00000000	// Imposta la modalit� Cursore Off

#define LCD_DC_CURBLINK_ON	0b00000001	// Imposta la modalit� Cursore lampeggiante
#define LCD_DC_CURBLINK_OFF	0b00000000	// Imposta la modalit� Cursore non lampeggiante
/* ----------------------------------------------------------------------------------------- */

// ------------------------
// Cursor or Display Shift
// ------------------------
#define LCD_CMD_CDS		0b00010000	// Comando per lo shift del display o del cursore

#define LCD_CDS_MCL		0b00000000	// Sposta il cursore a sinistra
#define LCD_CDS_MCR		0b00000100	// Sposta il cursore a destra

#define LCD_CDS_MDL		0b00001000	// Sposta il display a sinistra
#define LCD_CDS_MDR		0b00001100	// Sposta il display a destra
/* ----------------------------------------------------------------------------------------- */

// -------------
// Function Set
// -------------
#define LCD_CMD_FS		0b00100000	// Comando per la definizione del modo di funzionamento

#define LCD_FS_DL8		0b00010000	// Imposta la modalit� di comunicazione dati a 8 bit
#define LCD_FS_DL4		0b00000000	// Imposta la modalit� di comunicazione dati a 4 bit

#define LCD_FS_NRM		0b00001000	// Imposta la modalit� a + righe
#define LCD_FS_NRS		0b00000000	// Imposta la modalit� a 1 riga

#define LCD_FS_F5X10	0b00000100	// Imposta la dimensione Font 5x10
#define LCD_FS_F5X7		0b00000000	// Imposta la dimensione Font 5x7
/* --------------------------------------------------------------------- */
/* ===================================================================== */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* Inizializza il display */
void LcdInit(void);
/* Canella il display e posiziona il cursore alla posizione home */
void LcdClear(void);
/* Posiziona il cursore alla posizione home */
void LcdHome(void);
/******************************************************************************
 * Posiziona il cursore alla riga e colonna indicata dai parametri
 *
 * @param row: indica la righa a cui posizionare il cursore (indice da 0)
 * @param col: indica la colonna a cui posizionare il	cursore (indice da 0)
******************************************************************************/
void LcdCursorPosition(unsigned char row, unsigned char col);
/******************************************************************************
 * Scrive un carattere sul display
 *
 * @param c: carattere da visualizzare sul display
******************************************************************************/
void LcdPutch(unsigned char c);
/******************************************************************************
 * Scrive una stringa di caratteri sul display
 *
 * @param s: stringa da visualizzare sul display
******************************************************************************/
void LcdPuts(const char *s);
/******************************************************************************
 * Scrive sul display il numero passato come parametro, posizionandolo nella 
 * possizione indicata dagli altri due parametri
 * 
 * @param numero: numero da visualizzare sul display
 * @param riga: indica la righa a cui posizionare il cursore (indice da 0)
 * @param colonna: indica la colonna a cui posizionare il cursore (indice da 0)
******************************************************************************/
void LcdPutUChar(unsigned char number, unsigned char row, unsigned char col);
/******************************************************************************
 * Scrive sul display il numero passato come parametro, posizionandolo nella 
 * possizione indicata dagli altri due parametri
 * 
 * @param numero: numero da visualizzare sul display
 * @param riga: indica la righa a cui posizionare il cursore (indice da 0)
 * @param colonna: indica la colonna a cui posizionare il cursore (indice da 0)
******************************************************************************/
void LcdPutUInt(unsigned int number, unsigned char row, unsigned char col);

#endif	/* DTERMINAL_H */