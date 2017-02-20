## Function **Codifica(FILE*, FILE*, char*)**

Encode a text file given a keyword.

#### Syntax

int Codifica(FILE* in, FILE* out, char* key)

#### Arguments

_in_: input file that will be encoded.
_out_: ouput file that will contain the encoded text.
_key_: keyword that will be used to encode the text.

#### Return value

Returns 0 if successful, any other number if it encounters an error.

#### Description

This function represents the alphabet as a circular linked list (that is, the last letter, 'z', is linked to the first letter, 'a'). This function implements the Vigenere cipher in this way: each character, if letter (stressed letters are converted to non stressed), is encoded following the corresponding letter in the keyword (if it is not a letter, it is copied untouched in the output). The encoding phase is delegated to the function codificaCarattere(char, char).

#### Example

        char* text2 = "ATTACKATDAWN"; char* key2 = "LEMON";

        Codifica(fmemopen(text2, strlen(text2), "r"), stdout, key2); //LXFOPVEFRNHR

## Function **codificaCarattere(char, char)**

Encodes a letter using the Caesar cipher.

#### Syntax

char codificaCarattere(char in, char key)

#### Arguments

_in_: letter to encode.
_key_: letter of the keyword.

#### Return value

Encoded letter.

#### Description

This function accepts lower-case letters. It makes use of a circular linked list. First, it searches in the list for the letter _key_, starting from 'a', increasing a counter by 1 every letter read. In this way, we get the displacement _shift_ to add to the input letter _in_. At this point, we start again from the letter 'a' in the circular linked list until we find the letter _in_. Then, we advance _shift_ times in the list. The resulting letter is the letter encoded according to the Caesar cipher.

#### Example

        char in = 'a'; char key = 'b';

        printf("%c\n", codificaCarattere(in, key)); //b



## Function **Decodifica(FILE*, FILE*, char*)**

Decode a text file given a key.

#### Syntax

int Decodifica(FILE* in, FILE* out, char* key)

#### Arguments

_in_: input file to be decoded.
_out_: output file decoded.
_key_: keyword.

#### Return value

Returns 0 if successful, any other number if it encounters an error.

#### Description

The text is analysed character  by character. If letter (also stressed), it is decoded, otherwise it is left untouched in the output, as the function Codifica() does in the opposite direction. The decoding phase is delegated to the function decodificaCarattere().

#### Example

        char* text3 = "MEGBSMXFUQHIUUEOS"; char* key3 = "VERME";

        Decodifica(fmemopen(text3, strlen(text3), "r"), stdout, key3); //RAPPORTOIMMEDIATO











## Function **decodificaCarattere(char, char)**

Decodes a letter using the Caesar cipher.

#### Syntax

char decodificaCarattere(char in, char key)

#### Arguments

_in_: letter to be decoded.
_key_: letter of the keyword.

#### Return value

Returns the decoded letter.

#### Description

This function accepts lower-case letters. It makes use of a circular linked list. First, it searched in the list for the letter _key_, starting from 'a', increasing a counter by 1 every letter read. In this way, we get the displacement _shift_ to subtract from the input letter _in_. At this point, we start again from the letter 'a' in the circular linked list until we find the letter _in_. Then, we go back _shift_ times in the list. The resulting letter is the letter decoded according to the Caesar cipher.



## Function **inizializzaAlfabeto()**

Allocates the alphabet to memory.

#### Syntax

void inizializzaAlfabeto()

#### Description

This function loads the alphabet, that is used by other functions of the program. We use the english alphabet of 26 letters (defined in the constant NUMERO\_LETTERE). The alphabet is represented as a circular linked list of structLettera; this structure consists of the character (the letter) and a link to the following letter. The last letter, 'z', is linked to the first one, 'a'. This is a circular doubly linked list. The link to the list's head is a global variable. This function is executed once.

#### Example

        inizializzaAlfabeto();

        //Per controllare che sia corretto stampiamo l'alfabeto due volte

        for (int i = 0; i &lt; NUMERO\_LETTERE * 2; i++) {

                printf("%c", head->carattere); head = head->next;

        }

        printf("\n");

        //Ora stampiamolo al contrario due volte per controllare i link ai nodi precedenti

        for (int i = 0; i &lt; NUMERO\_LETTERE * 2; i++) {

                printf("%c", head->carattere); head = head->prev;

        }

        printf("\n");

