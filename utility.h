
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

struct Reader writeIntoReaders(Relation *Head, Node *head, int max);
Node *writeIntoBook(Node *head, int max);


Node * delFromBook(Node *head);
Node * delFromReader(Node *head, Relation *Head);
void get_s(Node *ReaderID);
struct Reader get_m( Node *ReaderID, int num);


Node *readArr(int flag);
Relation *readRelArr();
Relation *pushIntoRel(Relation *head, int cardNum, int BookID);
Node *pushBack(Node *head, int id, int pos);

void updateBook(Node *s);
void updateReader(Node *s);

int findMaxID(Node *ID);


void writeIDIntoFile(Node *head, int flag);
void writeIDIntoRealFile(Relation *head);
void readBookByList(Node *head);
void readReaderByList(Node *head);


Relation *writeFileIntoRelList(const int arr[], int size);
Node *writeFileIntoList(const int arr[], int size);
Node *addelem(Node *lst, Node *s);
Relation *addToRel(Relation *lst, Relation *s);
void write(struct Node * head);
void writeRel(struct Relation * head);

#endif //LAB1_UTILITY_H
