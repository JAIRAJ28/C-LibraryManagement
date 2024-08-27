#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

void password();
void heading();
void mainMenu();
void addBook();
void viewBook();
void searchBook();
void editBook();
void deleteBook();
void help();
void exitProgram();


struct Book_info{
    int id;
    char name[10];
    char author[10];
    int quantity;
    int rack;
};

struct Book_info a;
FILE *file;

int main() {
    password();  // Call the password function to execute the password checking
    return 0;
}


void mainMenu(){
    int ch;

    #ifdef _WIN32
        system("cls");  // Clear the screen on Windows
    #else
        system("clear");  // Clear the screen on Unix-like systems
    #endif
    
    printf("\n \n \t \t ******************************** Main Menu ******************************** \n");
    
    int choice;

    printf("\n\t\t Main Menu   \n");
    printf("\t\t  1. Add book   \n");
    printf("\t\t  2. View book list   \n");
    printf("\t\t  3. Search book   \n");
    printf("\t\t  4. Edit book   \n");
    printf("\t\t  5. Delete book   \n");
    printf("\t\t  6. Help   \n");
    printf("\t\t  7. Exit   \n\n");
    printf("\t\t**************************************************\n");
    printf("\t\t  Enter your choice: ");
    
    scanf("%d", &choice);
    
    if(choice==1){
        addBook();
    }
    else if(choice==2){
        viewBook();
    }
    else if(choice ==3){
        searchBook();
    }
    else if(choice ==4){
        editBook();
    }
    else if (choice ==5){
         deleteBook();
    }
    else if(choice ==6){
         help() ;
    }
    else if(choice ==7){
        exitProgram();
    }
    while ((ch = getchar()) != '\n' && ch != EOF);  
    getchar();
}

void addBook() {
    system("cls");
    int d, count = 0;
    printf("\n\n \t \t Add Book \n");

    file = fopen("books.dat", "ab+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\t\t Enter the ID: ");
    scanf("%d", &d);
    rewind(file);

    while (fread(&a, sizeof(a), 1, file) == 1) {
        if (d == a.id) {
            printf("\n\n\t\t This book is already in the library");
            count = 1;
            break;
        }
    }

    if (count == 1) {
        printf("\n\n\t\t Book with the same ID already exists in the library");
        fflush(stdin);
        getchar();
        fclose(file);
        mainMenu();
        return;
    }

    a.id = d;
    printf("\n\n\t\t Enter the name: ");
    scanf("%s", a.name);

    printf("\n\n\t\t Enter the author's name: ");
    scanf("%s", a.author);

    printf("\n\n\t\t Enter the quantity: ");
    scanf("%d", &a.quantity);

    printf("\n\n\t\t Enter the rack number: ");
    scanf("%d", &a.rack);

    fseek(file, 0, SEEK_END);
    fwrite(&a, sizeof(a), 1, file);
    fclose(file);

    printf("\n\n\t\t Book added successfully!");
    fflush(stdin);
    getchar();
    mainMenu();
}

void viewBook() {
    system("cls");
    printf("\n\n\t\t ************* View BOOK LIST *************");
    printf("\n\tID\tName\tAuthor\tQuantity\t Rack\n\n");
    file = fopen("books.dat", "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    while (fread(&a, sizeof(a), 1, file) == 1) {
        printf("\t%d\t%s\t%s\t%d\t%d\n", a.id, a.name, a.author, a.quantity, a.rack);
    }
    fclose(file);
    printf("\n\nPress Enter to return to the main menu...");
    getchar();  
    getchar();  
    mainMenu();
}

void help() {
    system("cls");
    printf("\n\n\t\t************* Help Menu *************\n\n");
    printf("\t1. To add a book, select option 1 from the main menu and enter the details.\n");
    printf("\t2. To view the book list, select option 2 from the main menu.\n");
    printf("\t3. To search for a book, select option 3 and enter the book's ID.\n");
    printf("\t4. To edit a book's details, select option 4 and enter the book's ID.\n");
    printf("\t5. To delete a book, select option 5 and enter the book's ID.\n");
    printf("\t6. For help, select this option.\n");
    printf("\t7. To exit, select option 7 from the main menu.\n");
    printf("\n\nPress Enter to return to the main menu...");
    getchar();
    getchar();
    mainMenu();
}


