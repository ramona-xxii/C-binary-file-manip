#include <stdio.h>
#include <stdlib.h>

// student record structure
struct student_record
{
    int studentID;
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
            
            // check if file already exists
            fptr = fopen("student-records.dat", "rb");
            
            if (fptr == NULL)
            {
                printf("Creating file 'student-records.dat'");
                fptr = fopen("student-records.dat", "wb+");
                fclose(fptr);
            }
            else
            {
                printf("File 'student-records.dat' already exists.\n");
                fclose(fptr);
            }
            break;

        case 2: // ADD RECORD TO FILE
            break;
        case 3:
            // display file contents
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