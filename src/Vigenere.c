#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Vigenere.h"
#define NUMERO_LETTERE 26 //Numero lettere dell'alfabeto

typedef struct Lettera* link; //link è un tipo che rappresenta un puntatore a Lettera

typedef struct Lettera {
	char carattere; //Lettera (esempio 'a', 'b', ...)
	link prev; //Puntatore al nodo/lettera precedente nella lista
	link next; //Puntatore al nodo/lettera successivo nella lista
} Lettera; //Struct che rappresenta il nodo di una lista doppiamente concatenata

typedef struct LetteraValore {
	char carattere; //Lettera dell'alfabeto
	float valore; //Un certo valore associato alla lettera
} LetteraValore;

typedef struct PeriodoValore {
	int periodo; //Lunghezza della chiave
	float valore; //Un certo valore associato al periodo
} PeriodoValore;

void inizializzaAlfabeto();
void inizializzaProbabilita();
char codificaCarattere(char in, char key);
char decodificaCarattere(char in, char key);
char convertiLetteraAccentata(char c);
float IC(char* stringa);
float chiquadro(char* stringa);
PeriodoValore* trovaPeriodo(char* text, int min, int max);
LetteraValore* attaccaCesare(char* stringa);
LetteraValore** attaccaVigenere(char* testo, int lunghezza_periodo);
void insertionSort_LetteraValore(LetteraValore* array, int l, int r);
void insertionSort_PeriodoValore(PeriodoValore* array, int l, int r);
char* ReadToEnd(FILE* in);
float pow_mia(float base, int esponente);

link head = NULL;	//Puntatore alla testa della lista, che in pratica sarà la testa dell'alfabeto, cioè la lettera 'a'
					//Ora lo impostiamo a NULL perché non abbiamo ancora creato la lista

float* prob = NULL; //Array di dimensione NUMERO_LETTERE che contiene le frequenze delle lettere. Letto da file.

int Codifica(FILE* in, FILE* out, char* key)
{
	//Inizializziamo l'alfabeto
	inizializzaAlfabeto();
	//Stabiliamo la lunghezza della chiave
	int length = strlen(key); if (length <= 0) return 0;
	int i = 0; //Siamo per ora alla posizione 0 della chiave
	
	char c; //Qui leggeremo ogni carattere del file, uno per volta
	while ((c = fgetc(in)) != EOF) //Per ogni carattere, fino alla fine del file di input
	{
		char c_out; //Qui scrivero il carattere codificato da stampare
		c = convertiLetteraAccentata(c); //Gestisco le lettere accentate
		if (c < 0 || c > 255 || !isalpha(c)) 
		{
			//Gestisco caratteri non alfabetici, non codificandoli
			c_out = c;
		}
		else
		{
			//Codifichiamo la lettera
			c_out = codificaCarattere(tolower(c), tolower(key[i])); //Ricordiamoci di convertirla prima in minuscolo
			//Seleziono la lettera successiva della key
			i++;
			if (i >= length) //Se la chiave è finita, torno al suo carattere iniziale
				i = 0;
		}
		//Stampo la lettera codificata out sul file d'uscita
		fprintf(out, "%c", c_out);
	}

	return 1;
}

int Decodifica(FILE* in, FILE* out, char* key)
{
	//Inizializziamo l'alfabeto
	inizializzaAlfabeto();
	//Stabiliamo la lunghezza della chiave
	int length = strlen(key); if (length <= 0) return 0;
	int i = 0; //Siamo per ora alla posizione 0 della chiave

	char c; //Qui leggeremo ogni carattere del file, uno per volta
	while ((c = fgetc(in)) != EOF) //Per ogni carattere, fino alla fine del file di input
	{
		char c_out; //Qui scrivero il carattere decodificato da stampare
		if (c < 0 || c > 255 || !isalpha(c))
		{
			//Gestisco caratteri non alfabetici, non decodificandoli
			c_out = c;
		}
		else
		{
			//Deodifichiamo la lettera
			c_out = decodificaCarattere(tolower(c), tolower(key[i])); //Ricordiamoci di convertirla prima in minuscolo
			//Seleziono la lettera successiva della key	
			i++;	
			if (i >= length) //Se la chiave è finita, torno al suo carattere iniziale
				i = 0;
		}
		//Stampo la lettera decodificata out sul file d'uscita, maiuscola se era maiuscola, minuscola se era minuscola
		fprintf(out, "%c", c_out);
	}

	return 1;
}

