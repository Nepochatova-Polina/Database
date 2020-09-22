#include <stdio.h>
#include "stdlib.h"
#include "utility.h"


int main() {
    Node *BookID, *ReaderID;
    Relation *RelID;
    int firstID, secondID;
    BookID = readArr(1);
    ReaderID = readArr(2);
    RelID = readRelArr();

    firstID = findMaxID(BookID);
    secondID = findMaxID(ReaderID);

    writeIntoReaders(RelID, ReaderID, firstID);
    secondID++;
    writeIntoBook(BookID, secondID);
    firstID++;

    writeIDIntoFile(BookID, 1);
    writeIDIntoFile(ReaderID, 2);
     writeIDIntoRealFile(RelID);
    return 0;
}


Node *readArr(int flag) {
    Node *head = NULL;
    FILE *file;
    int pos;

    switch (flag) {
        case 1:
            file = fopen("BookArr.bin", "ab+");
            fseek(file, 0L, SEEK_END);
            pos = ftell(file) / sizeof(struct Node);
            break;
        case 2:
            file = fopen("ReaderArr.bin", "ab+");
            fseek(file, 0L, SEEK_END);
            pos = ftell(file) / sizeof(struct Node);
            break;
        default:
            printf("wrong type!");
            break;
    }
    Node s[pos];
    if (file == NULL)
        printf("Error while opening");
    fread(&s, sizeof(struct Node), pos, file);
    head = pushBack(head, s);
    fclose(file);
    return head;
}

//запись ID в файл
void writeIDIntoFile(Node *head, int flag) {
    FILE *file;
    switch (flag) {
        case 1:
            file = fopen("BookArr.bin", "wb+");
            break;
        case 2:
            file = fopen("ReaderArr.bin", "wb+");
            break;
        default:
            printf("wrong type!");
            break;
    }
    while (head != NULL) {
        scanf("%d %d", &head->id, &head->pos);
        head = head->next;
    }
    fclose(file);
}

Relation *readRelArr() {
    int pos;
    Relation *head = NULL;
    FILE *file;
    file = fopen("Realation.bin", "ab+");
    if (file == NULL)
        printf("Error while opening");
    fseek(file, 0L, SEEK_END);
    pos = ftell(file) / sizeof(struct Relation);
    Relation s[pos];
    fread(&s, sizeof(struct Relation), pos, file);
    fclose(file);
    head = pushIntoRel(head, s);
    return head;
}


void writeIDIntoRealFile(Relation *head) {
    FILE *file;
    file = fopen("RelationArr.bin", "wb+");
        while (head != NULL) {
        scanf("%d %d", &head->BookID, &head->cardNum);
        head = head->next;
    }
    fclose(file);
}

Node *pushBack(Node *head, Node s[]) {
    Node *last;
    int maxNum = 0;
    if (head == NULL) {
        last = NULL;
    } else {
        while (head->next != NULL) {
            head = head->next;
        }
        last = head;
    }
    for (int i = 0; i < sizeof(struct Node); i++) {
        Node *tmp = (Node *) malloc(sizeof(struct Node));
        tmp->id = s[i].id;
        tmp->pos = s[i].pos;
        tmp->next = NULL;
        if (last == NULL) {
            break;
        } else {
            last->next = tmp;
        }
    }
    return last;
}

Relation *pushIntoRel(Relation *head, Relation s[]) {
    Relation *last;
    int maxNum = 0;
    if (head == NULL) {
        last = NULL;
    } else {
        while (head->next != NULL) {
            head = head->next;
        }
        last = head;
    }
    for (int i = 0; i < sizeof(struct Relation); i++) {
        Relation *temp = (Relation *) malloc(sizeof(struct Relation));
        temp->BookID = s[i].BookID;
        temp->cardNum = s[i].cardNum;
        temp->next = NULL;
        if (last == NULL) {
            break;
        } else {
            last->next = temp;
        }
    }
    return last;
}


int findMaxID(Node *ID) {
    int max = 0;
    if (ID == NULL)
        return 0;
    while (ID->next != NULL) {
        if (ID->id > max) {
            max = ID->id;
        }
        ID = ID->next;
    }
    return max;
}

