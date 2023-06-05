#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ProtoLinkedList.h"

void buy(LinkedList *list, char *name, int stock, int *status);
void suggestion(LinkedList *list, char *name);
void readFile(LinkedList *list);
void writeFile(LinkedList *list);
void validateCatalog(LinkedList *list, char *name, int *status);
void validateName(LinkedList *list, char *name, int *status);
float transaction(LinkedList *list);
void decreaseStock(LinkedList *list, char *name, int stock);
void receipt(LinkedList *list, float money, float price);
void cleanUp(LinkedList *list);
void restock(LinkedList *list, char *name, int stock);
void masterMenu(LinkedList *list);
void ownerMenu(LinkedList *list);
void buyerMenu(LinkedList *list);
void helpMenu();

// Make owner and user menus different

int main()
{
    LinkedList *list = create();

    readFile(list);

    masterMenu(list);
}

void masterMenu(LinkedList *list)
{
    time_t t;
    int selection;

    while (1)
    {
        time(&t);
        printf("Current date - %s", ctime(&t));
        printf("Select : \n1. Owner\n2. Buyer\n3. Help\n4. Exit\nSelect : ");
        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
            system("cls");
            ownerMenu(list);
            break;

        case 2:
            system("cls");
            buyerMenu(list);
            break;

        case 3:
            system("cls");

            helpMenu();

            system("pause");
            system("cls");
            break;

        case 4:
            system("cls");
            printf("Progam close!\n");
            exit(100);
            break;

        default:
            break;
        }
    }
}

void helpMenu()
{

    printf("Untuk menu owner : \n");
    printf("- Add untuk menambahkan DVD, input berupa nama, harga, dan stok awal\n- Delete untuk menghapus data DVD, input berupa nama\n- Edit untuk mengedit DVD, input berupa nama, nama baru, dan harga baru\n- Restock untuk menambahkan stok DVD, input berupa stok\n- View untuk melihat database DVD\n- Sales History untuk melihat riwayat penjualan\n");
    printf("\nUntuk menu buyer : \n");
    printf("-View DVD untuk melihat semua DVD yang ada\n- Buy DVD untuk memulai membeli DVD, input berupa nama dan jumlah\n- View Shopping Cart untuk melihat barang apa saja yang sudah dibeli, user bisa kembali ke menu sebelumnya, lanjut transaksi, atau menghapus DVD dari keranjang belanja buyer\n");
}

void ownerMenu(LinkedList *list)
{
    int selection;
    char name[256];
    float price;
    int stock;

    int status;

    time_t t;

    while (1)
    {
        time(&t);
        printf("Current date - %s", ctime(&t));
        printf("Select : \n1. Add\n2. Delete\n3. Edit\n4. Restock\n5. View\n6. Sales History\n7. Back\nSelect : ");
        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
            system("cls");

            printf("Input DVD to add : ");
            scanf(" %[^\n]s", name);

            strupr(name);

            validateName(list, name, &status);

            if (status == 1)
            {
                printf("The same DVD is already in the database!\n");
                system("pause");
                system("cls");
                break;
            }

            printf("Input price : ");
            scanf("%f", &price);

            printf("Input stock : ");
            scanf("%d", &stock);

            addList(list, name, price, stock);

            system("pause");
            system("cls");

            break;

        case 2:
            system("cls");

            printf("Input DVD to delete : ");
            scanf(" %[^\n]s", name);

            validateName(list, name, &status);

            if (status == 0)
            {
                printf("DVD name is not found on the database!\n");
                suggestion(list, name);
            }
            else
            {
                printf("DVD found!\n");
                deleteList(list, name);
            }

            system("pause");
            system("cls");
            break;

        case 3:
            system("cls");

            char nname[256];

            printf("Input DVD to edit : ");
            scanf(" %[^\n]s", name);

            validateName(list, name, &status);

            if (status == 0)
            {
                printf("DVD cannot be found!\n");
                system("pause");
                system("cls");
                break;
            }

            printf("Input new DVD name : ");
            scanf(" %[^\n]s", nname);

            printf("Input new DVD price : ");
            scanf("%f", &price);

            editList(list, name, nname, price);

            system("pause");
            system("cls");
            break;

        case 4:
            system("cls");

            int restockAmt;

            printf("Input DVD to restock : ");
            scanf(" %[^\n]s", name);

            validateName(list, name, &status);

            if (status == 0)
            {
                printf("DVD name is not found on the database!\n");
                suggestion(list, name);
            }
            else
            {
                printf("DVD found!\n");
                printf("Restock amount : ");
                scanf("%d", &restockAmt);
                restock(list, name, restockAmt);
            }

            system("pause");
            system("cls");
            break;

        case 5:
            system("cls");

            if (sizeList(list) == 0)
            {
                printf("There are no DVDs history!\n");
            }
            else
            {
                getList(list);
            }

            system("pause");
            system("cls");
            break;

        case 6:
            system("cls");

            if (sizeHist(list) == 0)
            {
                printf("There are no sales history!\n");
            }
            else
            {
                getHist(list);
            }

            system("pause");
            system("cls");
            break;

        case 7:
            system("cls");
            masterMenu(list);
            break;

        default:
            break;
        }

        writeFile(list);
    }
}