void Attacco(FILE* in)
{
	char* stringa = ReadToEnd(in);
	int min, max;
	printf("Insert the smallest period (length of keyword) you want to try:\n");
	scanf("%d", &min);
	printf("Insert the largest period (length of keyword) you want to try:\n");
	scanf("%d", &max);
	PeriodoValore* periodi = trovaPeriodo(stringa, min, max);
	printf("Most likely periods (length of keyword) are, from the most likely:\n");
	for (int i = 0; i < max - min + 1; i++)
		printf("%d ", periodi[i].periodo);
	printf("\nWhich period do you want to use to try and decode the text?\n");
	int periodo;
	scanf("%d", &periodo);
	LetteraValore** lettere = attaccaVigenere(stringa, periodo);
	printf("The ten most likely letters for each position of the keyword are:\n");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < periodo; j++)
			printf("%c ", lettere[j][i].carattere);
		printf("\n");
	}
}


//Funzione che codifica la lettera in attraverso la lettera chiave key.
char codificaCarattere(char in, char key)
{
	//Inizializziamo l'alfabeto
	inizializzaAlfabeto(head);
	link a = head;

	//Convertiamo tutto in minuscolo
	in = tolower(in); key = tolower(key);

	int shift = 0; //Questo numero indica di quanto dovremo spostare la lettera in
	//Stabiliamo lo shift traversando la lista dalla prima lettera, la 'a'
	while (a->carattere != key) //Andiamo avanti nell'alfabeto fino a trovare la lettera key
	{
		shift++; a = a->next;
	}
	//A questo punto dobbiamo andare avanti di shift lettere nell'alfabeto a partire dalla lettera in
	//Prima di tutto cerchiamo la lettera in nell'alfabeto
	a = head; //Ripartiamo dalla 'a'
	while (a->carattere != in) //Andiamo avanti nell'alfabeto fino a trovare la lettera in
		a = a->next;
	//Ora andiamo avanti di shift lettere
	for (int i = 0; i < shift; i++)
		a = a->next;
	//Abbiamo trovato il carattere codificato
	return a->carattere;
}

//Funzione che decodifica la lettera in attraverso la lettera chiave key.
char decodificaCarattere(char in, char key)
{
	//Inizializziamo l'alfabeto
	inizializzaAlfabeto(head);
	link a = head;

	//Convertiamo tutto in minuscolo
	in = tolower(in); key = tolower(key);

	int shift = 0; //Questo numero indica di quanto dovremo spostare la lettera in
				   //Stabiliamo lo shift traversando la lista dalla prima lettera, la 'a'
	while (a->carattere != key) //Andiamo avanti nell'alfabeto fino a trovare la lettera key
	{
		shift++; a = a->next;
	}
	//A questo punto dobbiamo andare indietro di shift lettere nell'alfabeto a partire dalla lettera in
	//Prima di tutto cerchiamo la lettera in nell'alfabeto
	a = head; //Ripartiamo dalla 'a'
	while (a->carattere != in) //Andiamo avanti nell'alfabeto fino a trovare la lettera in
		a = a->next;
	//Ora andiamo indietro di shift lettere
	for (int i = 0; i < shift; i++)
		a = a->prev;
	//Abbiamo trovato il carattere decodificato
	return a->carattere;
}

