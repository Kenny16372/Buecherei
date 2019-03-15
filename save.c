#include <stdio.h>
#include "struct.h"
#include <stdlib.h>
#include "save.h"


void save(struct Book* lib[], const char* path, int amount) {
	FILE* file = fopen(path, "wt");
	for(int i = 0; (i < amount) && (lib[i] != 0); i++){
		struct Book b = *lib[i];
		fprintf(file, "%s-%s-%s-%d", b.isbn, b.title, b.author, b.count);
		if(b.numOwners > 0)
			fprintf(file, "-%s", b.owners[0]);
        for(int i = 1; i < b.numOwners; i++){
			fprintf(file, "/%s", b.owners[i]);
		}

        fprintf(file, "\n");
        free(lib[i]);
	}
	fclose(file);
}