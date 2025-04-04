#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pro_invent_man_header.h"

void main() {
    	int choice, id, quan, price;
    	char name[30], cat[40];
    	loadFromFile();

    	while (1) {
		printf("\n--- Inventory Management ---\n");
		printf("\t1. Add Product\n");
        	printf("\t2. Delete Product\n");
        	printf("\t3. Search Product\n");
        	printf("\t4. Display All Products\n");
        	printf("\t5. Check Low Stock\n");
        	printf("\t6. Save & Exit\n");
		printf("\t7. Modify the Product details\n");
        	printf("\tEnter your choice: ");
        	scanf("%d", &choice);
        	switch(choice){
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
				getchar();
                                fgets(name, sizeof(name), stdin);
                                name[strcspn(name, "\n")] = 0;
                		deleteProduct(id,name);
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
			case 7:
				printf("Enter the Product ID and Name:");
				scanf("%d",&id);
				getchar();
				fgets(name, sizeof(name), stdin);
				name[strcspn(name, "\n")] = '\0';
				Rectify(id,name);
				break;
			default:
                		printf("Invalid choice, try again.\n");
        	}
	}
}


