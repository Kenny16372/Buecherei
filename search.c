#include "search.h"
#include "helper.h"
#include "struct.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const int NUM_OF_RESULTS = 10;

// Buchsuche; gibt Anzahl an Treffern zurueck
int search(struct Book* lib[], int amount, struct Book** selVal){
    struct Book* res[NUM_OF_RESULTS];
    for(int i = 0; i < NUM_OF_RESULTS; i++){
        res[i] = (struct Book*)calloc(1, sizeof(struct Book*));
    }
    int resNum = 0;
    char type;
    char value[100];
    // Abfrage des Suchbegriffs
    printf("Suche nach ISBN(I), Titel(T) oder Autor(A)? ");
    flush();
    scanf("%c", &type);
    if(!(type == 'i' || type == 'I' || type == 'a' || type == 'A' || type == 't' || type == 'T'))
        return 0;
    printf("Suchbegriff: ");
    flush();
    scanf("%s", value);
    flush();
    // Gehe ueber das Array und speichere die Buecher, die dem Suchkriterium entsprechen
    switch(type){
        case 'i': case 'I':
        for(int i = 0; i < amount; i++){
            if(strstr(lib[i]->isbn, value)){
                if(resNum < NUM_OF_RESULTS){
                    res[resNum] = lib[i];
                    resNum++;
                }
                else{
                    printf("Es werden die ersten %d Ergebnisse angezeigt. Bitte grenzen Sie Ihre Suche weiter\nein, um weitere Treffer zu erhalten.\n", NUM_OF_RESULTS);
                    break;     
                }
            }
        }
        break;
        case 't': case 'T':
        for(int i = 0; i < amount; i++){
            if(strstr(lib[i]->title, value)){
                if(resNum < NUM_OF_RESULTS){
                    res[resNum] = lib[i];
                    resNum++;
                }
                else{
                    printf("Es werden die ersten %d Ergebnisse angezeigt. Bitte grenzen Sie Ihre Suche weiter\nein, um weitere Treffer zu erhalten.\n", NUM_OF_RESULTS);
                    break;
                }
            }
        }
        break;
        case 'a': case 'A':
        for(int i = 0; i < amount; i++){
            if(strstr(lib[i]->author, value)){
                if(resNum < NUM_OF_RESULTS){
                    res[resNum] = lib[i];
                    resNum++;
                }
                else{
                    printf("Es werden die ersten %d Ergebnisse angezeigt. Bitte grenzen Sie Ihre Suche weiter\nein, um weitere Treffer zu erhalten.\n", NUM_OF_RESULTS);
                    break;
                }
            }
        }
        break;
        default:
        printf("Falsche Eingabe.\n");
		flush();
        break;
    }
    // Ende der Suche, falls kein Trffer
    if(resNum == 0){
        printf("Kein Treffer.\n");
		selVal = NULL;
        return resNum;
    }
    if(selVal){
        // Falls ein einziges Buch gefordert ist, speichere dieses in selVal
        *selVal = select(res, resNum);
    }
    else{
        // Sonst gebe die Treffer aus
        for(int i = 0; i < resNum; i++){
            printf("Treffer %d von %d:\n", i + 1, resNum);
            PrintBook(*res[i]);
            printf("\n");
        }
    }
    free(res);
	return resNum;
}

// Laesst den Benutzer ein Buch aus einer Liste auswaehlen
struct Book* select(struct Book* res[], int resNum){
	if (resNum < 1) {
		printf("Keine Buecher gefunden\n");
		return NULL;
	}
	else if (resNum == 1) return res[0];
	while (1) {
		int sel;
		printf("Treffer:\n\n");
		for (int i = 0; i < resNum; i++) {
			printf("Buch %d\n", i + 1);
			PrintBook(*res[i]);
			printf("\n\n");
		}
		printf("Bitte geben Sie die Nummer des gewuenschten Buches ein: ");
		if (0 == scanf("%d", &sel)) {
			flush();
			printf("Falsche Eingabe.\n");
			continue;
		}
		if (sel < 1 || sel > resNum) {
			printf("Falsche Eingabe.\n");
			continue;
		}
		return res[sel - 1];
	}
}