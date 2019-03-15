#include "struct.h"
#include "addDel.h"
#include "search.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


void addB(struct Book* lib[], int* amount, char* isbn, char* title, char* author, int count, char* owners[]){
    struct Book* b = (struct Book*)malloc(sizeof(struct Book));
    if(strlen(isbn) < sizeof(b->isbn))
        strcpy(b->isbn, isbn);
    else {
    memcpy(b->isbn, isbn, sizeof(b->isbn) - 1);
    b->isbn[sizeof(b->isbn)] = 0;
    printf("Die ISBN ist zu lang: Nur %s wurde gespeichert.\n", b->isbn);
    }
    if(strlen(title) <= sizeof(b->title))
    strcpy(b->title, title);
    else {
    memcpy(b->title, title, sizeof(b->title) - 1);
    b->title[sizeof(b->title)] = 0;
    printf("Der Titel ist zu lang: Nur %s wurde gespeichert.\n", b->title);
    }
    if(strlen(author) <= sizeof(b->author))
        strcpy(b->author, author);
    else {
    memcpy(b->author, author, sizeof(b->author) - 1);
    b->author[sizeof(b->author)] = 0;
    printf("Der Autor ist zu lang: Nur %s wurde gespeichert.\n", b->author);
    }
    b->count = count;
    lib[(*amount)++] = b;
}

void delB(struct Book* lib[], int* amount){
    struct Book* b;
    search(lib, *amount, &b);
    if(b){
        // Gebe das geloeschte Buch frei
        free(b);
        // Suche den Platz des geloeschten Buches und verschiebe das letzte Buch dort hin
        for(int i = 0; i < *amount; i++){
            if(lib[i] == b){
                lib[i] = lib[--(*amount)];
                lib[*amount] = 0;
            }
        }
        printf("Loeschen erfolgreich.\n");
    }
    else{
        printf("Fehler beim Loeschen. Haben Sie alle Daten richtig eingegeben?\n");
    }
}