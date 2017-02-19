#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Vigenere.h"
#define NUMERO_LETTERE 26 //Numero lettere dell'alfabeto

void Test();

/*	Test per Vigenere.c
	Serve a controllare che tutte le funzioni implementate funzionino correttamente. */
void Test()
{
	/* --- Check della funzione inizializzaAlfabeto(link head) --- */
	inizializzaAlfabeto(head);
	//Per controllare che sia corretto stampiamo l'alfabeto due volte
	for (int i = 0; i < NUMERO_LETTERE * 2; i++) {
		printf("%c", head->carattere); head = head->next;
	}
	printf("\n");
	//Ora stampiamolo al contrario due volte per controllare i link ai nodi precedenti
	for (int i = 0; i < NUMERO_LETTERE * 2; i++) {
		printf("%c", head->carattere); head = head->prev;
	}
	printf("\n");


	/* --- Check della funzione codificaCarattere(char in, char key) --- */
	char in = 'a'; char key = 'a';
	printf("%c\n", codificaCarattere(in, key)); //a
	in = 'a'; key = 'b';
	printf("%c\n", codificaCarattere(in, key)); //b
	in = 'z'; key = 'b';
	printf("%c\n", codificaCarattere(in, key)); //a
	in = 'r'; key = 'v';
	printf("%c\n", codificaCarattere(in, key)); //m
	in = 'n'; key = 'e';
	printf("%c\n", codificaCarattere(in, key)); //r

	/* --- Check della funzione Codifica(FILE* in, FILE* out, char* key) --- */
	char* text1 = "Oà"; char* key1 = "VERME";
	Codifica(fmemopen(text1, strlen(text1), "r"), stdout, key1); //MEGBSMXFUQHIUUEOS
	printf("\n");
	char* text2 = "ATTACKATDAWN"; char* key2 = "LEMON";
	Codifica(fmemopen(text2, strlen(text2), "r"), stdout, key2); //LXFOPVEFRNHR
	printf("\n");

	/* --- Check della funzione Decodifica(FILE* in, FILE* out, char* key) --- */
	char* text3 = "MEGBSMXFUQHIUUEOS"; char* key3 = "VERME";
	Decodifica(fmemopen(text3, strlen(text3), "r"), stdout, key3); //RAPPORTOIMMEDIATO
	printf("\n");
	char* text4 = "LXFOPVEFRNHR"; char* key4 = "LEMON";
	Decodifica(fmemopen(text4, strlen(text4), "r"), stdout, key4); //ATTACKATDAWN
	printf("\n");

	/* -- Check della funzione IC(char* stringa) */
	char* text5 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
	printf("L'IC di questo testo e': %f\n", IC(text5)); //0.0650359

	/* -- Check della funzione chiquadro(char* stringa) */
	char* text6 = "The frequency of letters in text has been studied for use in cryptanalysis, and frequency analysis in particular.";
	printf("Il chi-quadrato di questo testo e': %f\n", chiquadro(text6)); //73.05 in inglese

	/* -- Check della funzione attaccaCesare(char* stringa) */
	char* text7 = "VURZJUGRGGUGVGJQKEOAGUGKKQVWQP";
	LetteraValore* val1 = attaccaCesare(text7, 0);
	printf("La chiave secondo Cesare di questo testo piu probabile e': %c\n", val1[0].carattere); //C

	/* -- Check della funzione trovaPeriodo() */
	char* text8 = "ETGU RLXRGA JGM, OMTGECGX ANU JCCM XB TFKT HR N FZNAHQNVZA BBWFKFL. XM ANU YCGX XUCK FT UIPCDC PVUHCZLIXH JKKF IAI JTZRXGKF QW YAUIEVZ, RGBXUGDGJL EAF GMGME, NPU FXL MAVVPTLX VP TPNIXBIIYEAC JCJ GVGMGGU. DDK QNPP WTTVF, EIWEMSTTRNWR ANU EMIAMAI DMGX XUCE Y IHSY VYYI AIYRVB WBQ UKJ BXIPBORRXV ABTB, ZJM EG VYC PZI BH KFXKXL PZLT, OMTGECGX HREZBTW XUCK FT AEQ CDYHLIQ GEMJZL ZQECN MS OG RZAX XB CSYCWSA JZQ RTVRGI YCW GBPTCCMVNVV MC T PVHV MU LXHFP. GI PEF QEJN MLRP KFPM LR DVEPG VRUVYGVL VPKM P GIJ EZNWXV.";
	printf("Il periodo potrebbe essere %d\n", trovaPeriodo(text8, 1, 15, 0)[0].periodo); //7

	/* -- Check della funzione attaccaVigenere() */
	LetteraValore** val = attaccaVigenere(text8, 7); //encrypt
	printf("La chiave piu' probabile e' %c%c%c%c%c%c%c\n", val[0][0].carattere, val[1][0].carattere, val[2][0].carattere, val[3][0].carattere, val[4][0].carattere, val[5][0].carattere, val[6][0].carattere);
}