void buyerMenu(LinkedList *list)
{
    int selection;
    char name[256];
    int stock;

    int status;

    time_t t;

    while (1)
    {
        time(&t);
        printf("Current date - %s", ctime(&t));
        printf("Select : \n1. View DVD\n2. Buy DVD\n3. View Shopping Cart\n4. Back\nSelect : ");
        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
            system("cls");

            if (sizeList(list) == 0)
            {
                printf("There are no DVDs history!\n");
            }
            else
            {
                getList(list);
            }

            system("pause");
            system("cls");
            break;

        case 2:
            system("cls");

            printf("Input name : ");
            scanf(" %[^\n]s", name);

            validateCatalog(list, name, &status);

            if(status == 1) {
                printf("DVD is already in the catalog!\n");
                system("pause");
                system("cls");
                break;
            }

            validateName(list, name, &status);

            if (status == 0)
            {
                printf("DVD name is not found on the database!\n");
                suggestion(list, name);
                system("pause");
                system("cls");
                break;
            }

            printf("How many do you want to buy : ");
            scanf("%d", &stock);

            buy(list, name, stock, &status);

            if (status == 1)
            {
                printf("Added DVD into the catalog\n");
            }
            else
            {
                printf("Available stock is not enough!\n");
            }

            system("pause");
            system("cls");
            break;

        case 3:
            system("cls");

            int proceed = -1;
            float totalPrice;
            float money = 0;

            if (sizeCat(list) == 0)
            {
                printf("Catalog list is empty!\n");
                system("pause");
                system("cls");
                break;
            }

            getCat(list);

            printf("Press 0 to go back, 1 to continue, and 2 to remove catalogs : ");
            scanf("%d", &proceed);

            system("cls");

            while (proceed < 0 || proceed > 2)
            {
                if (proceed == 0)
                {
                    break;
                }
                else if (proceed == 1)
                {
                    getCat(list);
                    totalPrice = transaction(list);
                }
                else
                {
                    printf("Input name : ");
                    scanf(" %[^\n]s", name);
                    validateName(list, name, &status);

                    if (status == 0)
                    {
                        printf("DVD name is not found on the database!\n");
                        suggestion(list, name);
                        system("pause");
                        system("cls");
                        break;
                    }
                    else
                    {
                        printf("Deleted from the shopping catalog!\n");
                        deleteCat(list, name);

                        system("pause");
                        system("cls");
                        break;
                    }
                }
            }

            while (totalPrice > money)
            {
                printf("Input the money : ");
                scanf("%f", &money);
            }

            system("pause");
            system("cls");

            receipt(list, money, totalPrice);

            system("pause");

            cleanUp(list);

            system("cls");
            break;

        case 4:
            system("cls");
            masterMenu(list);
            break;

        default:
            break;
        }

        writeFile(list);
    }
}

void validateCatalog(LinkedList *list, char *name, int *status)
{
    Node *current = list->headCat;

    *status = 0;

    while (current)
    {
        Node *t = current;
        current = current->next;

        if (strcmp(strupr(t->name), strupr(name)) == 0)
        {
            *status = 1;
        }
    }
}

void validateName(LinkedList *list, char *name, int *status)
{
    Node *current = list->headList;

    *status = 0;

    while (current)
    {
        Node *t = current;
        current = current->next;

        if (strcmp(strupr(t->name), strupr(name)) == 0)
        {
            *status = 1;
        }
    }
}

