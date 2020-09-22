
#ifndef LAB1_UTILITY_H
#define LAB1_UTILITY_H

#include <bits/types/FILE.h>

struct Book {
    int BookID;
    char name[30];
    char author[30];
    int yearOfPublishing;

};
struct Reader {
    int cardNum;
    char name[30];
   char surname[30];
    int BookID;
};

typedef struct Node {
    int id;
    int pos;
    struct Node *next;
} Node;

typedef struct Relation {
    int cardNum;
    int BookID;
    struct Relation *next;
} Relation;

void writeIntoReaders(Relation *Head, Node *head, int max );

void writeIntoBook( Node *head, int max);

void readBooks();

void readReaders();

Node *readArr(int flag);

Node *pushBack(Node *head, Node s[]);

void get_s(int num,Node *ReaderID);

struct Reader get_m(int num,Node *ReaderID);

Relation *pushIntoRel(Relation *head, Relation s[] );

 Relation *readRelArr();

int findMaxID( Node *ID);

void del_m(Node *head, Relation *Head, int index, int flag);

void writeIDIntoFile(Node *head, int flag);

void writeIDIntoRealFile(Relation *head);
#endif //LAB1_UTILITY_H
