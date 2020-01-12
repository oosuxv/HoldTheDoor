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

void mergeSort(Sale *sales, int start, int end);

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
        sales[i].day = i % 31 + 1; // potential impossible dates
        sales[i].month = i % 12 + 1;
        sales[i].year = i + 2000;
    }
}

void readSale(Sale *s) {
    printf("-----New record-----\n");
    printf("Enter the name: ");
    scanf("%s", &s->name);
    printf("Enter the day: ");
    scanf("%d", &s->day);               //validation needed?
    printf("Enter the month: ");
    scanf("%d", &s->month);             //validation needed?
    printf("Enter the year: ");
    scanf("%d", &s->year);
    printf("Enter the price: ");
    scanf("%f", &s->price);             //validation needed?
    printf("Enter the quantity: ");
    scanf("%d", &s->quantity);          //validation needed?
}

void merge(Sale *sales, int start, int middle, int end) {
    int sizeL = middle - start + 1;
    int sizeR = end - middle;

    Sale *left = malloc(sizeL * sizeof(Sale));
    Sale *right = malloc(sizeR * sizeof(Sale));
    for (int i = 0; i < sizeL; i++) {
        left[i] = sales[start + i];
    }
    for (int j = 0; j < sizeR; j++) {
        right[j] = sales[middle + 1 + j];
    }

    int posL = 0,  posR = 0, posOrigin = start;
    while (posL < sizeL && posR < sizeR) {
        if (left[posL].month <= right[posR].month) {
            sales[posOrigin] = left[posL];
            posL++;
        } else {
            sales[posOrigin] = right[posR];
            posR++;
        }
        posOrigin++;
    }
    while (posL < sizeL) {
        sales[posOrigin] = left[posL];
        posL++;
        posOrigin++;
    }
    while (posR < sizeR) {
        sales[posOrigin] = right[posR];
        posR++;
        posOrigin++;
    }
    free(left);
    free(right);
}

void mergeSort(Sale *sales, int start, int end) {
    if (start < end) {
        int middle = start + (end - start) / 2;
        mergeSort(sales, start, middle);
        mergeSort(sales, middle + 1, end);
        merge(sales, start, middle, end);
    }
}
