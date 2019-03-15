#include <stdio.h>
#include "struct.h"
#include "load.h"
#include "main.h"
#include "save.h"
#include <stdbool.h>
#include <stdlib.h>
#include "addDel.h"
#include "helper.h"
#include "search.h"
#include <string.h>

const int START_SIZE = 100;


void Choose(bool* loop, struct Book* Library[], int* amount){
    printf("\nType:\nX for exit\nS for Showing all\nF for finding books\nH zum Hinzufuegen\nL zum Loeschen\n");
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
        size_t bufsize = 200;
        char* isbn = (char*)malloc(bufsize);        
        char* title = (char*)malloc(bufsize);
        char* author = (char*)malloc(bufsize);
        int count;
        flush();
        printf("Buch hinzufuegen\n\nISBN: ");
        getline(&isbn, &bufsize, stdin);
        isbn = strtok(isbn, "\n");
        printf("Titel: ");
        getline(&title, &bufsize, stdin);
        title = strtok(title, "\n");
        printf("Autor: ");
        getline(&author, &bufsize, stdin);
        author = strtok(author, "\n");
        printf("Anzahl an Buechern: ");
        printf("%s %s %s", isbn, title, author);
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
