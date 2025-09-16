#include <stdio.h>

    //student record structure
    struct student_record
    {
        int studentID;
        char studentName[50]; 
        char emailID[50];
        char courseID[50];
        char grade[3];
    };

int main(void){

    // variable declarations
    int choice;
    FILE *fptr;

    // display main menu
    printf("\t\tMAIN MENU\n"
    "1. Create the binary file\n"
    "2. Add a record to the file\n"
    "3. Display the contents of the file\n"
    "4. Seek a specific record\n"
    "5. Update contents of a record\n"
    "6. Delete a record for a specific name\n"
    "7. Exit\n"
    "\t\tPlease enter your choice...");

    // get & store user's choice
    scanf("%d", &choice);

    
    
}