#include "utility.h"
#include <stdio.h>



Node *writeIntoBook(Node *head, int max) {
    Node *l;
    FILE *file;
    struct Book s;
    file = fopen("Book.bin", "ab+");
    if (file == NULL) {
        printf("Error while opening");
    } else {
        printf("enter name of book, author and year of publishing ");
        scanf("%s %s  %d", s.name, s.author, &s.yearOfPublishing);
        s.BookID = ++max;
        fwrite(&s, sizeof(s), 1, file);
        fseek(file, 0L, SEEK_END);
        int pos = ftell(file) - sizeof(struct Book);
        if (pos == -1) {
            printf("error\n");
        } else {
            head = pushBack(head, s.BookID, pos);
            fclose(file);
        }
    }
    return head;
}


void readBookByList(Node *head) {
    FILE *file;
    struct Book s;
    file = fopen("Book.bin", "ab+");
    if (file == NULL) {
        printf("Error while opening");
    } else {
        while (head != NULL) {
            fseek(file, head->pos, SEEK_SET);
            fread(&s, sizeof(struct Book), 1, file);
            printf(" %d %s %s %d ", s.BookID, s.name, s.author, s.yearOfPublishing);
            printf("\n");
            head = head->next;
            printf("\n");

        }

    }
    fclose(file);
}


void readReaderByList(Node *head) {
    FILE *file;
    struct Reader s;
    file = fopen("Reader.bin", "ab+");
    if (file == NULL) {
        printf("Error while opening");
    } else {
        while (head != NULL) {
            fseek(file, head->pos, SEEK_SET);
            fread(&s, sizeof(struct Reader), 1, file);
            printf(" %d %s %s %d ", s.cardNum, s.name, s.surname, s.BookID);
            printf("\n");
            head = head->next;
        }

    }
    fclose(file);
}



