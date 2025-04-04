#ifndef PRO_INVENT_MAN_HEADER_H
#define PRO_INVENT_MAN_HEADER_H

typedef struct Pro{
    int id;
    char name[30];
    char cat[40];
    int quan;
    int price;
    struct Pro *next;
    struct Pro *prev;
}prod;

extern prod *head;

prod *CreateProduct(int id, char name[], char cat[], int quan, int price);
void InsertProduct(int id, char name[], char cat[], int quan, int price);
void deleteProduct(int id, char name[]);
void Rectify(int id, char name[]);
void SearchProduct(int id);
void displayProducts();
void checkLowStock(int threshold);
void saveToFile();
void loadFromFile();

#endif
