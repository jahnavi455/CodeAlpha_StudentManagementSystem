#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    char course[50];
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {

    int choice;

    while(1) {

        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}


void addStudent() {

    FILE *fp = fopen("students.txt", "a");
    struct Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf("%s",&s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf("%s",&s.course);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}


void displayStudents() {

    FILE *fp = fopen("students.txt", "r");
    struct Student s;

    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- STUDENT RECORDS ---\n");

    while(fread(&s, sizeof(s), 1, fp)) {
        printf("\nID: %d\nName: %s\nAge: %d\nCourse: %s\n",
               s.id, s.name, s.age, s.course);
    }

    fclose(fp);
}


void searchStudent() {

    FILE *fp = fopen("students.txt", "r");
    struct Student s;
    int id, found = 0;

    printf("Enter ID to search: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {

        if(s.id == id) {
            printf("\nStudent Found!\n");
            printf("ID: %d\nName: %s\nAge: %d\nCourse: %s\n",
                   s.id, s.name, s.age, s.course);
            found = 1;
        }
    }

    if(!found) {
        printf("Student not found!\n");
    }

    fclose(fp);
}


void updateStudent() {

    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Student s;
    int id, found = 0;

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {

        if(s.id == id) {

            printf("Enter new name: ");
            scanf("%s", s.name);

            printf("Enter new age: ");
            scanf("%d", &s.age);

            printf("Enter new course: ");
            scanf("%s", s.course);

            found = 1;
        }

        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        printf("Student updated successfully!\n");
    else
        printf("Student not found!\n");
}

void deleteStudent() {

    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Student s;
    int id, found = 0;

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {

        if(s.id == id) {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        printf("Student deleted successfully!\n");
    else
        printf("Student not found!\n");
}
