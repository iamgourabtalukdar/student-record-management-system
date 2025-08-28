/*
 ============================================================================
 File: main.c
 Description: A simple Student Record Management System in C.
 This program allows a user to add, display, search, and delete student
 records, which are stored in a binary file named "students.dat".
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a student record
struct Student {
    int rollNumber;
    char name[50];
    float marks;
};

// --- Function Prototypes ---
void addStudentRecord();
void displayAllRecords();
void searchStudentRecord();
void deleteStudentRecord();
void print_help();

// Name of the file where records are stored
const char* FILENAME = "students.dat";

int main() {
    char command[20];

    while (1) {
        print_help();
        printf("\nEnter your choice: ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            addStudentRecord();
        } else if (strcmp(command, "display") == 0) {
            displayAllRecords();
        } else if (strcmp(command, "search") == 0) {
            searchStudentRecord();
        } else if (strcmp(command, "delete") == 0) {
            deleteStudentRecord();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void print_help() {
    printf("\n--- Student Record System ---\n");
    printf("  add      - Add a new student record\n");
    printf("  display  - Display all student records\n");
    printf("  search   - Search for a student by roll number\n");
    printf("  delete   - Delete a student record by roll number\n");
    printf("  exit     - Exit the program\n");
    printf("-----------------------------\n");
}

// Function to add a new student record to the file
void addStudentRecord() {
    struct Student newStudent;
    FILE *fp;

    // Open the file in "append binary" mode.
    // 'ab' adds to the end of the file without deleting existing content.
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error: Cannot open file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &newStudent.rollNumber);
    printf("Enter Name: ");
    scanf(" %[^\n]s", newStudent.name); // Read string with spaces
    printf("Enter Marks: ");
    scanf("%f", &newStudent.marks);

    // Write the new student struct to the file
    fwrite(&newStudent, sizeof(struct Student), 1, fp);

    printf("\nStudent record added successfully!\n");
    fclose(fp);
}

// Function to display all records from the file
void displayAllRecords() {
    struct Student currentStudent;
    FILE *fp;

    // Open the file in "read binary" mode
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error: No records found or cannot open file!\n");
        return;
    }

    printf("\n--- All Student Records ---\n");
    printf("%-15s %-30s %-10s\n", "Roll Number", "Name", "Marks");
    printf("-----------------------------------------------------\n");

    // Read and display each record one by one until the end of the file
    while (fread(&currentStudent, sizeof(struct Student), 1, fp) == 1) {
        printf("%-15d %-30s %-10.2f\n", currentStudent.rollNumber, currentStudent.name, currentStudent.marks);
    }
    printf("-----------------------------------------------------\n");

    fclose(fp);
}

// Function to search for a specific student by roll number
void searchStudentRecord() {
    int rollToSearch;
    int found = 0;
    struct Student currentStudent;
    FILE *fp;

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &rollToSearch);

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error: Cannot open file!\n");
        return;
    }

    while (fread(&currentStudent, sizeof(struct Student), 1, fp) == 1) {
        if (currentStudent.rollNumber == rollToSearch) {
            printf("\n--- Record Found ---\n");
            printf("Roll Number: %d\n", currentStudent.rollNumber);
            printf("Name: %s\n", currentStudent.name);
            printf("Marks: %.2f\n", currentStudent.marks);
            printf("----------------------\n");
            found = 1;
            break; // Stop searching once found
        }
    }

    if (!found) {
        printf("\nRecord with Roll Number %d not found.\n", rollToSearch);
    }

    fclose(fp);
}

// Function to delete a student record
void deleteStudentRecord() {
    int rollToDelete;
    int found = 0;
    struct Student currentStudent;
    FILE *fp, *temp_fp;

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &rollToDelete);

    fp = fopen(FILENAME, "rb");
    temp_fp = fopen("temp.dat", "wb"); // Create a temporary file

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Cannot open file!\n");
        return;
    }

    // Read from the original file and write to the temporary file,
    // skipping the record that needs to be deleted.
    while (fread(&currentStudent, sizeof(struct Student), 1, fp) == 1) {
        if (currentStudent.rollNumber == rollToDelete) {
            found = 1; // Mark as found, but don't write it to the temp file
        } else {
            fwrite(&currentStudent, sizeof(struct Student), 1, temp_fp);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    // Delete the original file and rename the temporary file
    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found) {
        printf("\nRecord with Roll Number %d deleted successfully.\n", rollToDelete);
    } else {
        printf("\nRecord with Roll Number %d not found.\n", rollToDelete);
    }
}
