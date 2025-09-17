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
            
            printf("\n1. Create File\n");
            printf("--------------\n");

            // CHECK IF FILE EXCISTS
            if (fileExists(filename))
            {
                printf("ERROR: File '%s' already exists!!\n", filename);
            }
            else
            {
                printf("Creating file '%s'...\n", filename);
                fptr = fopen(filename, "wb");
                fclose(fptr);
                printf("Binary file created.\n");
            }
            break;

        case 2: // ADD RECORD TO BINARY FILE
            
        printf("\n2. Add Record to File\n");
        printf("---------------------\n");

            if (!fileExists(filename))
            {
                printf("File DNE. Create file first using menu option 1.\n");
            }
            else
            {
                // CREATE NEW RECORD
                struct student_record record;

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

                // OPEN BINARY FILE IN APPEND MODE
                fptr = fopen(filename, "ab");

                // WRITE RECORD TO FILE
                fwrite(&record, sizeof(record), 1, fptr);
                fclose(fptr);
            }
            break;

        case 3: // DISPLAY BINARY FILE CONTENTS

            printf("\n3. Display File Contents\n");
            printf("------------------------\n");

            // CHECK IF FILE EXISTS
            if (!fileExists(filename))
            {
                printf("ERROR: File DNE. Create file first using menu option 1.\n");
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

            printf("\n4. Seek A Record\n");
            printf("----------------\n");

            // CHECK IF FILE EXISTS
            if (!fileExists(filename))
            {
                printf("ERROR: File DNE. Create file first using menu option 1.\n");
            }
            else
            {
                char searchByID[20];
                bool IDfound = false;

                struct student_record record;
                fptr = fopen(filename, "rb");

                // DISPLAY ID LIST
                printf("=> IDs in File:\n");
                while (fread(&record, sizeof(record), 1, fptr) == 1)
                {
                    printf("- %s\n", record.studentID);
                }

                // SEEK BY STUDENT ID
                printf("\tEnter student ID to search: ");
                scanf("%s", searchByID);
                rewind(fptr);

                while (fread(&record, sizeof(record), 1, fptr) == 1)
                {
                    if (strcmp(record.studentID, searchByID) == 0)
                    {
                        printf("Record of student ID %s:\n", searchByID);
                        printf("\n\tStudent ID: %s\n\tStudent name: %s\n\tEmail ID: %s\n\tCourse ID: %s\n\tGrade: %s\n",
                               record.studentID, record.studentName, record.emailID, record.courseID, record.grade);
                        IDfound = true;
                        break;
                    }
                }
                if (!IDfound)
                {
                    printf("No record found for student ID: %s\n", searchByID);
                }
                
                fclose(fptr);
            }
            break;

        case 5:
            // update a record
            break;
        case 6:
            // delete a record
            break;
        case 7:
            // EXIT PROGRAM
            printf("Exiting program. Goodbye!");
            break;
        default:
            printf("Please enter a valid choice... ");
        }

    } while (menuSelection != 7);
    exit(0);
}