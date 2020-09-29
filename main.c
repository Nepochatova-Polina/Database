#include <stdio.h>
#include "stdlib.h"
#include "utility.h"


int main() {
    int s, num;;
    Node *BookID = NULL, *ReaderID = NULL;
    Relation *RelID = NULL;
    int firstID, secondID;
    BookID = readArr(1);
    ReaderID = readArr(2);
    RelID = readRelArr();
    firstID = findMaxID(BookID);
    secondID = findMaxID(ReaderID);

    printf("1 - Add to Books\n"
           "2 - Add to Readers\n"
           "3 - Update book\n"
           "4 - Update reader\n"
           "5 - Read information about Book\n"
           "6 - Read information about Reader\n"
           "7 - Delete from Book\n"
           "8- Delete from Reader\n"
    );

    scanf("%d", &s);
    switch (s) {
        case 1:
            while (firstID < 3) {
                BookID = writeIntoBook(BookID, firstID);
                firstID++;
            }
            readBookByList(BookID);
            break;
        case 2:
            while (secondID < 3) {
                FILE *file;
                struct Reader x;
                file = fopen("Reader.bin", "ab+");
                if (file == NULL) {
                    printf("Error while opening");
                } else {
                    printf("enter your name, surname and BookID");
                    scanf(" %s %s %d", x.name, x.surname, &x.BookID);
                    x.cardNum = ++secondID;
                    fwrite(&x, sizeof(struct Reader), 1, file);
                    fseek(file, 0L, SEEK_END);
                    int pos = ftell(file) - sizeof(struct Reader);
                    if (pos == -1) {
                        printf("error\n");
                    } else {
                        ReaderID = pushBack(ReaderID, x.cardNum, pos);
                        RelID = pushIntoRel(RelID, x.cardNum, x.BookID);
                    }
                    fclose(file);
                }
            }
            readReaderByList(ReaderID);
            break;
        case 3:
            updateBook(BookID);
            readBookByList(BookID);
            break;
        case 4:
            updateReader(ReaderID);
            readReaderByList(ReaderID);
            break;
        case 5:
            get_s(ReaderID);
            break;
        case 6:
            printf("Enter number of recording\n");
            scanf("%d", &num);
            get_m(ReaderID, num);
            break;
        case 7:
            BookID = delFromBook(BookID);
            readBookByList(BookID);
            break;
        case 8:
            ReaderID = delFromReader(ReaderID, RelID);
            readReaderByList(ReaderID);
            break;
        default:
            printf("Wrong type!!!");
            break;
    }


    writeIDIntoFile(BookID, 1);
    writeIDIntoFile(ReaderID, 2);
    writeIDIntoRealFile(RelID);

    return 0;
}


Node *readArr(int flag) {
    Node *head = NULL;
    FILE *file;
    int pos, id;
    switch (flag) {
        case 1:
            file = fopen("BookArr.bin", "ab+");
            if (file == NULL) {
                printf("Error while opening");
                return NULL;
            }
            break;
        case 2:
            file = fopen("ReaderArr.bin", "ab+");
            if (file == NULL) {
                printf("Error while opening");
                return NULL;
            }
            break;
        default:
            printf("wrong type!");
            return NULL;
    }
    fseek(file, 0L, SEEK_END);
    int size = ftell(file) / sizeof(int);
    int arr[size];
    fseek(file, 0L, SEEK_SET);
    fread(&arr, sizeof(int), size, file);
    head = writeFileIntoList(arr, size);
    fclose(file);
    return head;
}
Relation *readRelArr() {
    int cardNum, BookID;
    Relation *head = NULL;
    FILE *file;
    file = fopen("Relation.bin", "ab+");
    if (file == NULL) {
        return NULL;
    }
    fseek(file, 0L, SEEK_END);
    int size = ftell(file) / sizeof(int);
    int arr[size];
    fseek(file, 0L, SEEK_SET);
    fread(&arr, sizeof(int), size, file);
    head = writeFileIntoRelList(arr, size);

    fclose(file);
    return head;
}
void writeIDIntoFile(Node *head, int flag) {
    FILE *file;
    switch (flag) {
        case 1:
            file = fopen("BookArr.bin", "wb");
            break;
        case 2:
            file = fopen("ReaderArr.bin", "wb");
            break;
        default:
            printf("wrong type!");
            break;
    }
    if (file == NULL) printf("Error while opening");
    fseek(file, 0L, SEEK_SET);

    while (head != NULL) {
        fwrite(&head->id, sizeof(int), 1, file);
        fwrite(&head->pos, sizeof(int), 1, file);
        head = head->next;

    }
    fclose(file);
}
void writeIDIntoRealFile(Relation *head) {
    FILE *file;
    file = fopen("Relation.bin", "wb");
    if (file == NULL) printf("Error while opening");
    while (head != NULL) {
        fwrite(&head->cardNum, sizeof(int), 1, file);
        fwrite(&head->BookID, sizeof(int), 1, file);
        head = head->next;
    }
    fclose(file);
}
Node *pushBack(Node *head, int id, int pos) {
    struct Node *temp = (struct Node *) malloc(sizeof(struct Node));
    temp->id = id;
    temp->pos = pos;
    temp->next = NULL;
    struct Node *p = head;
    if (p == NULL) {
        p = temp;
        head = temp;
    } else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}                            /*Записывают элемент в конец листа*/
Relation *pushIntoRel(Relation *head, int cardNum, int BookID) {
    Relation *temp = (Relation *) malloc(sizeof(Relation));
    temp->cardNum = cardNum;
    temp->BookID = BookID;
    temp->next = NULL;
    Relation *p = head;
    if (p == NULL) {
        p = temp;
        head = temp;
    } else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}
int findMaxID(Node *ID) {
    int max = 0;
    if (ID == NULL)
        return 0;
    while (ID != NULL) {
        if (ID->id > max) {
            max = ID->id;
        }
        ID = ID->next;
    }
    return max;
}
Node *writeFileIntoList(const int arr[], int size) {
    Node *head = NULL;
    int i = 0;
    while (i < size) {
        Node *lst;
        lst = (Node *) malloc(sizeof(Node));
        lst->id = arr[i];
        i++;
        lst->pos = arr[i];
        lst->next = NULL;
        i++;
        head = addelem(head, lst);
    }
    return head;
}
Relation *writeFileIntoRelList(const int arr[], int size) {
    Relation *head = NULL;
    int i = 0;
    while (i < size) {
        Relation *lst;
        lst = (Relation *) malloc(sizeof(Relation));
        lst->cardNum = arr[i];
        i++;
        lst->BookID = arr[i];
        lst->next = NULL;
        i++;
        head = addToRel(head, lst);
    }
    return head;
}
Node *addelem(Node *head, Node *s) {
    Node *temp = (struct Node *) malloc(sizeof(struct Node));
    temp = s;
    Node *p = head;
    if (p == NULL) {
        p = temp;
        head = temp;
    } else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
    return head;

}
Relation *addToRel(Relation *head, Relation *s) {
    Relation *temp = (Relation *) malloc(sizeof(Relation));
    temp = s;
    Relation *p = head;
    if (p == NULL) {
        p = temp;
        head = temp;
    } else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}
void write(struct Node *head) {
    while (head != NULL) {
        printf("%d %d\n", head->id, head->pos);
        head = head->next;
    }
}
void writeRel(struct Relation *head) {
    while (head != NULL) {
        printf("%d %d\n", head->cardNum, head->BookID);
        head = head->next;
    }
}
