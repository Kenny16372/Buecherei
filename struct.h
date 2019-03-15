#ifndef STRUCT_H
#define STRUCT_H


struct Book{
    char isbn[15];
    char title[50];
    char author[30];
    int count;
    char** owners;
};

#endif // STRUCT_H