//Funzione che si occupa di allocare in memoria la lista circolare
//doppiamente concatenata che rappresenta l'alfabeto di lettere minuscole.
void inizializzaAlfabeto()
{
	if (head == NULL) //Inizializziamo la lista solo se non è stato ancora fatto
	{
		//Alloco la prima lettera, la 'a'
		link a = (Lettera*)malloc(1 * sizeof(Lettera));
		a->carattere = 'a';
		a->prev = NULL;
		a->next = NULL;
		//Alloco le altre lettere
		link prev = a; //Contiene il puntatore alla lettera precedente
		for (int i = 1; i < NUMERO_LETTERE; i++, prev = prev->next)
		{
			//Alloco una lettera e la inizializzo
			Lettera* node = (Lettera*)malloc(1 * sizeof(Lettera)); //Creiamo spazio in memoria
			node->carattere = 'a' + i; //Assegniamo il giusto carattere
			node->prev = prev; //Il link al nodo precedente è in prev
			prev->next = node; //Il nodo precedente ha ora un successore, cioè il nodo che abbiamo appena creato
			node->next = NULL; //Per ora il successore di questo nodo non c'è
		}
		//Collego l'ultima lettera, la 'z', alla prima, la 'a', così da creare una lista circolare
		prev->next = a;
		a->prev = prev;
		head = a;
	}
}

//Funzione che calcola l'indice di coincidenza di un testo contenuto in stringa
float IC(char* stringa)
{
	int* occorrenze = (int*)malloc(NUMERO_LETTERE * sizeof(int)); //Vettore che conterrà il numero di occorrenze per ogni lettera
	//Inizializzazione
	for (int i = 0; i < NUMERO_LETTERE; i++)
		occorrenze[i] = 0;
	int lunghezza = 0; //Intero che conterrà il numero di lettere di stringa
	for (int i = 0; i < strlen(stringa); i++)
	{
		char lettera = tolower(stringa[i]);
		if (isalpha(lettera))
		{
			//Se il carattere corrente è una lettera, la conteggiamo
			occorrenze[lettera - 'a']++; lunghezza++;
		}
	}
	//Calcoliamo l'indice di coincidenza usando la formula
	float somma = 0;
	for (int i = 0; i < NUMERO_LETTERE; i++)
		somma += occorrenze[i] * (occorrenze[i] - 1);
	somma /= lunghezza * (lunghezza - 1);
	return somma;
}

//Funzione che analizza i periodi da min e max (compresi) sul testo cifrato text.
//Calcola i periodi più probabili usando l'indice di coincidenza.
//Ritorna un array di PeriodoValore ordinato dal periodo più probabile, cioè quello con IC maggiore.
PeriodoValore* trovaPeriodo(char* text, int min, int max)
{
	//Allochiamo l'array che conterrà l'IC medio per ogni periodo da min a max
	PeriodoValore* ic_medio = (PeriodoValore*)malloc((max - min + 1)*sizeof(PeriodoValore));
	//float* ic_medio = (float*)malloc((max - min + 1) * sizeof(float));
	//Per ogni periodo calcolo l'IC medio
	for (int i = min; i <= max; i++)
	{
		int j, k; //j è il contatore che va avanti in text, k conta solo le lettere alfabetiche
		//Alloco e inizializzo a vuote le i sequenze
		char** sequenze = (char**)malloc(i  *sizeof(char*));
		for (j = 0; j < i; j++)
		{
			sequenze[j] = (char*)calloc((strlen(text) / i + 2), sizeof(char));
		}
		//Concateno ogni carattere nella corretta sequenza
		for (j = 0, k = 0; j < strlen(text); j++)
		{
			char lettera = tolower(text[j]);
			if (isalpha(lettera))
			{
				int indice = k % i; k++; //In quale sequenza devo inserire la lettera
				strncat(sequenze[indice], text + j, 1); //Aggiungo la lettera nella sequenza
			}
		}
		//Calcolo l'IC medio tra le sequenze
		float media = 0;
		for (j = 0; j < i; j++) //Per ognuna delle i sequenze
		{
			media += IC(sequenze[j]);
		}
		media = media / i;
		ic_medio[i - min].periodo = i;
		ic_medio[i - min].valore = media; //Salvo l'IC medio per questo periodo
	}
	//Ordino l'array ic_medio in ordine decrescente
	insertionSort_PeriodoValore(ic_medio, 0, max - min);

	return ic_medio;
}

