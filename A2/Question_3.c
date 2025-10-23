#include <stdio.h>

#define ROWS 3
#define COLS 3

void updateSectorStatus(int grid[ROWS][COLS]) {
    int row, col, flag, action;

    printf("\nEnter Sector Row (0-%d): ", ROWS - 1);
    scanf("%d", &row);

    printf("Enter Sector Column (0-%d): ", COLS - 1);
    scanf("%d", &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("\nInvalid coordinates.\n");
        return;
    }

    printf("\nSelect Status Flag to Update:\n");
    printf("1. Power Status (Bit 0)\n");
    printf("2. Overload Warning (Bit 1)\n");
    printf("3. Maintenance Required (Bit 2)\n");
    printf("Enter your choice: ");
    scanf("%d", &flag);

    printf("Enter 1 to SET or 0 to CLEAR the flag: ");
    scanf("%d", &action);

    int bit = flag - 1;

    if (action == 1)
        grid[row][col] |= (1 << bit);
    else
        grid[row][col] &= ~(1 << bit);

    printf("\nSector [%d][%d] updated successfully.\n", row, col);
}

void querySectorStatus(int grid[ROWS][COLS]) {
    int row, col;

    printf("\nEnter Sector Row (0-%d): ", ROWS - 1);
    scanf("%d", &row);

    printf("Enter Sector Column (0-%d): ", COLS - 1);
    scanf("%d", &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("\nInvalid coordinates.\n");
        return;
    }

    int sector = grid[row][col];
    printf("\n================ SECTOR STATUS REPORT ================\n");
    printf("Sector Coordinates: [%d][%d]\n", row, col);
    printf("Power Status: %s\n", (sector & 1) ? "ON" : "OFF");
    printf("Overload Warning: %s\n", (sector & 2) ? "OVERLOADED" : "NORMAL");
    printf("Maintenance Required: %s\n", (sector & 4) ? "YES" : "NO");
    printf("======================================================\n");
}

void runSystemDiagnostic(int grid[ROWS][COLS]) {
    int overloadedCount = 0;
    int maintenanceCount = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] & 2)
                overloadedCount++;
            if (grid[i][j] & 4)
                maintenanceCount++;
        }
    }

    printf("\n================= SYSTEM DIAGNOSTIC =================\n");
    printf("Total Overloaded Sectors: %d\n", overloadedCount);
    printf("Sectors Requiring Maintenance: %d\n", maintenanceCount);
    printf("=====================================================\n");
}

int main() {
    int grid[ROWS][COLS] = {0};
    int choice;

    do {
        printf("\n===================================================\n");
        printf("        IESCO POWER GRID MONITORING SYSTEM         \n");
        printf("===================================================\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("===================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateSectorStatus(grid);
                break;
            case 2:
                querySectorStatus(grid);
                break;
            case 3:
                runSystemDiagnostic(grid);
                break;
            case 4:
                printf("\nExiting system... Stay powered!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
