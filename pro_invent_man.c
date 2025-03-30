#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pro{
    	int id;
    	char name[30];
    	char cat[40];
    	int quan;
    	int price;
    	struct Pro *next;
 	struct Pro *prev;
}prod;

prod *head = NULL;

prod *CreateProduct(int id, char name[], char cat[], int quan, int price){
    	prod *new = (prod*)malloc(sizeof(prod));
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
	if(head == NULL || head ->id >= id){
                new -> next = head;
                if(head != NULL)head -> prev = new;
                head = new;
                return;
        }
	while(temp != NULL){
		if(temp -> id == id){
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

void deleteProduct(int id) {
    	prod *temp = head;
    	if (temp != NULL && temp -> id == id) {
    		head = temp -> next;
       		if (head != NULL) head -> prev = NULL;
       		free(temp);
        	return;
    	}
    	while (temp != NULL && temp -> id != id)
        	temp = temp -> next;
    	if (temp == NULL) {
        	printf("\nProduct ID %d not found.\n", id);
        	return;
    	}
    	if (temp -> next != NULL) temp -> next -> prev = temp -> prev;
    	if (temp -> prev != NULL) temp -> prev -> next = temp -> next;
    	free(temp);
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
    	char name[50], cat[50];
    	while (fscanf(file, "%d\t%49[^,]\t%49[^,]\t%d\t%d\n", &id, name, cat, &quan, &price) != EOF) {
    	    InsertProduct(id, name, cat, quan, price);
    	}
    	fclose(file);
    	printf("\nInventory loaded from file successfully.\n");
}

void main() {
    	int choice, id, quan, price;
    	char name[50], cat[50];
    	loadFromFile();

    	while (1) {
		printf("\n--- Inventory Management ---\n");
		printf("\t1. Add Product\n");
        	printf("\t2. Delete Product\n");
        	printf("\t3. Search Product\n");
        	printf("\t4. Display All Products\n");
        	printf("\t5. Check Low Stock\n");
        	printf("\t6. Save & Exit\n");
        	printf("\tEnter your choice: ");
        	scanf("%d", &choice);
        	switch (choice) {
        	    case 1:
                	printf("Enter ID, Name, Category, Quantity, Price: ");
                	scanf("%d", &id);
                	getchar();
                	fgets(name, sizeof(name), stdin);
                	name[strcspn(name, "\n")] = 0;
                	fgets(cat, sizeof(cat), stdin);
                	cat[strcspn(cat, "\n")] = 0;
                	scanf("%d%d", &quan, &price);
                	InsertProduct(id, name, cat, quan, price);
                	break;
		    case 2:
            	    	printf("Enter Product ID to delete: ");
                	scanf("%d", &id);
                	deleteProduct(id);
                	break;
		    case 3:
                	printf("Enter Product ID to search: ");
                	scanf("%d", &id);
                	SearchProduct(id);
                	break;
		    case 4:
                	displayProducts();
                	break;
		    case 5:
        	        printf("Enter stock threshold: ");
                	scanf("%d", &quan);
                	checkLowStock(quan);
                	break;
		    case 6:
                	saveToFile();
                	printf("Exiting program.\n");
                	exit(0);
		    default:
                	printf("Invalid choice, try again.\n");
        	}
	}
}

