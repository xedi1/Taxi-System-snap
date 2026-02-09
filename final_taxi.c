#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>   

#define MAX_USER 1404
#define NAME_LEN 50
#define PASS_LEN 20
#define LOC_LEN 100
#define MAX_RIDES 200

#define RESET       7
#define RED         12
#define GREEN       10
#define YELLOW      14
#define BLUE        9
#define MAGENTA     13
#define CYAN        11
#define WHITE       15

// ───────────────────────────────────────────────
// Color helpers (Windows)
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// ───────────────────────────────────────────────
// Sound effects
void playSuccess() {
    Beep(800, 150);   // short high beep
    Beep(1200, 100);
}

void playError() {
    Beep(300, 400);   // low long beep
}

void playRideBooked() {
    Beep(600, 120);
    Beep(900, 120);
    Beep(1200, 180);
}

// ───────────────────────────────────────────────
// ASCII Art Header
void printHeader() {
    setColor(CYAN);
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║              ADVANCED TAXI SYSTEM                  ║\n");
    printf("║                  (Powered by Edi)  ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    setColor(RESET);
}

// ───────────────────────────────────────────────
// Data Structures
struct driver {
    char username[NAME_LEN];
    char password[PASS_LEN];
    int id;
    char status[NAME_LEN];  // block/unblock
    float balance;
    int trips;
    char location[LOC_LEN];  // Added location
    bool is_logged_in;
};

struct passenger {
    char username[NAME_LEN];
    char password[PASS_LEN];
    int id;
    float balance;
    int trips;
    char status[NAME_LEN];  // None/Waiting/inRide
    char location[LOC_LEN];  // Added location
    bool is_logged_in;
};

struct ride {
    int id;
    int passenger_id;
    int driver_id;
    char pickup[LOC_LEN];
    char destination[LOC_LEN];
    float fare;
    bool completed;
};

struct driver drivers[MAX_USER];
struct passenger passengers[MAX_USER];
struct ride rides[MAX_RIDES];

int dCount = 0;
int pCount = 0;
int ride_count = 0;

// ───────────────────────────────────────────────
// File Handling Functions
void loadData() {
    FILE *ptf1 = fopen("drivers.txt", "r");
    if (ptf1) {
        while (fscanf(ptf1, "%s %s %d %s %f %d %s",
                      drivers[dCount].username, drivers[dCount].password, &drivers[dCount].id,
                      drivers[dCount].status, &drivers[dCount].balance, &drivers[dCount].trips,
                      drivers[dCount].location) == 7) {
            drivers[dCount].is_logged_in = false;
            dCount++;
        }
        fclose(ptf1);
    }

    FILE *ptf2 = fopen("passengers.txt", "r");
    if (ptf2) {
        while (fscanf(ptf2, "%s %s %d %s %f %d %s",
                      passengers[pCount].username, passengers[pCount].password, &passengers[pCount].id,
                      passengers[pCount].status, &passengers[pCount].balance, &passengers[pCount].trips,
                      passengers[pCount].location) == 7) {
            passengers[pCount].is_logged_in = false;
            pCount++;
        }
        fclose(ptf2);
    }

    FILE *ptf3 = fopen("rides.txt", "r");
    if (ptf3) {
        while (fscanf(ptf3, "%d %d %d %s %s %f %d",
                      &rides[ride_count].id, &rides[ride_count].passenger_id, &rides[ride_count].driver_id,
                      rides[ride_count].pickup, rides[ride_count].destination, &rides[ride_count].fare,
                      (int*)&rides[ride_count].completed) == 7) {
            ride_count++;
        }
        fclose(ptf3);
    }
}

void saveData() {
    FILE *ptf1 = fopen("drivers.txt", "w");
    if (ptf1) {
        for (int i = 0; i < dCount; i++) {
            fprintf(ptf1, "%s %s %d %s %.2f %d %s\n",
                    drivers[i].username, drivers[i].password, drivers[i].id, drivers[i].status,
                    drivers[i].balance, drivers[i].trips, drivers[i].location);
        }
        fclose(ptf1);
    }

    FILE *ptf2 = fopen("passengers.txt", "w");
    if (ptf2) {
        for (int i = 0; i < pCount; i++) {
            fprintf(ptf2, "%s %s %d %s %.2f %d %s\n",
                    passengers[i].username, passengers[i].password, passengers[i].id, passengers[i].status,
                    passengers[i].balance, passengers[i].trips, passengers[i].location);
        }
        fclose(ptf2);
    }

    FILE *ptf3 = fopen("rides.txt", "w");
    if (ptf3) {
        for (int i = 0; i < ride_count; i++) {
            fprintf(ptf3, "%d %d %d %s %s %.2f %d\n",
                    rides[i].id, rides[i].passenger_id, rides[i].driver_id,
                    rides[i].pickup, rides[i].destination, rides[i].fare,
                    rides[i].completed);
        }
        fclose(ptf3);
    }
}

// ───────────────────────────────────────────────
// Admin Menu
void adminMenu() {
    int c;
    do {
        system("cls");
        printHeader();
        setColor(MAGENTA);
        printf("=== ADMIN MENU ===\n");
        setColor(RESET);
        printf("1. Register Driver\n");
        printf("2. Register Passenger\n");
        printf("3. Update Driver Account\n");
        printf("4. Update Passenger Account\n");
        printf("5. View Drivers\n");
        printf("6. View Passengers\n");
        printf("7. View Rides\n");
        printf("8. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &c);

        if (c == 1) {
            if (dCount >= MAX_USER) {
                setColor(RED);
                printf("Driver limit reached!\n");
                setColor(RESET);
                playError();
                continue;
            }
            struct driver *driv = &drivers[dCount];
            setColor(YELLOW);
            printf("---- NEW DRIVER ----\n");
            setColor(RESET);
            printf("Username: "); scanf("%s", driv->username);
            for (int i = 0; i < dCount; i++) {
                if (strcmp(drivers[i].username, driv->username) == 0) {
                    setColor(RED);
                    printf("This username already exists!\n");
                    setColor(RESET);
                    playError();
                    return;
                }
            }
            printf("Password (4 digits): "); scanf("%s", driv->password);
            if (strlen(driv->password) != 4) {
                setColor(RED);
                printf("Invalid password (must be 4 digits)!\n");
                setColor(RESET);
                playError();
                return;
            }
            printf("Driver ID (4 digits): "); scanf("%d", &driv->id);
            printf("Location: "); scanf("%s", driv->location);
            int sta;
            printf("Status (1: block / 0: unblock): "); scanf("%d", &sta);
            strcpy(driv->status, (sta == 1) ? "block" : "unblock");
            driv->balance = 0.0;
            driv->trips = 0;
            driv->is_logged_in = false;
            dCount++;
            saveData();
            setColor(GREEN);
            printf("Driver registered successfully!\n");
            setColor(RESET);
            playSuccess();
        } else if (c == 2) {
            if (pCount >= MAX_USER) {
                setColor(RED);
                printf("Passenger limit reached!\n");
                setColor(RESET);
                playError();
                continue;
            }
            struct passenger *pass = &passengers[pCount];
            setColor(YELLOW);
            printf("---- NEW PASSENGER ----\n");
            setColor(RESET);
            printf("Username: "); scanf("%s", pass->username);
            for (int i = 0; i < pCount; i++) {
                if (strcmp(passengers[i].username, pass->username) == 0) {
                    setColor(RED);
                    printf("This username already exists!\n");
                    setColor(RESET);
                    playError();
                    return;
                }
            }
            printf("Password (4 digits): "); scanf("%s", pass->password);
            if (strlen(pass->password) != 4) {
                setColor(RED);
                printf("Invalid password (must be 4 digits)!\n");
                setColor(RESET);
                playError();
                return;
            }
            printf("Passenger ID (4 digits): "); scanf("%d", &pass->id);
            printf("Location: "); scanf("%s", pass->location);
            int sta;
            printf("Status (0: None / 1: Waiting / 2: inRide): "); scanf("%d", &sta);
            if (sta == 1) strcpy(pass->status, "Waiting");
            else if (sta == 2) strcpy(pass->status, "inRide");
            else strcpy(pass->status, "None");
            pass->balance = 0.0;
            pass->trips = 0;
            pass->is_logged_in = false;
            pCount++;
            saveData();
            setColor(GREEN);
            printf("Passenger registered successfully!\n");
            setColor(RESET);
            playSuccess();
        } else if (c == 3) {
            char username[NAME_LEN], password[PASS_LEN];
            setColor(YELLOW);
            printf("---- UPDATE DRIVER ----\n");
            setColor(RESET);
            printf("Driver Username: "); scanf("%s", username);
            printf("Password: "); scanf("%s", password);
            int found = 0;
            for (int i = 0; i < dCount; i++) {
                if (strcmp(drivers[i].username, username) == 0 && strcmp(drivers[i].password, password) == 0) {
                    found = 1;
                    int choic;
                    do {
                        system("cls");
                        printHeader();
                        setColor(MAGENTA);
                        printf("Update Driver (%s):\n", drivers[i].username);
                        setColor(RESET);
                        printf("1. Change Username\n2. Change Password\n3. Increase Balance\n4. Change Status\n5. Change Location\n6. Back\nChoice: ");
                        scanf("%d", &choic);
                        if (choic == 1) {
                            printf("New Username: "); scanf("%s", drivers[i].username);
                        } else if (choic == 2) {
                            printf("New Password (4 digits): "); scanf("%s", drivers[i].password);
                            if (strlen(drivers[i].password) != 4) {
                                setColor(RED);
                                printf("Invalid password!\n");
                                setColor(RESET);
                                playError();
                                continue;
                            }
                        } else if (choic == 3) {
                            float inc;
                            printf("Amount to Increase: "); scanf("%f", &inc);
                            drivers[i].balance += inc;
                        } else if (choic == 4) {
                            printf("New Status (block/unblock): "); scanf("%s", drivers[i].status);
                        } else if (choic == 5) {
                            printf("New Location: "); scanf("%s", drivers[i].location);
                        } else if (choic == 6) break;
                        saveData();
                        setColor(GREEN);
                        printf("Update successful!\n");
                        setColor(RESET);
                        playSuccess();
                    } while (choic != 6);
                    break;
                }
            }
            if (!found) {
                setColor(RED);
                printf("Driver not found!\n");
                setColor(RESET);
                playError();
            }
        } else if (c == 4) {
            char username[NAME_LEN], password[PASS_LEN];
            setColor(YELLOW);
            printf("---- UPDATE PASSENGER ----\n");
            setColor(RESET);
            printf("Passenger Username: "); scanf("%s", username);
            printf("Password: "); scanf("%s", password);
            int found = 0;
            for (int i = 0; i < pCount; i++) {
                if (strcmp(passengers[i].username, username) == 0 && strcmp(passengers[i].password, password) == 0) {
                    found = 1;
                    int choic;
                    do {
                        system("cls");
                        printHeader();
                        setColor(MAGENTA);
                        printf("Update Passenger (%s):\n", passengers[i].username);
                        setColor(RESET);
                        printf("1. Change Username\n2. Change Password\n3. Increase Balance\n4. Change Status\n5. Change Location\n6. Back\nChoice: ");
                        scanf("%d", &choic);
                        if (choic == 1) {
                            printf("New Username: "); scanf("%s", passengers[i].username);
                        } else if (choic == 2) {
                            printf("New Password (4 digits): "); scanf("%s", passengers[i].password);
                            if (strlen(passengers[i].password) != 4) {
                                setColor(RED);
                                printf("Invalid password!\n");
                                setColor(RESET);
                                playError();
                                continue;
                            }
                        } else if (choic == 3) {
                            float inc;
                            printf("Amount to Increase: "); scanf("%f", &inc);
                            passengers[i].balance += inc;
                        } else if (choic == 4) {
                            printf("New Status (None/Waiting/inRide): "); scanf("%s", passengers[i].status);
                        } else if (choic == 5) {
                            printf("New Location: "); scanf("%s", passengers[i].location);
                        } else if (choic == 6) break;
                        saveData();
                        setColor(GREEN);
                        printf("Update successful!\n");
                        setColor(RESET);
                        playSuccess();
                    } while (choic != 6);
                    break;
                }
            }
            if (!found) {
                setColor(RED);
                printf("Passenger not found!\n");
                setColor(RESET);
                playError();
            }
        } else if (c == 5) {
            system("cls");
            printHeader();
            setColor(CYAN);
            printf("=== ALL DRIVERS ===\n");
            setColor(RESET);
            for (int i = 0; i < dCount; i++) {
                printf("User: %-15s | Pass: %-4s | ID: %-4d | Status: %-7s | Bal: %-6.2f | Trips: %-3d | Loc: %-15s\n",
                       drivers[i].username, drivers[i].password, drivers[i].id, drivers[i].status,
                       drivers[i].balance, drivers[i].trips, drivers[i].location);
            }
        } else if (c == 6) {
            system("cls");
            printHeader();
            setColor(CYAN);
            printf("=== ALL PASSENGERS ===\n");
            setColor(RESET);
            for (int i = 0; i < pCount; i++) {
                printf("User: %-15s | Pass: %-4s | ID: %-4d | Status: %-7s | Bal: %-6.2f | Trips: %-3d | Loc: %-15s\n",
                       passengers[i].username, passengers[i].password, passengers[i].id, passengers[i].status,
                       passengers[i].balance, passengers[i].trips, passengers[i].location);
            }
        } else if (c == 7) {
            system("cls");
            printHeader();
            setColor(CYAN);
            printf("=== ALL RIDES ===\n");
            setColor(RESET);
            for (int i = 0; i < ride_count; i++) {
                printf("Ride %-3d | Pass: %-3d | Driv: %-3d | From: %-15s → To: %-15s | Fare: %-6.2f | Completed: %s\n",
                       rides[i].id, rides[i].passenger_id, rides[i].driver_id,
                       rides[i].pickup, rides[i].destination, rides[i].fare,
                       rides[i].completed ? "Yes" : "No");
            }
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    } while (c != 8);
}

// ───────────────────────────────────────────────
// Driver Login and Menu
int driverLogin() {
    char username[NAME_LEN], password[PASS_LEN];
    system("cls");
    printHeader();
    setColor(YELLOW);
    printf("=== DRIVER LOGIN ===\n");
    setColor(RESET);
    printf("Username: "); scanf("%s", username);
    printf("Password: "); scanf("%s", password);
    for (int i = 0; i < dCount; i++) {
        if (strcmp(drivers[i].username, username) == 0 &&
            strcmp(drivers[i].password, password) == 0 &&
            strcmp(drivers[i].status, "unblock") == 0) {
            drivers[i].is_logged_in = true;
            setColor(GREEN);
            printf("Login successful! Welcome, %s.\n", username);
            setColor(RESET);
            playSuccess();
            return i;
        }
    }
    setColor(RED);
    printf("Invalid credentials or blocked! Contact admin.\n");
    setColor(RESET);
    playError();
    return -1;
}

void driverMenu(int driver_idx) {
    int c;
    do {
        system("cls");
        printHeader();
        setColor(MAGENTA);
        printf("=== DRIVER MENU (%s) ===\n", drivers[driver_idx].username);
        setColor(RESET);
        printf("1. View Wallet Balance\n");
        printf("2. Accept a Ride\n");
        printf("3. Manage Active Rides\n");
        printf("4. Change Password\n");
        printf("5. Change Status\n");
        printf("6. Change Location\n");
        printf("7. Back\n");
        printf("Choice: ");
        scanf("%d", &c);

        if (c == 1) {
            setColor(GREEN);
            printf("Balance: %.2f\n", drivers[driver_idx].balance);
            setColor(RESET);
        } else if (c == 2) {
            system("cls");
            printHeader();
            setColor(YELLOW);
            printf("=== WAITING PASSENGERS (Near %s) ===\n", drivers[driver_idx].location);
            setColor(RESET);
            bool has_waiting = false;
            for (int j = 0; j < pCount; j++) {
                if (strcmp(passengers[j].status, "Waiting") == 0 &&
                    strcmp(passengers[j].location, drivers[driver_idx].location) == 0) {
                    has_waiting = true;
                    printf("User: %-15s | ID: %-4d | Bal: %-6.2f | Loc: %-15s\n",
                           passengers[j].username, passengers[j].id, passengers[j].balance, passengers[j].location);
                }
            }
            if (!has_waiting) {
                setColor(YELLOW);
                printf("No waiting passengers nearby.\n");
                setColor(RESET);
            } else {
                char p_username[NAME_LEN];
                printf("Enter Passenger Username to Accept: ");
                scanf("%s", p_username);
                int pass_idx = -1;
                for (int j = 0; j < pCount; j++) {
                    if (strcmp(passengers[j].username, p_username) == 0 &&
                        strcmp(passengers[j].status, "Waiting") == 0 &&
                        passengers[j].balance >= 10.0 &&
                        strcmp(passengers[j].location, drivers[driver_idx].location) == 0) {
                        pass_idx = j;
                        break;
                    }
                }
                if (pass_idx != -1) {
                    if (ride_count >= MAX_RIDES) {
                        setColor(RED);
                        printf("Ride limit reached!\n");
                        setColor(RESET);
                        playError();
                        continue;
                    }
                    struct ride *r = &rides[ride_count];
                    r->id = ride_count + 1;
                    r->passenger_id = passengers[pass_idx].id;
                    r->driver_id = drivers[driver_idx].id;
                    strcpy(r->pickup, passengers[pass_idx].location);
                    printf("Enter Destination: ");
                    scanf("%s", r->destination);
                    printf("Enter Fare: ");
                    scanf("%f", &r->fare);
                    r->completed = false;
                    strcpy(passengers[pass_idx].status, "inRide");
                    ride_count++;
                    saveData();
                    setColor(GREEN);
                    printf("Ride accepted! ID: %d\n", r->id);
                    setColor(RESET);
                    playRideBooked();
                } else {
                    setColor(RED);
                    printf("Invalid username, low balance, or not waiting!\n");
                    setColor(RESET);
                    playError();
                }
            }
        } else if (c == 3) {
            system("cls");
            printHeader();
            setColor(YELLOW);
            printf("=== ACTIVE RIDES ===\n");
            setColor(RESET);
            bool has_rides = false;
            for (int j = 0; j < ride_count; j++) {
                if (rides[j].driver_id == drivers[driver_idx].id && !rides[j].completed) {
                    has_rides = true;
                    printf("Ride %-3d | Pass: %-3d | From: %-15s → To: %-15s | Fare: %-6.2f\n",
                           rides[j].id, rides[j].passenger_id, rides[j].pickup, rides[j].destination, rides[j].fare);
                    char yn;
                    printf("Complete Ride? (y/n): ");
                    scanf(" %c", &yn);
                    if (yn == 'y' || yn == 'Y') {
                        rides[j].completed = true;
                        for (int k = 0; k < pCount; k++) {
                            if (passengers[k].id == rides[j].passenger_id) {
                                passengers[k].balance -= rides[j].fare;
                                passengers[k].trips++;
                                strcpy(passengers[k].status, "None");
                                break;
                            }
                        }
                        drivers[driver_idx].balance += rides[j].fare;
                        drivers[driver_idx].trips++;
                        saveData();
                        setColor(GREEN);
                        printf("Ride completed!\n");
                        setColor(RESET);
                        playSuccess();
                    }
                }
            }
            if (!has_rides) {
                printf("No active rides.\n");
            }
        } else if (c == 4) {
            char oldpass[PASS_LEN], newpass[PASS_LEN];
            printf("Old Password: "); scanf("%s", oldpass);
            if (strcmp(drivers[driver_idx].password, oldpass) == 0) {
                printf("New Password (4 digits): "); scanf("%s", newpass);
                if (strlen(newpass) != 4) {
                    setColor(RED);
                    printf("Invalid password!\n");
                    setColor(RESET);
                    playError();
                    continue;
                }
                strcpy(drivers[driver_idx].password, newpass);
                saveData();
                setColor(GREEN);
                printf("Password changed!\n");
                setColor(RESET);
                playSuccess();
            } else {
                setColor(RED);
                printf("Invalid old password!\n");
                setColor(RESET);
                playError();
            }
        } else if (c == 5) {
            printf("Current Status: %s\n", drivers[driver_idx].status);
            printf("New Status (block/unblock): "); scanf("%s", drivers[driver_idx].status);
            saveData();
        } else if (c == 6) {
            printf("New Location: "); scanf("%s", drivers[driver_idx].location);
            saveData();
            setColor(GREEN);
            printf("Location updated!\n");
            setColor(RESET);
            playSuccess();
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    } while (c != 7);
}

// ───────────────────────────────────────────────
// Passenger Login and Menu
int passengerLogin() {
    char username[NAME_LEN], password[PASS_LEN];
    system("cls");
    printHeader();
    setColor(YELLOW);
    printf("=== PASSENGER LOGIN ===\n");
    setColor(RESET);
    printf("Username: "); scanf("%s", username);
    printf("Password: "); scanf("%s", password);
    for (int i = 0; i < pCount; i++) {
        if (strcmp(passengers[i].username, username) == 0 &&
            strcmp(passengers[i].password, password) == 0) {
            passengers[i].is_logged_in = true;
            setColor(GREEN);
            printf("Login successful! Welcome, %s.\n", username);
            setColor(RESET);
            playSuccess();
            return i;
        }
    }
    setColor(RED);
    printf("Invalid credentials!\n");
    setColor(RESET);
    playError();
    return -1;
}

void passengerMenu(int pass_idx) {
    int c;
    do {
        system("cls");
        printHeader();
        setColor(MAGENTA);
        printf("=== PASSENGER MENU (%s) ===\n", passengers[pass_idx].username);
        setColor(RESET);
        printf("1. View Wallet Balance\n");
        printf("2. Request a Ride\n");
        printf("3. Cancel Ride\n");
        printf("4. Change Password\n");
        printf("5. Change Location\n");
        printf("6. Back\n");
        printf("Choice: ");
        scanf("%d", &c);

        if (c == 1) {
            setColor(GREEN);
            printf("Balance: %.2f\n", passengers[pass_idx].balance);
            setColor(RESET);
        } else if (c == 2) {
            if (strcmp(passengers[pass_idx].status, "None") == 0 && passengers[pass_idx].balance >= 10.0) {
                strcpy(passengers[pass_idx].status, "Waiting");
                saveData();
                setColor(GREEN);
                printf("Ride request sent! Waiting for driver...\n");
                setColor(RESET);
                playRideBooked();
            } else {
                setColor(RED);
                printf("Cannot request: Active ride or low balance!\n");
                setColor(RESET);
                playError();
            }
        } else if (c == 3) {
            if (strcmp(passengers[pass_idx].status, "Waiting") == 0) {
                strcpy(passengers[pass_idx].status, "None");
                saveData();
                setColor(GREEN);
                printf("Ride request canceled!\n");
                setColor(RESET);
                playSuccess();
            } else {
                setColor(RED);
                printf("No active request to cancel!\n");
                setColor(RESET);
                playError();
            }
        } else if (c == 4) {
            char oldpass[PASS_LEN], newpass[PASS_LEN];
            printf("Old Password: "); scanf("%s", oldpass);
            if (strcmp(passengers[pass_idx].password, oldpass) == 0) {
                printf("New Password (4 digits): "); scanf("%s", newpass);
                if (strlen(newpass) != 4) {
                    setColor(RED);
                    printf("Invalid password!\n");
                    setColor(RESET);
                    playError();
                    continue;
                }
                strcpy(passengers[pass_idx].password, newpass);
                saveData();
                setColor(GREEN);
                printf("Password changed!\n");
                setColor(RESET);
                playSuccess();
            } else {
                setColor(RED);
                printf("Invalid old password!\n");
                setColor(RESET);
                playError();
            }
        } else if (c == 5) {
            printf("New Location: "); scanf("%s", passengers[pass_idx].location);
            saveData();
            setColor(GREEN);
            printf("Location updated!\n");
            setColor(RESET);
            playSuccess();
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    } while (c != 6);
}

// ───────────────────────────────────────────────
// Main Function
int main() {
    loadData();
    int choice;
    int cur_driver = -1;
    int cur_passenger = -1;
    do {
        system("cls");
        printHeader();
        setColor(MAGENTA);
        printf("=== MAIN MENU ===\n");
        setColor(RESET);
        printf("1. Admin Login\n");
        printf("2. Driver Login\n");
        printf("3. Passenger Login\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char user[NAME_LEN], pass[PASS_LEN];
            system("cls");
            printHeader();
            setColor(YELLOW);
            printf("=== ADMIN LOGIN ===\n");
            setColor(RESET);
            printf("Username: "); scanf("%s", user);
            printf("Password: "); scanf("%s", pass);
            if (strcmp(user, "admin") == 0 && strcmp(pass, "2026") == 0) {
                setColor(GREEN);
                printf("Admin login successful!\n");
                setColor(RESET);
                playSuccess();
                adminMenu();
            } else {
                setColor(RED);
                printf("Invalid admin credentials!\n");
                setColor(RESET);
                playError();
            }
        } else if (choice == 2) {
            cur_driver = driverLogin();
            if (cur_driver != -1) {
                driverMenu(cur_driver);
                drivers[cur_driver].is_logged_in = false;
            }
        } else if (choice == 3) {
            cur_passenger = passengerLogin();
            if (cur_passenger != -1) {
                passengerMenu(cur_passenger);
                passengers[cur_passenger].is_logged_in = false;
            }
        } else if (choice == 4) {
            setColor(YELLOW);
            printf("Exiting system. Goodbye!\n");
            setColor(RESET);
            saveData();
            return 0;
        }
        printf("\nPress Enter to continue...");
        getchar(); getchar();
    } while (choice != 4);
    return 0;
}