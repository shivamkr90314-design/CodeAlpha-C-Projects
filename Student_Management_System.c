
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "students.dat"

typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

void addStudent(void) {
    FILE *fp;
    Student s, temp;
    int found = 0;

    fp = fopen(FILE_NAME, "ab+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    rewind(fp);
    while (fread(&temp, sizeof(Student), 1, fp) == 1) {
        if (temp.roll == s.roll) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Roll number already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Name (one word): ");
    scanf("%49s", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fseek(fp, 0, SEEK_END);
    fwrite(&s, sizeof(Student), 1, fp);

    fclose(fp);
    printf("Student added successfully!\n");
}

void displayStudents(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    Student s;
    int found = 0;

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n",
               s.roll, s.name, s.marks);
        found = 1;
    }

    if (!found)
        printf("No records available.\n");

    fclose(fp);
}

void searchStudent(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("Roll: %d\nName: %s\nMarks: %.2f\n",
                   s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");

    fclose(fp);
}

void updateStudent(void) {
    FILE *fp = fopen(FILE_NAME, "rb+");
    Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("Enter roll number to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("Enter new name (one word): ");
            scanf("%49s", s.name);

            printf("Enter new marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);

            found = 1;
            break;
        }
    }

    if (found)
        printf("Student updated successfully!\n");
    else
        printf("Student not found!\n");

    fclose(fp);
}

void deleteStudent(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    Student s;
    int roll, found = 0;

    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        if (fp != NULL)
            fclose(fp);
        return;
    }

    if (fp == NULL) {
        fclose(temp);
        remove("temp.dat");
        printf("No student records found.\n");
        return;
    }

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        if (remove(FILE_NAME) == 0 &&
            rename("temp.dat", FILE_NAME) == 0) {
            printf("Student deleted successfully!\n");
        } else {
            printf("File replacement failed!\n");
        }
    } else {
        remove("temp.dat");
        printf("Student not found!\n");
    }
}

int main(void) {
    int choice;

    do {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}