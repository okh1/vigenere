#pragma once
#include <stdio.h>

/*	Funzione che si occupa della codifica tramite cifrario di Vigenere.
	FILE* in � il file di ingresso da cui leggere il testo da cifrare.
	FILE* out � il file di uscita dove scrivere il testo cifrato.
	char* key � la stringa chiave ("verme").
	Ritorna 0 se riuscito, un altro numero se incontra un errore. */
int Codifica(FILE* in, FILE* out, char* key);

/*	Funzione che si occupa della decodifica di un testo tramite cifrario di Vigenere.
	FILE* in � il file di ingresso da cui leggere il testo cifrato.
	FILE* out � il file di uscita dove scrivere il testo decodificato.
	char* key � la stringa chiave da utilizzare per la decodifica.
	Ritorna 0 se riuscito, un altro numero se incontra un errore. */
int Decodifica(FILE* in, FILE* out, char* key);

/*	Funzione che si occupa dell'attacco a un testo cifrato secondo Vigenere.
	L'attacco � diviso in una prima parte di ricerca della lunghezza della chiave
	e in una seconda parte di ricerca delle chiavi pi� probabili.
	Entrambi i processi vengono mostrati a video all'utente. 
	FILE* in � il file di infresso da cui leggere il testo cifrato. */
void Attacco(FILE* in);