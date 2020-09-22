#include "utility.h"
#include <stdio.h>


void readBooks() {
    FILE *file;
    struct Book s;
    int n = 1;
    file = fopen("Book.bin", "ab+");
    if (file == NULL) {
        printf("Error while opening");
    } else {
        printf("All right");
    }
    int stat = fread(&s, sizeof(struct Book), 1, file);
    while (stat == 1) {
        stat = fread(&s, sizeof(struct Book), 1, file);
        printf(" %s %s %d %d ", s.name, s.author, s.BookID, s.yearOfPublishing);
        n++;
    }
    fclose(file);
}

void readReaders() {
    FILE *file;
    struct Reader s;
    int n = 1;
    file = fopen("Reader.bin", "ab+");
    if (file == NULL)
        printf("Error while opening");
    int stat = fread(&s, sizeof(struct Reader), 1, file);
    while (stat == 1) {
        stat = fread(&s, sizeof(struct Reader), 1, file);
        printf(" %d %s %s  ", s.cardNum, s.name, s.surname);
        n++;
    }
    fclose(file);
}

void writeIntoBook( Node *head, int max) {
    Node *l;
    struct Node x;
    FILE *file;
    struct Book s;
    file = fopen("Book.bin", "ab+");
    if (file == NULL)  printf("Error while opening");
    printf("enter name of book, author and year of publishing ");
    scanf("%s %s  %d", s.name, s.author, &s.yearOfPublishing);
    fwrite(&s, sizeof(s), 1, file);
    fseek(file, 0L, SEEK_END);
    int pos = ftell(file) - sizeof(struct Book);
    if (pos == -1) {
        printf("error\n");
    } else {
        s.BookID = max++;
        pushBack(head, &s);
        fclose(file);
    }
}

void writeIntoReaders(Relation *Head, Node *head, int max) {
    struct Relation z;
    FILE *file;
    struct Reader s;
    int n = 1;
    file = fopen("Reader.bin", "ab+");
    if (file == NULL)  printf("Error while opening");
    printf("enter your name, surname and BookID");
    scanf(" %s %s %d", s.name, s.surname, &s.BookID);
    fwrite(&s, sizeof(s), 1, file);
    s.cardNum = max++;
    fseek(file, 0L, SEEK_END);
    int pos = ftell(file) - sizeof(struct Reader);
    if (pos == -1) {
        printf("error\n");
    } else {
        s.cardNum = max++;
        z.cardNum = s.cardNum;
        z.BookID = s.BookID;
        pushBack(head, &s);
        pushIntoRel(Head, &z);
    }
    fclose(file);

}


