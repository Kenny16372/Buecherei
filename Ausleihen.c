#include "Ausleihen.h"
#include "helper.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void Borrow(struct Book * b) {

	if (b->numOwners >= b->count) {
		printf("All Books borrowed");
		return;
	}

	char * prename = (char *) malloc(sizeof(char)*60);
	char surname[20];
	bool loop = true;
	while (loop) {
		printf("\nVorname: ");
		flush();
		scanf("%s", prename);
		flush();
		printf("\nNachname: ");
		scanf("%s", surname);
		flush();
		char key[20];
		printf("Ist dies Ihr Name?\n\t %s %s\nY fuer ja.\n", prename, surname);
		scanf("%s", key);
		if (key[0] == 'Y' || key[0] == 'y') 
			loop = false;
		flush();
	}
	
	char ** owner =(char **) malloc(sizeof(char) * 60 * b->count);
	for (int i = 0; i < b->numOwners; i++) {
		owner[i] = b->owners[i];
		free(b->owners[i]);
	}

	strcat(prename, " ");
	strcat(prename, surname);
	owner[b->numOwners] = prename;
	b->numOwners += 1;
	free(b->owners);
	b->owners = owner;
	printf("\n\n");
	return;
}

void HandBack(struct Book * b) {

	if (b->numOwners < 1) {
		printf("Dieses Buch wurde nicht ausgeliehen.\n\n");
		return;
	}

	printf("Dieses Buch hat ausgeliehen:\n");

	for (int i = 0; i < b->numOwners; i++) {
		printf("\t%d. %s\n", i + 1, b->owners[i]);
	}

	int choice = -1;
	while (1) {

		printf("\nBitte geben Sie die Position Ihres Namens ein: ");
		flush();
		if (0 == scanf("%d", &choice)) {
			printf("Falsche Eingabe.\n");
			flush();
			continue;
		}
		if (choice > b->numOwners || choice < 1) {
			printf("Falsche Eingabe.\n");
			continue;
		}
		break;
	}
	int u = 0;
	char ** owner = (char **)malloc(sizeof(char) * 60 * b->count);
	for (int i = 0; i < b->numOwners; i++) {
		if (i == (choice - 1)) u = 1;
		owner[i - u] = b->owners[i];
		free(b->owners[i]);
	}
	b->numOwners -= 1;
	free(b->owners);
	b->owners = owner;
	return;
}