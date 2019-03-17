#include "struct.h"
#include "addDel.h"
#include "search.h"
#include "helper.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h> 

//  Erstellt ein neues Buch, welches am Ende des Arrays gespeichert wird
void addB(struct Book* lib[], int* amount){
    // Fragt die Infos ueber das Buch ab
    struct Book* b = (struct Book*)malloc(sizeof(struct Book));
    size_t INPUT_BUF_SIZE = 200;
    char* isbn = (char*)malloc(INPUT_BUF_SIZE);       // Man koennte auch die Strings auf ihre Ziellaenge begrenzen, verliert     
    char* title = (char*)malloc(INPUT_BUF_SIZE);      // dadurch aber Informationen ueber den Userinput, die moeglicherweise 
    char* author = (char*)malloc(INPUT_BUF_SIZE);     // spaeter verarbeitet werden koennten (in einer spaeteren Version)
    int count;
    printf("Buch hinzufuegen\n\nISBN: ");
    flush();
    getline(&isbn, &INPUT_BUF_SIZE, stdin);
    isbn = strtok(isbn, "\n");
    printf("Titel: ");
    getline(&title, &INPUT_BUF_SIZE, stdin);
    title = strtok(title, "\n");
    printf("Autor: ");
    getline(&author, &INPUT_BUF_SIZE, stdin);
    author = strtok(author, "\n");
    printf("Anzahl an Buechern: ");
    scanf("%d", &count);
    // Kopiert die Infos in der richtigen Laenge in die struct Book
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
    b->numOwners = 0;
    b->owners = (char**)malloc(1);
    lib[(*amount)++] = b;
    free(isbn);
    free(title);
    free(author);
}

// Loescht ein Buch aus dem Array und verschiebt das letzte Buch an die Stelle des Geloeschten
void delB(struct Book* lib[], int* amount){
    // Waehlt das zu loeschende Buch aus
    struct Book* b;
    search(lib, *amount, &b);
    if(b){
        // Gebe das geloeschte Buch frei
        for(int i = 0; i < b->numOwners; i++){
            free(b->owners[i]);
        }
        free(b->owners);
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