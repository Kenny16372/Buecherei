#include "search.h"
#include "struct.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "helper.h"


const int NUM_OF_RESULTS = 10;

void search(struct Book* lib[], int amount, struct Book** selVal){
    struct Book* res[NUM_OF_RESULTS];
    for(int i = 0; i < NUM_OF_RESULTS; i++){
        res[i] = (struct Book*)calloc(1, sizeof(struct Book*));
    }
    int resNum = 0;
    char type;
    char value[100];
    printf("Suche nach ISBN(I), Titel(T) oder Autor(A)? ");
    flush();
    scanf("%c", &type);
    printf("Suchbegriff: ");
    flush();
    scanf("%s", value);
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
        break;
    }
    if(selVal){
        *selVal = select(res, resNum);
    }
    else{
        for(int i = 0; i < resNum; i++){
            printf("Treffer %d von %d:\n", i + 1, resNum);
            PrintBook(*res[i]);
            printf("\n");
        }
    }
    free(res);
}

struct Book* select(struct Book* res[], int resNum){
    int sel;
    printf("Treffer:\n\n");
    for(int i = 0; i < resNum; i++){
        printf("Buch %d\n", i + 1);
        PrintBook(*res[i]);
        printf("\n\n");
    }
    printf("Bitte geben Sie die Nummer des gewuenschten Buches ein: ");
    flush();
    scanf("%d", &sel);
    return res[sel - 1];
}