//Funzione che popola l'array globale prob con le frequenze delle NUMERO_LETTERE
//lettere dell'alfabeto, leggendole da file.
void inizializzaProbabilita()
{
	prob = (float*)malloc(NUMERO_LETTERE * sizeof(float));
	FILE* fp = fopen("prob-it.txt", "r");
	for (int i = 0; i < NUMERO_LETTERE; i++)
		fscanf(fp, "%f", &prob[i]);
}

//Funzione che ritorna il valore del test del chi-quadrato per una stringa
//rispetto alle frequenze attese salvate nell'array globale prob
float chiquadro(char* stringa)
{
	//Se non è già stato inizializzato, inizializzo l'array prob
	if (prob == NULL) inizializzaProbabilita();

	int* occorrenze = (int*)calloc(NUMERO_LETTERE, sizeof(int)); //Vettore che conterrà il numero di occorrenze per ogni lettera
	int lunghezza = 0; //Intero che conterrà il numero di lettere di stringa
	for (int i = 0; i < strlen(stringa); i++)
	{
		char lettera = tolower(stringa[i]);
		if (isalpha(lettera))
		{
			//Se il carattere corrente è una lettera, la conteggiamo
			occorrenze[lettera - 'a']++; lunghezza++;
		}
	}
	//Calcoliamo il valore del chi-quadro usando la formula e le frequenze contenute in prob
	float chiquadro = 0;
	for (int i = 0; i < NUMERO_LETTERE; i++)
		chiquadro += (prob[i] != 0) ? pow_mia(occorrenze[i] - prob[i] * lunghezza, 2) / (prob[i] * lunghezza) : 0;
	return chiquadro;

}

//Funzione che prova a decifrare un testo contenuto in stringa cifrata secondo Cesare.
//Utilizza il test del chi-quadrato.
//Ritorna un array di LetteraValore ordinato dalla lettera più probabile,
//cioè quella col valore chi-quadro più piccolo.
LetteraValore* attaccaCesare(char* stringa)
{
	//Allochiamo l'array che conterrà i risultati del test per ogni lettera e che restituiremo
	LetteraValore* valori = (LetteraValore*)malloc(NUMERO_LETTERE * sizeof(LetteraValore));
	//Allochiamo una stringa temporanea che conterrà la possibile stringa decifrata
	char* temp = (char*)malloc(strlen(stringa) * sizeof(char));
	//Per ogni possibile spostamento, calcoliamo il chi-quadro della sequenza
	for (char i = 'a'; i <= 'z'; i++)
	{
		strcpy(temp, stringa);
		//Decifriamo usando come chiave la lettera i
		for (int j = 0; j < strlen(temp); j++)
		{
			temp[j] = decodificaCarattere(temp[j], i);
		}
		//Calcoliamo il chi-quadro e lo salviamo
		valori[i - 'a'].carattere = i;
		valori[i - 'a'].valore = chiquadro(temp);
	}
	//Ordino l'array valori per la chiave valore, in ordine crescente
	insertionSort_LetteraValore(valori, 0, NUMERO_LETTERE - 1);
	return valori;
}

