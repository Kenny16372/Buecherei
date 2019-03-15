#include <stdio.h>
#include "struct.h"
#include <stdlib.h>
#include <string.h>
#include "load.h"

const int INCR_PERC = 10;

void load(struct Book* lib[], const char* path, int* amount){
  FILE* file = fopen(path, "rt");
  if(file != NULL){
    char line [200];
    fgets(line, 200, file);
    for(int i = 0; fgets(line, 200, file); i++){
      if(i >= *amount){
        int inc = (*amount * INCR_PERC) / 100;
        if(inc < 1) inc = 1;
        lib = (struct Book**)realloc(lib, *amount + inc);
        for(int j = *amount; j < *amount + inc; j++){
          lib[j] = 0;
        }
        if(lib == NULL){
          printf("Speicherplatz nicht ausreichend.\n");
          break;
        }
      }
      struct Book* b = (struct Book*)malloc(sizeof(struct Book));
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
      lib[i] = b;
    }
    fclose(file);
    // Berechnung von amount
    for(int i = 0; i < *amount; i++){
      if(lib[i] == 0){
        *amount = i - 1;
        break;
      }
    }
  }
  else
    printf("Keine Datei mit dem Namen %s gefunden.", path);
}