## Function **Attacco(FILE*)**

Tries to decode a text file guessing the keyword.

#### Syntax

void Attacco(FILE* in)

#### Arguments

_in_: input file to be decoded.

#### Description

This function tries to find the keyword of a text encoded using the Vigenere cipher. The attack consists of two steps:

1. Determine the keyword length, called the period. This is done by the function trovaPeriodo().
2. Determine keyword. Once we know that the keyword length is _n_, we look for the _n_ most likely letter that might make up the keyword. This is delegated to the function attaccaVigenere().

User intervention is needed twice. At the beginning, the user is asked to specify the smallest and largest period to test. The program will then print the most likely periods, sorted from the most likely. The user is then asked to select a period. The program will then print the most likely letters for each letter of the keyword, sorted from the most likely.

#### Example

Suppose we have an input text file _in.txt_ in the same directory as the program.

Now let's encode this with keyword _manzoni_: select the option #1.


Press Enter. We are asked the keyword we wish to encode the text with. Write _manzoni_.


Press Enter. We are asked the input file's path. Write _in.txt_.


Press Enter. Now the decoded text is printed. Copy and paste it to a new text file named _out.txt_.


Now we want to test the Attacco() function: we will pretend not to know the keyword that encodes this text. Start the program again and select option #3. We are asked the input file's path. Write _out.txt_.


Press Enter. We are asked the smallest period we want to try. Remember that the Attacco() function tries all period between a minimum and a maximum and selects the most likely. For istance, write 1.


Press Enter. We now have to choose the largest period to try. For istance, write 10: we believe the keyword is under 10 characters long.


Press Enter. Now the program will calculate the probability that the keyword is 1, 2, 3, 4, 5, 6, 8, 9, 10 characters long. When done, it will print all the periods sorted from the most likely.


For example, after the analysis, the program determined that the most likely periodi s 7, followed by 3, 6 and so on. This is correct: _manzoni_ is 7 characters long. In some cases, the first and the second most likely period might be multiples (e.g. 14 and 7); in these cases, the most likely period is the smallest one. Once we determined that the keyword is 7 characters long, we need to find these 7 letters. We are now asked to choose a period, therefore we write 7 and press Enter.


Now the most likely letters that make up the keyword are printed.


For each position of the keyword, the most likely letters are printed in column sorted from the most likely. Thus, the printed results is to be read by columns: each column for each position of the keyword. The correct keyword may not be the word made up of the most likely letter for each posotion, but you should try some combinations of the 3 most likely letters for each position.

## Function **inizializzaProbabilita()**

Allocates the relative frequencies of letters for a certain language.

#### Syntax

void inizializzaProbabilita()

#### Description

This functions reads from a file the relative frequencies of every alphabet letter (26) and saves them in memory in the array prob. This probabilities are used to break the cipher, using the chi-squared test. The file must exist in the same folder as the program. Default filename is prob-it.txt, but you can change it in the code. This is the file for Italian:

0.1174

0.0092

0.0450

0.0373

0.1179

0.0095

0.0164

0.0154

0.1128

0

0

0.0651

0.0251

0.0688

0.0983

0.0305

0.0051

0.0637

0.0498

0.0562

0.0301

0.0210

0

0

0

0.0049

## Function **convertiLetteraAccentata(char*)**

Converts a stressed letter to a non stressed letter.

#### Syntax

char convertiLetteraAccentata(char* c)

#### Arguments

_c_: character (as string) to be converted

#### Return value

Returns the same letter, without the stress.

#### Description

This function returns the input, but in this cases:

| char* c | Return value |
| --- | --- |
| à | a |
| è | e |
| è | e |
| ì | i |
| ò | o |
| ù | u |



## Function **IC(char*)**

Calculates the index of coincidence of a string.

#### Syntax

float IC(char* stringa)

#### Arguments

_stringa_: the text you want to calculate the index of coincidence of.

