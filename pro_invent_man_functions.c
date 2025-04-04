#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pro_invent_man_header.h"


prod *head = NULL;

prod *CreateProduct(int id, char name[], char cat[], int quan, int price){
    	prod *new = (prod*)malloc(sizeof(struct Pro));
    	new -> id = id;
    	strcpy(new -> name, name);
    	strcpy(new -> cat, cat);
    	new -> quan = quan;
    	new -> price = price;
    	new -> next = NULL;
    	new -> prev = NULL;
}

void InsertProduct(int id, char name[], char cat[], int quan, int price){
	prod *temp = head;
	prod *new = CreateProduct(id, name, cat, quan, price);
	if(head == NULL)
	{
		new -> next = head;
                if(head != NULL)head -> prev = new;
                head = new;
                return;
        }
	while(temp != NULL){
		if(temp -> id == id && strcmp(temp -> name, name) == 0){
			temp -> quan = (temp -> quan) + quan;
			if(temp -> price != price){
				temp -> price = price;
			}
			return;
		}
		temp = temp -> next;
	}
	prod *current = head;
    	while(current -> next != NULL && current -> next -> id < id)current = current -> next;
    	new -> next = current -> next;
    	if(current -> next != NULL)current -> next -> prev = new;
    	current -> next = new;
    	new -> prev = current;
}

void deleteProduct(int id, char name[]){
        prod *temp = head;
        if (temp != NULL && temp -> id == id && strcmp(temp -> name, name) == 0){
                head = temp -> next;
                if (head != NULL) head -> prev = NULL;
                free(temp);
                return;
        }
	while(temp != NULL){
		if (temp->id == id && strcmp(temp->name, name) == 0) {
            		if (temp->prev != NULL)
                		temp->prev->next = temp->next;
            		if (temp->next != NULL)
		                temp->next->prev = temp->prev;
            		free(temp);
            		printf("\nProduct with ID %d and name '%s' deleted successfully.\n", id, name);
            		return;
        	}
        	temp = temp->next;
	}
	printf("\nProduct ID %d not found.\n", id);
}
	/*
        while (temp != NULL && temp -> id != id && strcmp(temp -> name, name) != 0)
                temp = temp -> next;
        if (temp == NULL) {
                printf("\nProduct ID %d not found.\n", id);
                return;
        }
        if (temp -> next != NULL) temp -> next -> prev = temp -> prev;
        if (temp -> prev != NULL) temp -> prev -> next = temp -> next;
        free(temp);
	*/

void Rectify(int id, char name[]){
	int Id, quan, price;
	char Name[30], cat[40];
	if(head == NULL){
		printf("\nEmpty File\n");
		return;
	}
	prod *temp = head;
	while(temp != NULL){
		if(temp -> id == id && strcmp(temp -> name, name) == 0){
			printf("%d\t%s\t%s\t%d\t$%d\n", temp -> id, temp -> name, temp -> cat, temp -> quan, temp -> price);
			deleteProduct(id,name);
			printf("Enter ID, Name, Category, Quantity, Price: ");
                        scanf("%d",&Id);
                        getchar();
                        fgets(Name, sizeof(Name), stdin);
                        Name[strcspn(Name, "\n")] = 0;
                        fgets(cat, sizeof(cat), stdin);
                        cat[strcspn(cat, "\n")] = 0;
                        scanf("%d%d", &quan, &price);
			printf("\nProduct updated sucessfully\n");
			InsertProduct(Id,Name,cat,quan,price);
			return;
		}
		temp = temp -> next;
	}
	printf("\nProduct not found\n");
}

			

void SearchProduct(int id) {
    	prod *temp = head;
    	while (temp != NULL){
	        if (temp -> id == id){
	            printf("%d\t%s\t%s\t%d\t$%d\n", temp -> id, temp -> name, temp -> cat, temp -> quan, temp -> price);
	            return;
        	}
        	temp = temp -> next;
    	}
    	printf("\nProduct with ID %d not found.\n", id);
}

void displayProducts() {
    	prod *temp = head;
    	if (temp == NULL) {
        	printf("\nNo products in inventory.\n");
        	return;
    	}
    
    	printf("\n--- Inventory List ---\n");
    	while (temp != NULL) {
        	printf("%d\t%s\t%s\t%d\t$%d\n",temp -> id, temp -> name, temp -> cat, temp -> quan, temp -> price);
        	temp = temp -> next;
    	}
}

void checkLowStock(int threshold) {
    	prod *temp = head;
    	int found = 0;
    	printf("\n--- Low Stock Alerts (Below %d) ---\n", threshold);
    	while (temp != NULL) {
    	    if (temp -> quan < threshold) {
        	    printf("%d\t%s\t%d\n", temp -> id, temp -> name, temp -> quan);
        	    found = 1;
        	}
        	temp = temp -> next;
    	}
    	if (!found) printf("No low stock alerts.\n");
}

void saveToFile(){
    	FILE *file = fopen("inventory.txt", "w");
    	if (file == NULL) {
    	    printf("\nError saving to file.\n");
    	    return;
    	}
    	prod* temp = head;
    	while (temp != NULL) {
    	    fprintf(file, "%d\t%s\t%s\t%d\t%d\n", temp -> id, temp -> name, temp -> cat, temp -> quan, temp -> price);
    	    temp = temp->next;
    	}    
    	fclose(file);
    	printf("\nInventory saved to file successfully.\n");
}

void loadFromFile(){
	FILE *file = fopen("inventory.txt", "r");
    	if (file == NULL) {
        	printf("\nNo previous inventory found.\n");
        	return;
    	}
    	int id, quan, price;
    	char name[30], cat[40];
    	while (fscanf(file, "%d\t%49[^\t]\t%49[^\t]\t%d\t%d\n", &id, name, cat, &quan, &price) != EOF) {
		InsertProduct(id, name, cat, quan, price);
    	}
    	fclose(file);
    	printf("\nInventory loaded from file successfully.\n");
}


