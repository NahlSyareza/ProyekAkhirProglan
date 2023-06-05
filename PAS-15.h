#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
    char name[256];
    float price;
    int stock;
} Node;

typedef struct
{
    Node *headList;
    Node *tailList;
    int sizeList;

    Node *headHist;
    Node *tailHist;
    int sizeHist;

    Node *headCat;
    Node *tailCat;
    int sizeCat;
} LinkedList;

LinkedList *create()
{
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list != NULL)
    {
        printf("Succesfully created Linked List\n");
        list->headList = NULL;
        list->tailList = NULL;

        list->headHist = NULL;
        list->tailHist = NULL;

        list->headCat = NULL;
        list->tailCat = NULL;

        list->sizeList = 0;
        list->sizeHist = 0;
        list->sizeCat = 0;
    }
    else
    {
        printf("Failed to create Linked List\n");
    }

    return list;
}

int sizeList(LinkedList *list)
{
    return list->sizeList;
}

int sizeHist(LinkedList *list)
{
    return list->sizeHist;
}

int sizeCat(LinkedList *list)
{
    return list->sizeCat;
}

void addList(LinkedList *list, char name[], float price, int stock)
{
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    strcpy(node->name, name);
    node->price = price;
    node->stock = stock;

    if (sizeList(list) == 0)
    {
        list->headList = node;
        list->tailList = list->headList;
    }
    else
    {
        list->tailList->next = node;
        Node *t = list->tailList;
        list->tailList = list->tailList->next;
        list->tailList->prev = t;
    }

    list->sizeList++;
}

void editList(LinkedList *list, char oldName[], char newName[], float price)
{
    Node *current = list->headList;

    while (current)
    {
        Node *temp = current;
        current = current->next;

        if (strcmp(strupr(temp->name), strupr(oldName)) == 0)
        {
            strupr(newName);
            strcpy(temp->name, newName);
            temp->price = price;
            break;
        }
    }
}

void deleteList(LinkedList *list, char name[])
{
#pragma omp critical
    {
        if (sizeList(list) == 1)
        {
            if (strcmp(list->headList->name, name) == 0)
            {
                list->headList = NULL;
                list->tailList = NULL;
                free(list->headList);
                free(list->tailList);
            }
        }
        else
        {
            if (strcmp(list->headList->name, name) == 0)
            {
                list->headList = list->headList->next;
                list->headList->prev = NULL;
                free(list->headList->prev);
            }
            else if (strcmp(list->tailList->name, name) == 0)
            {
                list->tailList = list->tailList->prev;
                list->tailList->next = NULL;
                free(list->tailList->next);
            }
            else
            {
                Node *current = list->headList;

                while (current)
                {
                    Node *t = current;
                    current = current->next;

                    if (strcmp(strupr(t->name), strupr(name)) == 0)
                    {
                        t->prev->next = t->next;
                        t->next->prev = t->prev;
                        t = NULL;
                        free(t);
                        break;
                    }
                }
            }
        }

        list->sizeList--;
    }
}

void getList(LinkedList *list)
{
#pragma omp single
    {
        Node *current = list->headList;

        printf("====================================\n");

        while (current)
        {
            Node *t = current;
            current = current->next;

            printf("Name is   : %s\n", t->name);
            printf("Price is  : %.2f\n", t->price);
            printf("Stock is  : %d\n", t->stock);
            printf("====================================\n");
        }
    }
}

void addCat(LinkedList *list, char name[], float price, int stock)
{
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    strcpy(node->name, name);
    node->price = price;
    node->stock = stock;

    if (sizeCat(list) == 0)
    {
        list->headCat = node;
        list->tailCat = list->headCat;
    }
    else
    {
        list->tailCat->next = node;
        Node *t = list->tailCat;
        list->tailCat = list->tailCat->next;
        list->tailCat->prev = t;
    }

    list->sizeCat++;
}

void deleteCat(LinkedList *list, char name[])
{
#pragma omp critical
    {
        if (sizeCat(list) == 1)
        {
            if (strcmp(list->headCat->name, name) == 0)
            {
                list->headCat = NULL;
                list->tailCat = NULL;
                free(list->headCat);
                free(list->tailCat);
            }
        }
        else
        {
            if (strcmp(list->headCat->name, name) == 0)
            {
                list->headCat = list->headCat->next;
                list->headCat->prev = NULL;
                free(list->headCat->prev);
            }
            else if (strcmp(list->tailCat->name, name) == 0)
            {
                list->tailCat = list->tailCat->prev;
                list->tailCat->next = NULL;
                free(list->tailCat->next);
            }
            else
            {
                Node *current = list->headCat;

                while (current)
                {
                    Node *t = current;
                    current = current->next;

                    if (strcmp(strupr(t->name), strupr(name)) == 0)
                    {
                        t->prev->next = t->next;
                        t->next->prev = t->prev;
                        t = NULL;
                        free(t);
                        break;
                    }
                }
            }
        }

        list->sizeCat--;
    }
}

void getCat(LinkedList *list)
{
#pragma omp single
    {
        Node *current = list->headCat;

        printf("====================================\n");

        while (current)
        {
            Node *t = current;
            current = current->next;

            printf("Name is    : %s\n", t->name);
            printf("Price is   : %f\n", t->price);
            printf("Amount is  : %d\n", t->stock);
            printf("====================================\n");
        }
    }
}

void addHist(LinkedList *list, char name[], float price, int stock)
{
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    strcpy(node->name, name);
    node->price = price;
    node->stock = stock;

    if (sizeHist(list) == 0)
    {
        list->headHist = node;
        list->tailHist = list->headHist;
    }
    else
    {
        list->tailHist->next = node;
        Node *t = list->tailHist;
        list->tailHist = list->tailHist->next;
        list->tailHist->prev = t;
    }

    list->sizeHist++;
}

void getHist(LinkedList *list)
{
#pragma omp single
    {
        Node *current = list->headHist;

        printf("====================================\n");
        printf("SALES HISTORY\n");
        printf("====================================\n");

        float totalPrice = 0;

        while (current)
        {
            Node *temp = current;
            current = current->next;
            totalPrice += (temp->price * temp->stock);
            printf("Name is    : %s\n", temp->name);
            printf("Price is   : %.2f\n", temp->price);
            printf("Amount is  : %d\n", temp->stock);
            printf("====================================\n");
        }
        printf("Total sold item price : %.2f\n", totalPrice);
        printf("====================================\n");
    }
}