void readFile(LinkedList *list)
{
    FILE *file = fopen("Database.txt", "r");

    char name[256];
    char priceChar[256];
    char stockChar[256];

    while (fscanf(file, "%s %s %s", name, priceChar, stockChar) != EOF)
    {
        float price = atof(priceChar);
        int stock = atoi(stockChar);

        int i;
#pragma omp parallel for schedule(static, 1)
        for (i = 0; i < 256; i++)
        {
            if (name[i] == 95)
            {
                name[i] = 32;
            }
        }

        addList(list, name, price, stock);
    }

    fclose(file);
}

void writeFile(LinkedList *list)
{
#pragma omp single
    {
        FILE *file = fopen("Database.txt", "w");
        Node *current = list->headList;

        while (current)
        {
            Node *t = current;
            current = current->next;
            int i;
#pragma omp parallel for schedule(static, 1)
            for (i = 0; i < 256; i++)
            {
                if (t->name[i] == 32)
                {
                    t->name[i] = 95;
                }
            }
#pragma omp task
            fprintf(file, t->name);
#pragma omp task
            fprintf(file, " ");
#pragma omp task
            fprintf(file, "%.2f", t->price);
#pragma omp task
            fprintf(file, " ");
#pragma omp task
            fprintf(file, "%d", t->stock);
#pragma omp task
            fprintf(file, "\n");

#pragma omp parallel for schedule(static, 1)
            for (i = 0; i < 256; i++)
            {
                if (t->name[i] == 95)
                {
                    t->name[i] = 32;
                }
            }
        }

        fclose(file);
    }
}

void suggestion(LinkedList *list, char *name)
{
    Node *current = list->headList;

    int status = 0;

    printf("Suggested names : \n");

    while (current)
    {
        Node *temp = current;
        current = current->next;

        printf("\e[1;36m");

        if (strstr(strupr(temp->name), strupr(name)))
        {
            status = 1;
            printf("- %s\n", temp->name);
        }
    }

    printf("\e[0m");

    if (status == 0)
    {
        printf("\e[1;31m");
        printf("There are no suggestions!\n");
        printf("\e[0m");
    }
}

void buy(LinkedList *list, char *name, int stock, int *status)
{
    Node *current = list->headList;

    while (current)
    {
        Node *temp = current;
        current = current->next;

        if (strcmp(strupr(name), strupr(temp->name)) == 0)
        {
            if (temp->stock >= stock)
            {
                *status = 1;
                addCat(list, temp->name, temp->price, stock);
            }
            else
            {
                *status = 0;
            }
        }
    }
}

float transaction(LinkedList *list)
{
    Node *current = list->headCat;

    float totalPrice = 0;

    while (current)
    {
        Node *t = current;
        current = current->next;

        addHist(list, t->name, t->price, t->stock);

        decreaseStock(list, t->name, t->stock);

        totalPrice += t->price * t->stock;
    }

    printf("Total price is : %.2f\n", totalPrice);

    return totalPrice;
}

void decreaseStock(LinkedList *list, char *name, int stock)
{
    Node *current = list->headList;

    while (current)
    {
        Node *t = current;
        current = current->next;

        if (strcmp(t->name, name) == 0)
        {
            t->stock -= stock;
            break;
        }
    }
}

void receipt(LinkedList *list, float money, float price)
{
    Node *current = list->headCat;

    time_t t;
    time(&t);

    printf("====================================\n\n");
    printf("DEF HYSTERIA DVD STORE\n%s\n", ctime(&t));
    printf("====================================\n");

    while (current)
    {
        Node *t = current;
        current = current->next;

        printf("Name   : %s\n", t->name);
        printf("Price  : %f\n", t->price);
        printf("Amount : %d\n", t->stock);
        printf("====================================\n");
    }
    printf("\nTotal  : %.2f\n", price);
    printf("Money  : %.2f\n", money);
    printf("Change : %.2f\n", money - price);
    printf("====================================\n");
}

void cleanUp(LinkedList *list)
{
    Node *current = list->headCat;

    while (current)
    {
        Node *t = current;
        current = current->next;
        deleteCat(list, t->name);
    }
}

void restock(LinkedList *list, char *name, int stock)
{
    Node *current = list->headList;

    while (current)
    {
        Node *t = current;
        current = current->next;

        if (strcmp(t->name, name) == 0)
        {
            t->stock += stock;
            break;
        }
    }
}