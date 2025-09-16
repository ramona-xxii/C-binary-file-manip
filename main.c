#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// function to check if binary file exists
bool fileExists(const char *filename) {
    FILE *fptr = fopen(filename, "rb");
    if(fptr != NULL){
        fclose(fptr);
        return true;
    }
    return false;
}

// student record structure
struct student_record
{
    char studentID[20];
    char studentName[50];
    char emailID[50];
    char courseID[50];
    char grade[3];
};

int main(void)
{
    // variable declarations
    int menuSelection;
    FILE *fptr;
    char filename[] = "student_records.dat";

    do
    {
        // display main menu
        printf("\t\tMAIN MENU\n"
               "1. Create the binary file\n"
               "2. Add a record to the file\n"
               "3. Display the contents of the file\n"
               "4. Seek a specific record\n"
               "5. Update contents of a record\n"
               "6. Delete a record for a specific name\n"
               "7. Exit\n"
               "\t\tPlease enter your choice... ");

        // get & store user's menu selection
        scanf("%d", &menuSelection);

        // determine menu selection
        switch (menuSelection)
        {

        case 1: // CREATE FILE
            
            // CHECK IF FILE EXCISTS
            if(fileExists(filename)){
                printf("File '%s' already exists.\n", filename);
            }else{
                printf("Creating file '%s'", filename);
                fptr = fopen(filename, "rb");
                fclose(fptr);
            }
            break;

        case 2: // ADD RECORD TO BINARY FILE
            if(!fileExists(filename)){
                printf("File DNE. Create file first using menu option 1.\n");
            }else{
                // CREATE NEW RECORD
                struct student_record record;

                printf("Enter student ID: ");
                scanf("%s", record.studentID);

                printf("Enter student name: ");
                scanf("%s", record.studentName);

                printf("Enter student email ID: ");
                scanf("%s", record.emailID);

                printf("Enter course ID: ");
                scanf("%s", record.courseID);

                printf("Enter grade: ");
                scanf("%s", record.grade);

                // OPEN BINARY FILE IN APPEND MODE
                fptr = fopen(filename, "ab");

                // WRITE RECORD TO FILE
                fwrite(&record, sizeof(record), 1, fptr);
                fclose(fptr);
            }
            break;

        case 3: // DISPLAY BINARY FILE CONTENTS
            break;
        case 4:
            // seek a record
            break;
        case 5:
            // update a record
            break;
        case 6:
            // delete a record
            break;
        case 7:
            // exit program
            printf("Exiting program.");
            exit(0);
        default:
            printf("Please enter a valid choice...");
        }

    } while (menuSelection != 7);

}