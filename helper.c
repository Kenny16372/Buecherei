#include "helper.h"
#include "struct.h"
#include <stdio.h>
#include <windows.h>


// Gibt ein Buch in der Konsole aus
void PrintBook(struct Book b){
    printf("Titel:  %s\n", b.title);
    printf("Author: %s\n", b.author);
    printf("ISBN:   %s\n", b.isbn);
    printf("Anzahl:  %d\n", b.count);
    printf("Besitzer:\n");
    for(int i = 0; i < b.numOwners; i++){
        printf("\t%d. %s\n", i + 1, b.owners[i]);
    }
	printf("\n\n");
}

// Flusht stdin
void flush(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Loescht den Inhalt der Konsole(Windows-spezifisch)
void clear ()
{
  DWORD n;                         /* Number of characters written */
  DWORD size;                      /* number of visible characters */
  COORD coord = {0};               /* Top left screen position */
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  /* Get a handle to the console */
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

  GetConsoleScreenBufferInfo ( h, &csbi );

  /* Find the number of characters to overwrite */
  size = csbi.dwSize.X * csbi.dwSize.Y;

  /* Overwrite the screen buffer with whitespace */
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );

  /* Reset the cursor to the top left position */
  SetConsoleCursorPosition ( h, coord );
}