#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define DATABASE "book.txt"

char *PreName[] = {"Tmofej", "Luta", "Smiljana", "Jefrossinja","Wratimir","Porfirij","Praskowja","Swenislawa","Baerjan","Norbo","Mikola","Uljana","Swenislaw","Swetosar", "Beloslawa"}; // 15
char *AfterName[] = {"Neswitajlo", "Dappersjen", "Neswitajlo", "Dragan","Ossipko","Meleschko","Pritula","Sidorko","Kaltofen","Firnske","Mikola","Tschumak","Tereschko","Wassilko", "Machno"}; //15
char *Adjektiv[] = {"Ehrlicher", "Wahnsinniger", "Lieblicher", "Attraktiver", "Verfuehrerischer", "Seltener", "Rarer", "Intriganter", "Verlogener", "Malerischer", "Abenteuerlicher", "Atemberaubender","Edler"}; // 13 Elemente
char *Nomen[] = {"Wein", "Held", "Verraeter", "Moerder", "Barde", "Affront", "Aspekt", "Teufel", "Henker", "Wissenschaflter", "Koenig", "Fund", "Ausblick", "Erlebnispark", "Ausblick", "Herr"}; //16
char *Nachsatz[] = {"der Aufrichtigkeit", "des verolenen Verstandes", "des suessen Geschmackes", "der Unwiederstehlichkeit", "der Betoerungen", "der hoechsten Kostbarkeit", "der Giftmischerei", "der Unaufrichtigkeit", "der Transzendens", "der Erregung", "des Luft holens","der Armut", "der Haeufigkeit"}; // 13
char dash = '-';

int main(){

	time_t t;

	FILE *database = fopen(DATABASE, "w");
	char ISBN[15] = {};
	char Author[50] = {};
	char Title[50] = {};
	int count = 6;
	srand((unsigned) time(&t));
	for(int i =0; i<50; i++){

	for(int i = 0; i < 14; i++){ISBN[i] =(char) (48 + rand() % 10);}

	strcat(Author, PreName[rand() % 15]); 
	strcat(Author, " "); 
	strcat(Author, AfterName[rand() % 15]); 

	strcat(Title, Adjektiv[rand() % 13]);
	strcat(Title, " ");
	strcat(Title, Nomen[rand() % 16]);
	strcat(Title, " ");
	strcat(Title, Nachsatz[rand() % 13]);
	fprintf(database, "%s-%s-%s-%d-%s/%s\n", ISBN, Title, Author, count, PreName[rand() % 15], PreName[rand() % 15]);
	printf("%s", ISBN);
	printf("%c", dash);
	printf("%s", Author);
	printf("%c", dash);
	printf("%s", Title);
	printf("%c", dash);
	printf("%d\n", count);
	Title[0] = '\0';
	Author[0] = '\0';
	}


	return 0;

}