#### Return value

Returns a real value that is the index of coincidence of the input text.

#### Description

Given a text, the index of coincidence is:

I.C.=∑i=Ai=Zfi(fi−1)N(N−1)

where fi is the number of occurrences of the letter at index _i_ in the input text, and N is the number of letters of the text.

#### Example

        char* text5 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

        printf("L'IC di questo testo e': %f\n", IC(text5)); //0.0650359

## Function **chiquadro(char*)**

Executes the chi-squared test on a string.

#### Syntax

float chiquadro(char* stringa)

#### Arguments

_stringa_: the input text.

#### Return value

Returns a real number that is the chi-squared test of the input text.

#### Description

The chi-squared test of a string is calculated with respect to the expected frequencies for a certain language saved in the global array prob, allocated with the function inizializzaProbabilia(). The used formula is the following:

![alt text](https://github.com/okh1/vigenere/blob/master/docs/chiquadro.png)

where Ci is the number of occurrences of the letter at index _i_ in the input text, while Ei is the number of expected occurrences of the letter at index _i_, that is the probability of the letter contained in the prob array times the number of letters in the text.

#### Example

        char* text6 = "The frequency of letters in text has been studied for use in cryptanalysis, and frequency analysis in particular.";

        printf("Il chi-quadrato di questo testo e': %f\n", chiquadro(text6)); //73.05 in inglese



## Function **trovaPeriodo(char*, int, int)**

Estimates the probability that a text is encoded with a keyword of certain periods.

#### Syntax

PeriodoValore* trovaPeriodo(char* text, int min, int max)

#### Arguments

_text_: input encoded text
_min_: smallest period to try.
_max_: largest period to try.

#### Return value

Returns an array of struct PeriodoValore sorted from the most likely period.

#### Description

This function calculates the probability that the text has a keyword of a certain length _i_, for _i_ ranging from _min_ to _max_ included. In order to do this, the index of coincidence is used, calculated using the function IC (). The procedure is as follows: for each period, the sequences formed by letters encoded by the same letter (according to Caesar cipher) are found. For each sequence the index of coincidence is calculated and an arithmetic average is made. The most likely periods will be those with the highest coincidence index. The values are stored in the structure structPeriodoValore, which contains an integer indicating the period and a real number indicating the average index of coincidence. The function populates an array of PeriodoValore and then sorts it through the function insertionSort\_PeriodoValore.

#### Example

        char* text8 = "ETGU RLXRGA JGM, OMTGECGX ANU JCCM XB TFKT HR N FZNAHQNVZA BBWFKFL. XM ANU YCGX XUCK FT UIPCDC PVUHCZLIXH JKKF IAI JTZRXGKF QW YAUIEVZ, RGBXUGDGJL EAF GMGME, NPU FXL MAVVPTLX VP TPNIXBIIYEAC JCJ GVGMGGU. DDK QNPP WTTVF, EIWEMSTTRNWR ANU EMIAMAI DMGX XUCE Y IHSY VYYI AIYRVB WBQ UKJ BXIPBORRXV ABTB, ZJM EG VYC PZI BH KFXKXL PZLT, OMTGECGX HREZBTW XUCK FT AEQ CDYHLIQ GEMJZL ZQECN MS OG RZAX XB CSYCWSA JZQ RTVRGI YCW GBPTCCMVNVV MC T PVHV MU LXHFP. GI PEF QEJN MLRP KFPM LR DVEPG VRUVYGVL VPKM P GIJ EZNWXV.";

        printf("Il periodo potrebbe essere %d\n", trovaPeriodo(text8, 1, 15, 0)[0].periodo); //7

## Function **attaccaCesare(char*)**

Attempts to decode a text encoded using the Caesar cipher.

#### Syntax

LetteraValore* attaccaCesare(char* stringa)

#### Arguments

_stringa_: input text encoded using the Caesar cipher.

#### Return value

Returns an array of LetteraValore sorted from the most likley letter.

#### Description

This function attempts to decrypt a string encoded according to the Caesar cipher. In order to do this, it tries all the 26 possible shifts and, for each one of them, it executes the chi-squared test through the function chiquadro(). The most likely shift is the one with the lowest chi-squared value. Each letter/shift with its own probability is stored in the structure structLetteraValore. The array of 26 LetteraValore is then sorted through the function insertionSort\_LetteraValore().

#### Example

        char* text7 = "VURZJUGRGGUGVGJQKEOAGUGKKQVWQP";

        LetteraValore* val1 = attaccaCesare(text7, 0);

        printf("La chiave secondo Cesare di questo testo piu probabile e': %c\n", val1[0].carattere); //C



## Function **attaccaVigenere(char*, int)**

Attempts to decode a text encoded using the Vigenere cipher, given the length of the keyword.

#### Syntax

LetteraValore** attaccaVigenere(char* testo, int lunghezza\_periodo)

#### Arguments

_testo_: text to be decoded.
_lunghezza\_periodo_: supposed period.

#### Return value

Returns an array of LetteraValore.

#### Description

This function determines the most likely keywords of the given length for the input text. To do this, it analyses the _lunghezza\_periodo_ sequences in the text encrypted with the same letter (that is, according to the Caesar cipher) and finds the most likely letters/shift using the function attaccaCesare(). This function returns an array of arrays of LetteraValore, i.e. a matrix of size _lunghezza\_periodo_ x _NUMERO\_LETTERE,_ where _NUMERO\_LETTERE_ is 26. That is, for every letter of the period, it returns an array of 26 possible shifts with their probability, sorted from the most likely.

#### Example

        char* text8 = "ETGU RLXRGA JGM, OMTGECGX ANU JCCM XB TFKT HR N FZNAHQNVZA BBWFKFL. XM ANU YCGX XUCK FT UIPCDC PVUHCZLIXH JKKF IAI JTZRXGKF QW YAUIEVZ, RGBXUGDGJL EAF GMGME, NPU FXL MAVVPTLX VP TPNIXBIIYEAC JCJ GVGMGGU. DDK QNPP WTTVF, EIWEMSTTRNWR ANU EMIAMAI DMGX XUCE Y IHSY VYYI AIYRVB WBQ UKJ BXIPBORRXV ABTB, ZJM EG VYC PZI BH KFXKXL PZLT, OMTGECGX HREZBTW XUCK FT AEQ CDYHLIQ GEMJZL ZQECN MS OG RZAX XB CSYCWSA JZQ RTVRGI YCW GBPTCCMVNVV MC T PVHV MU LXHFP. GI PEF QEJN MLRP KFPM LR DVEPG VRUVYGVL VPKM P GIJ EZNWXV.";

        LetteraValore** val = attaccaVigenere(text8, 7); //encrypt

        printf("La chiave piu' probabile e' %c%c%c%c%c%c%c\n", val[0][0].carattere, val[1][0].carattere, val[2][0].carattere, val[3][0].carattere, val[4][0].carattere, val[5][0].carattere, val[6][0].carattere);



## Function **insertionSort\_LetteraValore(LetteraValore*, int, int)**

Sorts an array of LetteraValore.

#### Syntax

void insertionSort\_LetteraValore(LetteraValore* array, int l, int r)

#### Arguments

_array_: array to be sorted.
_l_: left-most index.
_r_: right-most index.

#### Description

The array is sorted by the key _valore_ using Insertion Sort.

## Function **insertionSort\_PeriodoValore(PeriodoValore*, int, int)**

Sorts an array PeriodoValore.

#### Syntax

void insertionSort\_PeriodoValore(PeriodoValore* array, int l, int r)

#### Arguments

_array_: array to be sorted.
_l_: left-most index.
_r_: right-most index.

#### Description

The array is sorted by the key _valore_ using Insertion Sort.



## Function **ReadToEnd(FILE*)**

Reads a plaintext file into a string.

#### Syntax

char* ReadToEnd(FILE* in)

#### Arguments

_in_: input text file to read.

#### Return value

A string containing the complete input text.

## Function **pow\_mia(float, int)**

Exponentiation.

#### Syntax

float pow\_mia(float base, int esponente)

#### Arguments

_base_: base.
_esponente_: exponent.

#### Return value

Returns base^sponente.
