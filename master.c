#include "utility.h"
#include <stdio.h>

struct Reader get_m(Node *ReaderID, int num) {
    struct Reader x;
    FILE *file;
    if (ReaderID == NULL) {
        printf("File is empty");
    } else {
        file = fopen("Reader.bin", "ab+");
        if (file == NULL) {
            printf("Error while opening");
        } else {
            while (ReaderID->id != num) {
                ReaderID = ReaderID->next;
            }
            fseek(file, ReaderID->pos, SEEK_SET);
            fread(&x, sizeof(struct Reader), 1, file);
            printf("%d %s %s %d", x.cardNum, x.name, x.surname, x.BookID);
            printf("\n");
            fclose(file);
            return x;
        }
    }
}

void get_s(Node *ReaderID) {
    int num;
    printf("Enter number of recording\n");
    scanf("%d", &num);
    FILE *file;
    struct Book s;
    struct Reader x = get_m(ReaderID, num);
    while (ReaderID->id != x.BookID) {
        ReaderID = ReaderID->next;
    }
    file = fopen("Book.bin", "ab+");
    fread(&s, sizeof(struct Book), 1, file);
    printf("%d %s %s %d", s.BookID, s.name, s.author, s.yearOfPublishing);
    printf("\n");

}

Node *delFromBook(Node *head) {
    int index;
    int i = 0;
    printf("Enter number of recording\n");
    scanf("%d", &index);
    Node *last;
    Relation *Last;
    if (head == NULL) {
        printf("Your database is empty");
    } else {
        while (i < index) {
            if (head == NULL) {
                printf("There are no book with such ID number\n");
                break;
            } else {

                last = head;
                head = head->next;
                i++;
            }
        }
        last->next = head->next;
    }
    return head;
}

Node *delFromReader(Node *head, Relation *Head) {
    int index;
    printf("Enter number of recording\n");
    scanf("%d", &index);
    Node *last;
    Relation *Last;
    if (head == NULL) {
        printf("Your database is empty");
    } else {
        while (head->id != index) {
            last = head;
            head = head->next;
        }
        last->next = head->next;

        while (Head != NULL) {
            if (Head->cardNum != index) {
                Last = Head;
                Head = Head->next;
            } else {
                Last->next = Head->next;
                Head = Head->next;
            }
        }
    }
    return head;
}

void updateReader(Node *s) {
    int num;
    printf("Enter number of recording\n");
    scanf("%d", &num);
    FILE *file;
    struct Reader x;
    while (s->id < num) {
        s = s->next;
    }
    file = fopen("Reader.bin", "rb+");
    if (file == NULL) printf("Error while opening");
    fseek(file, s->pos, SEEK_SET);
    fread(&x, sizeof(struct Reader), 1, file);
    printf(" Old information\n ");
    printf(" %d %s %s %d",x.cardNum, x.name, x.surname, x.BookID);
    printf("\n");
    printf(" Enter new information : ");
    scanf("%s %s %d", x.name, x.surname, &(x.BookID));
    fseek(file, s->pos, SEEK_SET);
    fwrite(&x, sizeof(struct Reader), 1, file);
    fclose(file);
}


void updateBook(Node *s) {
    int num;
    printf("Enter number of recording\n");
    scanf("%d", &num);
    FILE *file;
    struct Book x;
    int i = 0;
    if (s == NULL) {
        printf("Your database is empty");
    } else {
        while (s->id < num) {
            s = s->next;
        }
        file = fopen("Book.bin", "rb+");
        if (file == NULL) printf("Error while opening");
        fseek(file, s->pos, SEEK_SET);
        fread(&x, sizeof(struct Book), 1, file);
        printf(" Old information\n ");
        printf(" %s %s %d", x.name, x.author, x.yearOfPublishing);
        printf("\n");
        printf(" Enter new data about name, author and yead of publishing : ");
        scanf("%s %s %d", x.name, x.author, &x.yearOfPublishing);
        fseek(file, s->pos, SEEK_SET);
        fwrite(&x, sizeof(struct Book), 1, file);
        fclose(file);
    }
}