void searchBook() {
    int d;
    int bookFound = 0;  //

    system("cls");
    printf("\n\n \t\t ******************************** Search The Book ********************************");
    printf("\n\n \t\t Enter the ID of the book: ");
    scanf("%d", &d);

    file = fopen("books.dat", "rb");  
    if (file == NULL) {
        printf("\nError opening file!\n"); 
        return;
    }

    while (fread(&a, sizeof(a), 1, file) == 1) {
        if (d == a.id) {
            bookFound = 1;  
            printf("\n\n\t\t *************** Book Is Found ****************");
            printf("\n\t\t ID: %d", a.id);
            printf("\n\t\t Name: %s", a.name);
            printf("\n\t\t Author: %s", a.author);
            printf("\n\t\t Quantity: %d", a.quantity);
            printf("\n\t\t Rack: %d\n", a.rack);
            break;  
        }
    }
    if (bookFound == 0) {
        printf("\n\n\t\t No book found with ID %d.\n", d);
    }
    fclose(file);  
    printf("\n\nPress Enter to return to the main menu...");
    fflush(stdin);  
    getchar(); 
    mainMenu();  
}


void editBook() {
    system("cls");
    int d, count = 0;
    printf("\n\n\t\t **************** Edit Book ********************\n");
    file = fopen("books.dat", "rb+");  
    if (file == NULL) {
        printf("\nError opening file!\n");  
        return;
    }
    printf("\n\t\t Enter ID: ");
    scanf("%d", &d);
    while (fread(&a, sizeof(a), 1, file) == 1) {
        if (d == a.id) {
            printf("\n\t\t Book is available \n");
            printf("\n\t\t ID: %d", a.id);
            printf("\n\t\t Current Name: %s", a.name);
            printf("\n\t\t Current Author: %s", a.author);
            printf("\n\t\t Current Quantity: %d", a.quantity);
            printf("\n\t\t Current Rack: %d\n", a.rack);
            printf("\n\n Enter New Name: ");
            scanf("%s", a.name);
            printf("\n\n Enter New Author: ");
            scanf("%s", a.author);
            printf("\n\n Enter New Quantity: ");
            scanf("%d", &a.quantity);
            printf("\n\n Enter New Rack: ");
            scanf("%d", &a.rack);
            fseek(file, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, file);
            fclose(file);  
            count = 1;
            printf("\n\t\t Book details updated successfully.\n");
            break;
        }
    }
    if (count == 0) {
        printf("\n\t\t Book with ID %d is not found.\n", d);  
    }
    fclose(file);  
    printf("\n\nPress Enter to return to the main menu...");
    fflush(stdin);  
    getchar();  
    mainMenu();  
}


void deleteBook() {
    system("cls");
    int d;
    int bookFound = 0;

    printf("\n\n\t\t **************** Delete Book ********************\n");

    file = fopen("books.dat", "rb");
    if (file == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("\nError opening temporary file!\n");
        fclose(file);
        return;
    }

    printf("\n\t\t Enter the ID of the book to delete: ");
    scanf("%d", &d);

    while (fread(&a, sizeof(a), 1, file) == 1) {
        if (d == a.id) {
            bookFound = 1;
            printf("\n\t\t Book with ID %d is deleted successfully.\n", a.id);
        } else {
            fwrite(&a, sizeof(a), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (bookFound) {
        remove("books.dat");
        rename("temp.dat", "books.dat");
    } else {
        printf("\n\t\t No book found with ID %d.\n", d);
        remove("temp.dat");
    }

    printf("\n\nPress Enter to return to the main menu...");
    fflush(stdin);
    getchar();
    mainMenu();
}


void exitProgram() {
    system("cls");
    printf("\n\n\t\t************* Exiting Program *************\n");
    printf("\tThank you for using the Library Management System.\n");
    printf("\tGoodbye!\n\n");
    exit(0);
}


void heading() {
#ifdef _WIN32
    system("cls");  // Clear the screen on Windows
#else
    system("clear");  // Clear the screen on Unix-like systems
#endif

   printf("\n \n \t \t ******************************** Library Management Software ******************************** \n");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);  
    printf("Press Enter to continue...");
    getchar();  
}


void password() {
    int isEqual;
    heading();
    char staticPwd[10] = "admin@28";
    char enteredPwd[100];  
    int maxAttempts = 3;

    for (int attempt = 0; attempt < maxAttempts; attempt++) {
        printf("Enter password (Attempt %d/%d): ", attempt + 1, maxAttempts);
        scanf("%s", enteredPwd);

        isEqual = 1;  
        for (int i = 0; staticPwd[i] != '\0' || enteredPwd[i] != '\0'; i++) {
            if (staticPwd[i] != enteredPwd[i]) {
                isEqual = 0; 
                break;
            }
        }

        if (isEqual && staticPwd[strlen(staticPwd)] == '\0' && enteredPwd[strlen(enteredPwd)] == '\0') {
            printf("Password correct! Access granted.\n");
            mainMenu();
            return;  
        } else {
            printf("Incorrect password.\n");
        }
    }

    printf("Access denied. Too many failed attempts.\n");
}
