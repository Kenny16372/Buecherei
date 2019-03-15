#include "helper.h"
#include "struct.h"
#include <stdio.h>


void PrintBook(struct Book b){
    printf("Titel:  %s\n", b.title);
    printf("Author: %s\n", b.author);
    printf("ISBN:   %s\n", b.isbn);
    printf("Anzahl:  %d\n", b.count);
    printf("Last people borrowing this book:\n");
    // WIP
}

void flush(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}