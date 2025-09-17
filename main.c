#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// function to check if binary file exists
bool fileExists(const char *filename)
{
    FILE *fptr = fopen(filename, "rb");
    if (fptr != NULL)
    {
        fclose(fptr);
        return true;
    }
    return false;
}

// student record structure
struct student_record
{
    char studentID[20];
    char studentName[30];
    char emailID[50];
    char courseID[10];
    char grade[3];
};

int main(void)
{
    // variable declarations
    int menuSelection;
    FILE *fptr;
    char filename[] = "student_records.dat";
    char errorFileDNE[] = "ERROR: File DNE. Create file first using menu option 1.";

    // remove local copies if any before execution
    if(fileExists(filename)){
        remove(filename);
    }

    do
    {
        // display main menu
        printf("\n\t\tMAIN MENU\n"
               "\t\t---------\n"
               "1. Create the binary file\n"
               "2. Add a record to the file\n"
               "3. Display the contents of the file\n"
               "4. Seek a specific record\n"
               "5. Update contents of a record\n"
               "6. Delete a record for a specific name\n"
               "7. Exit\n"
               "\tPlease enter your choice... ");

        // get & store user's menu selection
        scanf("%d", &menuSelection);

        // determine menu selection
        switch (menuSelection)
        {

        case 1: // CREATE FILE

            printf("\nYour choice: 1. Create File\n");
            printf("-----------------------------\n");

            // check if file exists before creating
            if (fileExists(filename))
            {
                // display error message if file already exists
                printf("ERROR: File '%s' already exists!!\n", filename);
            }
            else
            {
                // create binary file if file DNE
                printf("=> Creating file '%s'...\n", filename);
                fptr = fopen(filename, "wb");
                fclose(fptr);
                printf("=> Binary file created.\n");
            }
            break;

        case 2: // ADD RECORD TO BINARY FILE

            printf("\nYour choice: 2. Add Record to File\n");
            printf("----------------------------------\n");

            if (!fileExists(filename))
            {
                // display error message if file DNE
                printf("%s\n", errorFileDNE);
            }
            else
            {
                // create new record
                struct student_record record;
                printf("Enter Record Info Below:\n");

                printf("=> Enter student ID: ");
                scanf("%s", record.studentID);

                printf("=> Enter student name: ");
                scanf("%s", record.studentName);

                printf("=> Enter student email ID: ");
                scanf("%s", record.emailID);

                printf("=> Enter course ID: ");
                scanf("%s", record.courseID);

                printf("=> Enter grade: ");
                scanf("%s", record.grade);

                // open file in append/binary mode
                fptr = fopen(filename, "ab");

                // write record to file
                fwrite(&record, sizeof(record), 1, fptr);
                fclose(fptr);
            }
            break;

        case 3: // DISPLAY BINARY FILE CONTENTS

            printf("\nYour choice: 3. Display File Contents\n");
            printf("-------------------------------------\n");

            if (!fileExists(filename))
            {
                // dislpay error message if file DNE
                printf("%s\n", errorFileDNE);
            }
            else
            {
                fptr = fopen(filename, "rb");
                struct student_record record;
                while (fread(&record, sizeof(record), 1, fptr) == 1)
                {
                    printf("\nStudent ID: %s\nStudent name: %s\nEmail ID: %s\nCourse ID: %s\nGrade: %s\n",
                           record.studentID, record.studentName, record.emailID, record.courseID, record.grade);
                }
                fclose(fptr);
            }
            break;

        case 4: // SEEK A RECORD

            printf("\nYour choice: 4. Seek A Record\n");
            printf("-----------------------------\n");

            // CHECK IF FILE EXISTS
            if (!fileExists(filename))
            {
                printf("%s\n", errorFileDNE);
            }
            else
            {
                char searchByID[20];
                bool IDfound = false;

                struct student_record record;
                fptr = fopen(filename, "rb");

                // display list of all IDs in file
                printf("List of IDs in File:\n");
                while (fread(&record, sizeof(record), 1, fptr) == 1)
                {
                    printf("- %s\n", record.studentID);
                }

                // seek by student ID
                printf("\n=> Enter student ID to seek record: ");
                scanf("%s", searchByID);
                rewind(fptr);

                // read one record at a time while there is a record to read
                while (fread(&record, sizeof(record), 1, fptr) == 1)
                {
                    if (strcmp(record.studentID, searchByID) == 0)
                    {
                        printf("\nRecord of student ID %s:\n", searchByID);
                        printf("\n\tStudent ID: %s\n\tStudent name: %s\n\tEmail ID: %s\n\tCourse ID: %s\n\tGrade: %s\n",
                               record.studentID, record.studentName, record.emailID, record.courseID, record.grade);
                        IDfound = true;
                        break;
                    }
                }
                if (!IDfound)
                {
                    printf("ERROR: No record found for student ID: %s\n", searchByID);
                }

                fclose(fptr);
            }
            break;

        case 5: // UPDATE A RECORD

            printf("\nYour choice: 5. Update A Record\n");
            printf("-------------------------------\n");

            // check if file exists
            if (!fileExists(filename))
            {
                printf("%s\n", errorFileDNE);
            }
            else
            {
                char searchByID[20];
                bool IDfound = false;

                struct student_record record;
                fptr = fopen(filename, "rb+");

                // display list of students by ID
                printf("List of IDs in File:\n");
                while (fread(&record, sizeof(record), 1, fptr) == 1)
                {
                    printf("- %s\n", record.studentID);
                }
                rewind(fptr);

                printf("=> Which record would you like to modify: ");
                scanf("%s", searchByID);

                // read one record at a time while there is a record to read
                while (fread(&record, sizeof(record), 1, fptr) == 1)
                {
                    if (strcmp(record.studentID, searchByID) == 0)
                    {
                        printf("\nEnter new record info for student ID: %s\n", searchByID);

                        printf("=> Enter new student ID: ");
                        scanf("%s", record.studentID);

                        printf("=> Enter new student name: ");
                        scanf("%s", record.studentName);

                        printf("=> Enter new student email ID: ");
                        scanf("%s", record.emailID);

                        printf("=> Enter new course ID: ");
                        scanf("%s", record.courseID);

                        printf("=> Enter new grade: ");
                        scanf("%s", record.grade);

                        // move pointer back 1 record to overwrite it
                        fseek(fptr, -sizeof(record), SEEK_CUR);
                        fwrite(&record, sizeof(record), 1, fptr);

                        printf("\nRecord updated.\n");

                        IDfound = true;
                        break;
                    }
                }
                if (!IDfound)
                {
                    printf("No record for ID %s found.\n", searchByID);
                }
                fclose(fptr);
            }
            break;
        case 6: // DELETE A RECORD

            printf("\nYour choice: 6. Delete A Record\n");
            printf("-------------------------------\n");

            // check if file exists
            if (!fileExists(filename))
            {
                printf("%s\n", errorFileDNE);
            }
            else
            {
                char searchByName[30];
                bool IDfound = false;
                struct student_record record;
                fptr = fopen(filename, "rb");

                // show list of students by IDs
                printf("List of Names in File:\n");
                while (fread(&record, sizeof(record), 1, fptr) == 1)
                {
                    printf("- %s\n", record.studentName);
                }
                rewind(fptr);

                printf("=> Which record would you like to delete: ");
                scanf("%s", searchByName);

                // temp file to store records minus deleted one
                FILE *tempfptr = fopen("temp.dat", "wb");

                while (fread(&record, sizeof(record), 1, fptr) == 1)
                {
                    if (strcmp(record.studentName, searchByName) != 0)
                    {
                        // write record to temp file
                        fwrite(&record, sizeof(record), 1, tempfptr);
                    }
                    if(strcmp(record.studentName, searchByName) == 0){
                        IDfound = true;
                        printf("Record for %s deleted.\n", searchByName);
                    }
                    
                }
                fclose(fptr);
                fclose(tempfptr);

                // replace old file with new file
                remove(filename);
                rename("temp.dat", filename);
            }

            break;
        case 7: // EXIT PROGRAM

            // delete binary file
            remove(filename);

            printf("\n--- Exiting program. Goodbye! ---\n");
            break;

        default:
            printf("ERROR: Please enter a valid choice...\n");
        }

    } while (menuSelection != 7);
    exit(0);
}