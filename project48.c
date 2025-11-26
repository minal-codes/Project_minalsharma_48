#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEHICLE_NUM 20

// ---------------- STRUCTURE ----------------
struct Vehicle {
    char number[20];
    int lastServiceDay;
    int lastServiceMonth;
    int lastServiceYear;
    int mileage;
    int avgDailyUsage;
};

// ---------------- FUNCTION DECLARATIONS ----------------
void addVehicles(struct Vehicle *v, int count);
void displayVehicles(struct Vehicle *v, int count);
void predictNextService(struct Vehicle *v, int count);
void checkOverdue(struct Vehicle *v, int count, int currentDay, int currentMonth, int currentYear);
int daysSinceService(int d, int m, int y, int cd, int cm, int cy);

// -------------------------------------------------------
int main() {
    int vehicleCount;
    printf("Enter number of vehicles: ");
    scanf("%d", &vehicleCount);

    // Dynamic allocation using pointers (CO4)
    struct Vehicle *fleet = (struct Vehicle *)malloc(vehicleCount * sizeof(struct Vehicle));

    addVehicles(fleet, vehicleCount);

    int choice;
    int cDay, cMonth, cYear;

    while (1) {
        printf("\n========== SMART VEHICLE MAINTENANCE TRACKER ==========\n");
        printf("1. Display Vehicle Records\n");
        printf("2. Predict Next Service Date\n");
        printf("3. Check Overdue Services\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayVehicles(fleet, vehicleCount);
                break;

            case 2:
                predictNextService(fleet, vehicleCount);
                break;

            case 3:
                printf("Enter Current Date (DD MM YYYY): ");
                scanf("%d %d %d", &cDay, &cMonth, &cYear);
                checkOverdue(fleet, vehicleCount, cDay, cMonth, cYear);
                break;

            case 4:
                free(fleet);  
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// ---------------- FUNCTIONS ----------------

// Add vehicle data
void addVehicles(struct Vehicle *v, int count) {
    for (int i = 0; i < count; i++) {
        printf("\nEnter details for Vehicle %d\n", i + 1);
        printf("Vehicle Number: ");
        scanf("%s", v[i].number);

        printf("Last Service Date (DD MM YYYY): ");
        scanf("%d %d %d", &v[i].lastServiceDay, &v[i].lastServiceMonth, &v[i].lastServiceYear);

        printf("Current Mileage: ");
        scanf("%d", &v[i].mileage);

        printf("Average Daily Usage (km/day): ");
        scanf("%d", &v[i].avgDailyUsage);
    }
}

// Display vehicle records
void displayVehicles(struct Vehicle *v, int count) {
    printf("\n----- VEHICLE RECORDS -----\n");
    for (int i = 0; i < count; i++) {
        printf("\nVehicle %d:\n", i + 1);
        printf("Number: %s\n", v[i].number);
        printf("Last Service Date: %02d-%02d-%04d\n", v[i].lastServiceDay, v[i].lastServiceMonth, v[i].lastServiceYear);
        printf("Mileage: %d km\n", v[i].mileage);
        printf("Average Daily Usage: %d km/day\n", v[i].avgDailyUsage);
    }
}

// Predict next service using mileage logic
void predictNextService(struct Vehicle *v, int count) {
    printf("\n----- PREDICTED NEXT SERVICE -----\n");
    for (int i = 0; i < count; i++) {
        int kmLeft = 5000 - (v[i].mileage % 5000);  // Assuming service every 5000 km
        int daysLeft = kmLeft / v[i].avgDailyUsage;

        printf("\nVehicle: %s\n", v[i].number);
        printf("Kilometers left for service: %d km\n", kmLeft);
        printf("Estimated days before next service: %d days\n", daysLeft);
    }
}

// Check overdue services
void checkOverdue(struct Vehicle *v, int count, int cd, int cm, int cy) {
    printf("\n----- OVERDUE SERVICE CHECK -----\n");
    for (int i = 0; i < count; i++) {
        int days = daysSinceService(v[i].lastServiceDay, v[i].lastServiceMonth, v[i].lastServiceYear, cd, cm, cy);

        if (days > 180) {
            printf("\nALERT: Vehicle %s is OVERDUE (%d days since last service!)\n", v[i].number, days);
        } else {
            printf("\nVehicle %s is OK (%d days since service)\n", v[i].number, days);
        }
    }
}

// Rough day calculator
int daysSinceService(int d, int m, int y, int cd, int cm, int cy) {
    return (cy - y) * 365 + (cm - m) * 30 + (cd - d);
}

