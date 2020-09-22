#include "utility.h"
#include <stdio.h>


void readBooks() {
    FILE *file;
    struct Book s;
    file = fopen("Book.bin", "ab+");
    if (file == NULL) {
        printf("Error while opening");
    } else {
        while (!feof(file)) {
            fread(&s, sizeof(struct Book), 1, file);
            printf(" %d %s %s %d ", s.BookID, s.name, s.author, s.yearOfPublishing);
        }
    }
    fclose(file);
}

void readReaders() {
    FILE *file;
    struct Reader s;

    file = fopen("Reader.bin", "ab+");
    if (file == NULL) {
        printf("Error while opening");
    } else {
        while (!feof(file)) {
            fread(&s, sizeof(struct Reader), 1, file);
            printf(" %d %s %s %d ", s.cardNum, s.name, s.surname, s.BookID);
        }
    }
    fclose(file);
}

void writeIntoBook(Node *head, int max) {
    Node *l;
    struct Node x;
    FILE *file;
    struct Book s;
    file = fopen("Book.bin", "ab+");
    if (file == NULL) {
        printf("Error while opening");
    } else {
        printf("enter name of book, author and year of publishing ");
        scanf("%s %s  %d", s.name, s.author, &s.yearOfPublishing);
        s.BookID = max++;
        fwrite(&s, sizeof(s), 1, file);
        fseek(file, 0L, SEEK_END);
        int pos = ftell(file) - sizeof(struct Book);
        if (pos == -1) {
            printf("error\n");
        } else {
            pushBack(head, &s);
            fclose(file);
        }
    }
}

void writeIntoReaders(Relation *Head, Node *head, int max) {
    Relation z;
    FILE *file;
    struct Reader s;
        file = fopen("Reader.bin", "ab+");
    if (file == NULL) {
        printf("Error while opening");
    } else {
        printf("enter your name, surname and BookID");
        scanf(" %s %s %d", s.name, s.surname, &s.BookID);
        s.cardNum = max++;
        fwrite(&s, sizeof(s), 1, file);
        fseek(file, 0L, SEEK_END);
        int pos = ftell(file) - sizeof(struct Reader);
        if (pos == -1) {
            printf("error\n");
        } else {
            z.cardNum = s.cardNum;
            z.BookID = s.BookID;
            pushBack(head, &s);
            pushIntoRel(Head, &z);
        }
        fclose(file);
    }
}




