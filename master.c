#include "utility.h"
#include "stdlib.h"
#include <stdio.h>

struct Reader get_m(int num, Node *ReaderID) {
    struct Reader x;
    FILE *file;
    while (ReaderID->id != num) {
        ReaderID = ReaderID->next;
    }
    file = fopen("Reader.bin", "ab+");
    if (file == NULL)  printf("Error while opening");
    fseek(file, ReaderID->pos, SEEK_END);
    fread(&x, sizeof(struct Reader), 1, file);
    printf("%d %s %s %d", x.cardNum, x.name, x.surname, x.BookID);
    fclose(file);
    return x;
}

void get_s(int num, Node *ReaderID) {
    FILE *file;
    struct Book l;
    struct Reader x = get_m(num, ReaderID);

    while (ReaderID->id != x.BookID) {
        ReaderID = ReaderID->next;
    }
    file = fopen("Book.bin", "ab+");
    if (file == NULL)  printf("Error while opening");
    fread(&l, sizeof(struct Book), 1, file);
    printf("%s %s %d", l.name, l.author, l.yearOfPublishing);

}

void del_m(Node *head, Relation *Head, int index, int flag) {
    Node *last;
    Relation *Last;
    switch (flag) {
//        delete from Book file
        case 1:
            while (head->id != index) {
                last = head;
                head = head->next;
            }
            last->next = head->next;
//            delete from Reader
        case 2:;
            while (head->id != index) {
                last = head;
                head = head->next;
            }
            last->next = head->next;

            while (Head != NULL) {
                if (Head->cardNum != index) {
                    Last = Head;
                    Head = Head->next;
                }
                Last->next = Head->next;
            }
    }

}


void updateReader(Node *s, int num, Relation *l) {
    FILE *file;
    struct Reader x;
    int i = 0;
    while (i < num) {
        s = s->next;
        i++;
    }
    file = fopen("Reader.bin", "ab+");
    if (file == NULL)  printf("Error while opening");
    fseek(file, sizeof(struct Reader), SEEK_SET);
    fread(&s, sizeof(struct Reader), 1, file);
    printf(" Old information\n ");
    printf(" %s %s %d", x.surname, x.name, x.BookID);
    i = x.BookID;
    printf(" Enter new information : ");
    scanf(" %s %s %d ", x.surname, x.name, &x.BookID);
    if(l->cardNum == x.cardNum && l->BookID == i){
        l->BookID = x.BookID;
    }else{
        l = l->next;
    }
    fseek(file, sizeof(struct Reader), SEEK_SET);
    fwrite(&x, sizeof(struct Reader), 1, file);

}

void updateBook(Node *s, int num) {
    FILE *file;
    struct Book x;
    int i = 0;
    while (i < num) {
        s = s->next;
        i++;
    }
    file = fopen("Reader.bin", "ab+");
    if (file == NULL)  printf("Error while opening");
    fseek(file, sizeof(struct Reader), SEEK_SET);
    fread(&s, sizeof(struct Reader), 1, file);
    printf(" Old information\n ");
    printf(" %s %s %d", x.name, x.author, x.yearOfPublishing);
    i = x.BookID;
    printf(" Enter new information : ");
    scanf(" %s %s %d ",x.name, x.author, &x.yearOfPublishing);
    fseek(file, sizeof(struct Book), SEEK_SET);
    fwrite(&x, sizeof(struct Book), 1, file);

}
