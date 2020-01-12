#include <stdio.h>
#include <stdlib.h>

#define READ_DATA_FROM_USER 0

typedef struct Sales {
    char name[20];
    float price;
    unsigned int quantity;
    int day;
    int month;
    int year;
} Sale;

void printSale(Sale *s) {
    printf("Name: %s; Date: %02d-%02d-%04d; Price: %6.2f; Quantity: %3d\n",
           s->name, s->day, s->month, s->year, s->price, s->quantity);
}

void readSale(Sale *s);

void generateSales(Sale *sales, int size);

void mergeSort(Sale *sales, int left, int right);

int main() {
    int size;
    printf("Welcome to the database with dynamic size.\n");
    printf("Please enter the size of database:");
    scanf("%d", &size);
    Sale *sales = malloc(size * sizeof(Sale));

    if (READ_DATA_FROM_USER) {
        printf("Please enter %d sale records for printout\n", size);
        for (int i = 0; i < size; i++) {
            readSale(&sales[i]);
        }
    } else {
        generateSales(sales, size);

    }
    mergeSort(sales, 0, size - 1);
    for (int i = 0; i < size; i++) {
        printSale(&sales[i]);
    }
    free(sales);

    return 0;
}

void generateSales(Sale *sales, int size) {
    for (int i = 0; i < size; i++) {
        sprintf(sales[i].name, "name %3d", i);
        sales[i].price = i + 1;
        sales[i].quantity = i + 1;
        sales[i].day = i % 31 + 1;
        sales[i].month = i % 12 + 1;
        sales[i].year = i + 2000;
    }
}

void readSale(Sale *s) {
    printf("-----New record-----\n");
    printf("Enter the name: ");
    scanf("%s", &s->name);
    printf("Enter the day: ");
    scanf("%d", &s->day);
    printf("Enter the month: ");
    scanf("%d", &s->month);
    printf("Enter the year: ");
    scanf("%d", &s->year);
    printf("Enter the price: ");
    scanf("%f", &s->price);
    printf("Enter the quantity: ");
    scanf("%d", &s->quantity);
}

void merge(Sale *sales, int left, int middle, int right) {
    int sizeL = middle - left + 1;
    int sizeR = right - middle;

    Sale *Left = malloc(sizeL * sizeof(Sale));
    Sale *Right = malloc(sizeR * sizeof(Sale));
    for (int i = 0; i < sizeL; i++) {
        Left[i] = sales[left + i];
    }
    for (int j = 0; j < sizeR; j++) {
        Right[j] = sales[middle + 1 + j];
    }

    int posL = 0,  posR = 0, positionOriginal = left;
    while (posL < sizeL && posR < sizeR) {
        if (Left[posL].month <= Right[posR].month) {
            sales[positionOriginal] = Left[posL];
            posL++;
        } else {
            sales[positionOriginal] = Right[posR];
            posR++;
        }
        positionOriginal++;
    }
    while (posL < sizeL) {
        sales[positionOriginal] = Left[posL];
        posL++;
        positionOriginal++;
    }
    while (posR < sizeR) {
        sales[positionOriginal] = Right[posR];
        posR++;
        positionOriginal++;
    }
    free(Left);
    free(Right);
}

void mergeSort(Sale *sales, int left, int right) {
    if (left < right) {
        int m = left + (right - left) / 2;
        mergeSort(sales, left, m);
        mergeSort(sales, m + 1, right);
        merge(sales, left, m, right);
    }
}
