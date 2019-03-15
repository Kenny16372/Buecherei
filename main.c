#include <stdio.h>
#include "struct.h"
#include "load.h"
#include "main.h"
#include "save.h"
#include <stdbool.h>
#include <stdlib.h>
#include "addDel.h"

const int START_SIZE = 100;

void PrintBook(struct Book b){
    printf("Titel:  %s\n", b.title);
    printf("Author: %s\n", b.author);
    printf("ISBN:   %s\n", b.isbn);
    printf("Anzahl:  %d\n", b.count);
    printf("Last people borrowing this book:\n");
    // WIP
}

void Choose(bool* loop, struct Book* Library[], int* amount){
    printf("\nType:\nX for exit\nS for Showing all\nF for finding books\nH zum Hinzufuegen\n");
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
        //Search(Library, amount);
        addB(Library, amount, "123456", "Das magische Baumhaus", "Cornelia Funke", 3, NULL);
        delB(Library, amount, 'i', "123456");
    }
    else if (input[0]== 'l' || input[0] == 'L'){
        printf("Buch loeschen\n\n");
        // bei delb suche einbinden und nur mit index loeschen
        delB(Library, amount, 'i', "123456");
    }
    else if (input[0]== 'h' || input[0] == 'H'){
        char isbn[15];
        char title[50];
        char author[30];
        int count;
        // ganze zeile einscannen sonst wird nur ein wort genommen
        printf("Buch hinzufuegen\n\nISBN: ");
        scanf("%s", isbn);
        printf("Titel: ");
        scanf("%s", title);
        printf("Autor: ");
        scanf("%s", author);
        printf("Anzahl an Buechern: ");
        scanf("%d", &count);
        addB(Library, amount, isbn, title, author, count, NULL);
    }
    else{
        printf("Wrong input detected\n");
    }

    free(input);
}

int main(){
    //List of all Books
    struct Book** Library = (struct Book**)calloc(START_SIZE, sizeof(struct Book));
    //struct Book* Library[100] = {0};
    int amount = START_SIZE;
    load(Library, "books.txt", &amount);
    bool loop = 1;
    while(loop){
        Choose(&loop, Library, &amount);
    }
    printf("%d", amount);
    save(Library, "dat.txt", amount);
    free(Library);
    return 0;
}
