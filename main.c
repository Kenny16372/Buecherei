#include "struct.h"
#include "load.h"
#include "save.h"
#include "addDel.h"
#include "helper.h"
#include "search.h"
#include "borrow.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const int START_SIZE = 10;





// Das Menue; setzt loop bei Programmende auf false
void Choose(bool* loop, struct Book* Library[], int* amount){
    clear(); 
    // Gibt die Optionen aus
    printf("X zum Schliessen\nS um alle Buecher zu zeigen\nF zur Buchsuche\nH zum Hinzufuegen\nL zum Loeschen\nA zum Ausleihen\nZ zum Zurueckgeben\n");
    // Liest die gewuenschte Option ein
    char* input = (char*) malloc(100);
    scanf("%s", input);
    // Programmende
    if(input[0] == 'x'|| input[0] == 'X'){
        *loop = false;
    } 
    // Gibt alle Buecher aus
    else if (input[0] == 's' || input[0] == 'S'){
        clear();   
        for(int i = 0; (i < *amount) && (Library[i] != 0); i++){
            PrintBook(*Library[i]);
        }
        flush();
    }
    // Buchsuche
    else if (input[0]== 'f' || input[0] == 'F'){
        clear();
        search(Library, *amount, NULL);
    }
    // Loeschen von Buechern
    else if (input[0]== 'l' || input[0] == 'L'){
        clear();
        delB(Library, amount);
    }
    // Hizufuegen von Buechern
    else if (input[0]== 'h' || input[0] == 'H'){
        clear();
        addB(Library, amount);
	}
    // Ausleihen
	else if (input[0] == 'a' || input[0] == 'A') {
        clear();
		struct Book * b;
		if (0 < search(Library, *amount, &b)) {
			Borrow(b);
		}
	}
    // Zurueckgeben
	else if (input[0] == 'z' || input[0] == 'Z') {
        clear();
		struct Book * b;
		if (0 < search(Library, *amount, &b)) {
			HandBack(b);
		}
	}
	else{
        printf("Falsche Eingabe.\n");
    }
    if(*loop){
        printf("Druecken Sie Enter zum Fortfahren.");
        getchar();
    }
    clear();
    free(input);
}

int main(){
    struct Book** Library = (struct Book**)calloc(START_SIZE, sizeof(struct Book*));
    int amount = START_SIZE;
    // Laden des Arrays
    Library = load(Library, "books.txt", &amount);
    // Hauptloop
    bool loop = 1;
    while(loop){
        Choose(&loop, Library, &amount);
    }
    // Speichern des Arrays
    save(Library, "books.txt", amount);
    free(Library);
    return 0;
}
