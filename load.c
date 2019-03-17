#include "struct.h"
#include "load.h"
#include "helper.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int INCR_PERC = 10;

// Laedt das Array aus der Textdatei am uebergebenen Ort
struct Book** load(struct Book* lib[], const char* path, int* amount){
  // Oeffnet die Datei
  FILE* file = fopen(path, "rt");
  if(file != NULL){
    // Durchlaeuft die Datei Zeile fuer Zeile
    char line [200];
    for(int i = 0; fgets(line, 200, file); i++){
      // Prueft, ob eine Vergroesserung des Arrays noetig ist
      if(i >= *amount){
        // Vergroessert das Array um (INCR_PERC)%
        int inc = (*amount * INCR_PERC) / 100;
        // Stellt eine stete Vergroesserung sicher
        if(inc < 1) inc = 1;
        // Vergroessert das Array
        struct Book** l = (struct Book**)calloc(*amount + inc, sizeof(struct Book*));
        memcpy(l, lib, (*amount) * sizeof(struct Book*));
        free(lib);
        lib = l;
        if(lib == NULL){
          printf("Speicherplatz nicht ausreichend.\n");
          break;
        }
        *amount += inc;
      }
      // Erzeugt ein neues Buch
      struct Book* b = (struct Book*)malloc(sizeof(struct Book));
      // Fuellt das Buch aus der Datei, die Zeilen enthaelt im folgenden Format(geschweifte Klammern bedeuten optional,
      // * Wiederholung(vorangestellt)):
      //[ISBN]-[Titel]-[Autor]-[Anzahl]{-[Ausleiher_1]*{/[Ausleiher_n]}}
      char* split = strtok(line, "\n");
  		split = strtok(split, "-");
      if(strlen(split) < sizeof(b->isbn))
  		  strcpy(b->isbn, split);
      else {
        memcpy(b->isbn, split, sizeof(b->isbn) - 1);
        b->isbn[sizeof(b->isbn)] = 0;
        printf("Die ISBN ist zu lang: Nur %s wurde gespeichert.\n", b->isbn);
      }
  		split = strtok(NULL, "-");
      if(strlen(split) <= sizeof(b->title))
        strcpy(b->title, split);
      else {
        memcpy(b->title, split, sizeof(b->title) - 1);
        b->title[sizeof(b->title)] = 0;
        printf("Der Titel ist zu lang: Nur %s wurde gespeichert.\n", b->title);
      }
  		split = strtok(NULL, "-");
      if(strlen(split) <= sizeof(b->author))
  		  strcpy(b->author, split);
      else {
        memcpy(b->author, split, sizeof(b->author) - 1);
        b->author[sizeof(b->author)] = 0;
        printf("Der Autor ist zu lang: Nur %s wurde gespeichert.\n", b->author);
      }
  		split = strtok(NULL, "-");
  		b->count = atoi(split);
      split = strtok(NULL, "-");
      b->owners = (char**)calloc(1,1);
      b->numOwners = 0; // wird fuer jeden Ausleiher inkrementiert
      for(int k = 1; (split = strtok(k==1?split:NULL, "/")); k++){
        b->owners = realloc(b->owners, k * sizeof(char*));
        b->owners[k - 1] = (char*)malloc(strlen(split) + 1);
        strcpy(b->owners[k - 1], split);
        b->numOwners++;
      }
      lib[i] = b;
    }
    fclose(file);
    // Berechnung von amount
    for(int i = 0; i < *amount; i++){
      if(lib[i] == 0){
        *amount = i;
        break;
      }
    }
  }
  else{
    printf("Keine Datei mit dem Namen %s gefunden.", path);
    *amount = 0;
  }
  return lib;
}
