#include <stdio.h>
#include "struct.h"
#include "load.h"
#include "save.h"
#include <stdbool.h>
#include <stdlib.h>
#include "addDel.h"
#include "helper.h"
#include "search.h"
#include "Ausleihen.h"
#include <string.h>

const int START_SIZE = 100;


void Choose(bool* loop, struct Book* Library[], int* amount){
    printf("\nX zum Schliessen\nS um alle Buecher zu zeigen\nF zur Buchsuche\nH zum Hinzufuegen\nL zum Loeschen\n");
    char* input = (char*) malloc(100);
    scanf("%s", input);

    //Exit
    if(input[0] == 'x'|| input[0] == 'X'){
        *loop = false;
    } //Show all Books
    else if (input[0] == 's' || input[0] == 'S'){
        for(int i = 0; (i < *amount) && (Library[i] != 0); i++){
            PrintBook(*Library[i]);
        }
    }
    else if (input[0]== 'f' || input[0] == 'F'){
        search(Library, *amount, NULL);
    }
    else if (input[0]== 'l' || input[0] == 'L'){
        delB(Library, amount);
    }
    else if (input[0]== 'h' || input[0] == 'H'){
        addB(Library, amount);
    }
    else{
        printf("Falsche Eingabe.\n");
    }

    free(input);
}

int main(){
    //List of all Books
    struct Book** Library = (struct Book**)calloc(START_SIZE, sizeof(struct Book*));
    //struct Book* Library[100] = {0};
    int amount = START_SIZE;
    load(Library, "books.txt", &amount);
    bool loop = 1;
    while(loop){
        Choose(&loop, Library, &amount);
    }
    save(Library, "books.txt", amount);
    free(Library);
    return 0;
}