//Funzione che prova a decifrare testo, cifrato secondo Vigenere il cui periodo della
//chiave è lunghezza_periodo. Restituisce un array di dimensione lunghezza_periodo, ogni elemento
//del quale è un array di dimensione NUMERO_LETTERE di LetteraValore che contiene i risultati del
//test chi-quadrato per ogni lettera del periodo, ordinati dalla lettera più probabile a quella meno.
LetteraValore** attaccaVigenere(char* testo, int lunghezza_periodo)
{
	//Alloco l'array di array, che abbia tanti elementi quante lettere ci sono nella chiave
	LetteraValore** risultato = (LetteraValore**)malloc(lunghezza_periodo * sizeof(LetteraValore*));

	//Ora prendo una lettera per volta della chiave e la analizzo
	int j, k; //j è il contatore che va avanti in testo, k conta solo le lettere alfabetiche
	//Alloco e inizializzo a vuote le lunghezza_periodo sequenze
	char** sequenze = (char**)malloc(lunghezza_periodo  *sizeof(char*));
	for (j = 0; j < lunghezza_periodo; j++)
	{
		sequenze[j] = (char*)calloc((strlen(testo) / lunghezza_periodo + 2), sizeof(char));
	}
	//Concateno ogni carattere nella corretta sequenza
	for (j = 0, k = 0; j < strlen(testo); j++)
	{
		char lettera = tolower(testo[j]);
		if (isalpha(lettera))
		{
			int indice = k % lunghezza_periodo; k++; //In quale sequenza devo inserire la lettera
			strncat(sequenze[indice], testo + j, 1); //Aggiungo la lettera nella sequenza
		}
	}

	//Ora analizzo ogni sequenza, che è cifrata secondo Cesare con una sola lettera
	for (int i = 0; i < lunghezza_periodo; i++)
	{
		risultato[i] = attaccaCesare(sequenze[i]);
	}

	return risultato;
}

//Funzione che converte le lettere accentate in lettere non accentate.
char convertiLetteraAccentata(char c)
{
	if (c == 'à')
		return 'a';
	else if (c == 'è' || c == 'é')
		return 'e';
	else if (c == 'ì')
		return 'i';
	else if (c == 'ò')
		return 'o';
	else if (c == 'ù')
		return 'u';
	else
		return c;
}


/* --- FUNZIONI UTILI --- */

//Ordina un array di LetteraValore dall'indice l all'indice r in senso crescente
//rispetto alla chiave valore usando l'insertion sort.
void insertionSort_LetteraValore(LetteraValore* array, int l, int r)
{
	for (int i = l; i <= r; i++)
	{
		int j = i;
		while (j > 0 && array[j].valore < array[j-1].valore)
		{
			LetteraValore temp = array[j - 1];
			array[j - 1] = array[j];
			array[j] = temp;
			j--;
		}
	}
}

//Ordina un array di PeriodoValore dall'indice l all'indice r in senso decrescente
//rispetto alla chiave valore usando l'insertion sort.
void insertionSort_PeriodoValore(PeriodoValore* array, int l, int r)
{
	for (int i = l; i <= r; i++)
	{
		int j = i;
		while (j > 0 && array[j].valore > array[j - 1].valore)
		{
			PeriodoValore temp = array[j - 1];
			array[j - 1] = array[j];
			array[j] = temp;
			j--;
		}
	}
}

char* ReadToEnd(FILE* in)
{
	/* read chars from stream in blocks of 4096 bytes,
	dynamically allocating until eof */
	size_t bytes_read = 0;
	char * ptr = NULL;

	while (1) {
		size_t chunk_read;
		/* increase size of allocation by 4096 bytes */
		ptr = realloc(ptr, bytes_read + 4096);

		/* read up to 4096 bytes to the newest portion of allocation */
		chunk_read = fread(ptr + bytes_read, 1, 4096, in);
		bytes_read += chunk_read;

		/* if fread() got less than the full amount of characters, break */
		if (chunk_read < 4096) break;
	}

	/* resize pointer downward to actual number of bytes read,
	plus an explicit null termination */
	bytes_read += 1;
	ptr = realloc(ptr, bytes_read);
	ptr[bytes_read - 1] = '\0';

	return ptr;
}

//Implementazione dell'elevamento a potenza
float pow_mia(float base, int esponente)
{
	if (esponente == 0)
		return 1;
	else
		return (float)base * pow_mia(base, esponente - 1);
}

