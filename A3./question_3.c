#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure to store employee data
struct Employee {
  int id;
  char name[50];
  char designation[50];
  float salary;
};

// Function to display all employee records
void displayEmployees(struct Employee emp[], int n) {
  printf("\n-------------------------------------------------------------\n");
  printf("%-10s %-20s %-20s %-10s\n", "ID", "Name", "Designation", "Salary");
  printf("-------------------------------------------------------------\n");

  for (int i = 0; i < n; i++) {
    printf("%-10d %-20s %-20s %-10.2f\n", emp[i].id, emp[i].name,
           emp[i].designation, emp[i].salary);
  }
  printf("-------------------------------------------------------------\n");
}

// Function to find and display employee with highest salary
void findHighestSalary(struct Employee emp[], int n) {
  int index = 0;

  for (int i = 1; i < n; i++) {
    if (emp[i].salary > emp[index].salary) {
      index = i;
    }
  }

  printf("\nEmployee with Highest Salary:\n");
  printf("ID: %d\n", emp[index].id);
  printf("Name: %s\n", emp[index].name);
  printf("Designation: %s\n", emp[index].designation);
  printf("Salary: %.2f\n", emp[index].salary);
}

// Function to search employee by ID or Name
void searchEmployee(struct Employee emp[], int n) {
  int choice;
  printf("\nSearch Employee by:\n");
  printf("1. ID\n");
  printf("2. Name\n");
  printf("Enter choice: ");
  scanf("%d", &choice);

  if (choice == 1) {
    int searchId;
    printf("Enter Employee ID: ");
    scanf("%d", &searchId);

    for (int i = 0; i < n; i++) {
      if (emp[i].id == searchId) {
        printf("\nEmployee Found:\n");
        printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n", emp[i].id,
               emp[i].name, emp[i].designation, emp[i].salary);
        return;
      }
    }
    printf("No employee found with ID %d\n", searchId);
  }

  else if (choice == 2) {
    char searchName[50];
    printf("Enter Employee Name: ");
    getchar(); // Clear newline
    fgets(searchName, sizeof(searchName), stdin);

    // Remove trailing newline
    searchName[strcspn(searchName, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
      if (strcmp(emp[i].name, searchName) == 0) { // case-sensitive
        printf("\nEmployee Found:\n");
        printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n", emp[i].id,
               emp[i].name, emp[i].designation, emp[i].salary);
        return;
      }
    }
    printf("No employee found with name %s\n", searchName);
  }

  else {
    printf("Invalid choice.\n");
  }
}

int main() {
  struct Employee emp[MAX];
  int n;

  printf("Enter number of employees: ");
  scanf("%d", &n);

  // Input Employee Records
  for (int i = 0; i < n; i++) {
    printf("\nEnter details for Employee %d:\n", i + 1);

    printf("ID: ");
    scanf("%d", &emp[i].id);

    printf("Name: ");
    getchar();
    fgets(emp[i].name, sizeof(emp[i].name), stdin);
    emp[i].name[strcspn(emp[i].name, "\n")] = '\0';

    printf("Designation: ");
    fgets(emp[i].designation, sizeof(emp[i].designation), stdin);
    emp[i].designation[strcspn(emp[i].designation, "\n")] = '\0';

    printf("Salary: ");
    scanf("%f", &emp[i].salary);
  }

  // Display
  displayEmployees(emp, n);

  // Highest salary
  findHighestSalary(emp, n);

  // Search employee
  searchEmployee(emp, n);

  return 0;
}
