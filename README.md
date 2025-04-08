# Product Inventory Management System (C Project)

This is a console-based Inventory Management System written in C using **Doubly Linked List** and **File Handling**. It allows users to manage products by adding, deleting, modifying, searching, and saving data persistently to a file.

---

## Project Structure

```plaintext
.
├── pro_invent_man_main.c        # Contains the main menu and main function
├── pro_invent_man_functions.c   # Core logic of product operations
├── pro_invent_man_header.h      # Header file with struct and function declarations
├── Makefile                     # Build file to compile the project
├── inventory.txt                # Data file (created at runtime)
└── README.md                    # Project documentation

To compile the project:  
    make

To run it:
    ./inventory
