#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "health_system_functions.h"


int main() {
    clear_screen(); // Clear screen at start

    // Print welcome frame
    printf("+-------------------------------------------------+\n");
    printf("|                                                 |\n");
    printf("|        +++ Occupational_Health_System +++       |\n");
    printf("|                                                 |\n");
    printf("|                Made by Maram Daas               |\n");
    printf("|                                                 |\n");
    printf("|             ~~ Welcome dear user ~~             |\n");
    printf("|                                                 |\n");
    printf("+-------------------------------------------------+\n");

    printf("\nPress enter to continue...\n");
    getchar(); // wait for user input
    clear_screen();

    // Files for saving/loading data
    FILE *appointmentFile, *nextDayFile, *employeeFile;

    // Initialize queues for appointments
    typeQueue todayQueue = createQueue();
    typeQueue nextDayQueue = createQueue();

    // Initialize employee records linked list
    emp *employeeRecords = NULL;

    // Temporary variables
    consultation tempConsultation;
    char userInput[10];
    int choice;
    int day, month, year;
    char *currentDate = get_date(&day, &month, &year);
    int currentTimeInt = time_int(get_time());

    // Try to load existing data
    printf("+-------------------------------------------------+\n");
    printf("|              LOADING SYSTEM DATA                |\n");
    printf("+-------------------------------------------------+\n");

    // Load employee records
    employeeFile = fopen("EmpRecords.txt", "r");
    if (employeeFile != NULL) {

        employeeRecords = loadEmp(employeeFile);

        fclose(employeeFile);
        printf("| Employee records loaded successfully.           |\n");
    } else {
        printf("| No existing employee records found.             |\n");
    }

    // Load today's appointments
    appointmentFile = fopen("Consultations.txt", "r");
    if (appointmentFile != NULL) {
        read_file_to_queue(appointmentFile, &todayQueue);
        fclose(appointmentFile);
        printf("| Today's appointments loaded successfully.       |\n");
    } else {
        printf("| No existing appointments found for today.       |\n");
    }

    printf("+-------------------------------------------------+\n");

    printf("\nPress enter to continue...\n");
    getchar(); // wait for user input
    clear_screen();

    // Main menu loop
    do {
        // Display current status in frame
        printf("+-------------------------------------------------+\n");
        printf("|               SYSTEM INFORMATION                |\n");
        printf("+-------------------------------------------------+\n");
        printf("| Current date: %-32s  |\n", currentDate);
        printf("| Current time: %-32s  |\n", get_time());
        printf("| Appointments processed: %-24d|\n", processed_count);
        printf("| Maximum appointments: %-25d |\n", maximum);
        printf("+-------------------------------------------------+\n");

        // Main menu
        printf("\n+-------------------------------------------------+\n");
        printf("|                   MAIN MENU                     |\n");
        printf("+-------------------------------------------------+\n");
        printf("| 1. Display today's appointment queue            |\n");
        printf("| 2. Display next day's appointment queue         |\n");
        printf("| 3. Add new appointment                          |\n");
        printf("| 4. Cancel appointment                           |\n");
        printf("| 5. Process next appointment                     |\n");
        printf("| 6. Reschedule appointment to next day           |\n");
        printf("| 7. Check periodic & return-to-work appointments |\n");
        printf("| 8. Employee record management                   |\n");
        printf("| 9. Save and exit                                |\n");
        printf("+-------------------------------------------------+\n");
        printf("Enter your choice (1-9): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            flush_input();
            continue;
        }
        flush_input();
        clear_screen(); // Clear screen after each menu selection

        switch (choice) {
            case 1:
                printf("+-------------------------------------------------+\n");
                printf("|          TODAY'S APPOINTMENT QUEUE              |\n");
                printf("+-------------------------------------------------+\n");
                if (emptyQueue(todayQueue)) {
                    printf("| No appointments scheduled for today.           |\n");
                    printf("+-------------------------------------------------+\n");
                } else {
                    printf("+-------------------------------------------------+\n");
                    display_queue(todayQueue);
                }
                break;

            case 2:
                printf("+-------------------------------------------------+\n");
                printf("|          NEXT DAY'S APPOINTMENT QUEUE           |\n");
                printf("+-------------------------------------------------+\n");
                if (emptyQueue(nextDayQueue)) {
                    printf("| No appointments scheduled for next day.        |\n");
                    printf("+-------------------------------------------------+\n");
                } else {
                    printf("+-------------------------------------------------+\n");
                    display_queue(nextDayQueue);
                }
                break;

            case 3:
                printf("+-------------------------------------------------+\n");
                printf("|               ADD NEW APPOINTMENT               |\n");
                printf("+-------------------------------------------------+\n");
                add_appointment(&todayQueue, &nextDayQueue);
                break;

            case 4:
                printf("+-------------------------------------------------+\n");
                printf("|               CANCEL APPOINTMENT                |\n");
                printf("+-------------------------------------------------+\n");
                printf("Enter employee ID to cancel appointment: ");
                scanf("%s", userInput);
                flush_input();
                int cancel ;

                cancel = cancel_appointment(&todayQueue, userInput);
                if (cancel)  //appointment was found
                {
                    printf("+-------------------------------------------------+\n");
                    printf("|                Appointment canceled             |\n");
                    printf("+-------------------------------------------------+\n");
                }

                break;

            case 5:
                printf("+-------------------------------------------------+\n");
                printf("|             PROCESS NEXT APPOINTMENT             |\n");
                printf("+-------------------------------------------------+\n");
                if (emptyQueue(todayQueue)) {
                    printf("| No appointments to process.                    |\n");
                    printf("+-------------------------------------------------+\n");
                } else {
                    close_appointment(&todayQueue, employeeRecords);
                    Sleep(1000);         // delay before exiting to menue
                }
                break;

            case 6:
                printf("+-------------------------------------------------+\n");
                printf("|             RESCHEDULE APPOINTMENT              |\n");
                printf("+-------------------------------------------------+\n");
                reschedule_manual(&todayQueue, &nextDayQueue);
                break;

            case 7:
                printf("+-------------------------------------------------+\n");
                printf("|          CHECK AUTOMATIC APPOINTMENTS           |\n");
                printf("+-------------------------------------------------+\n");
                printf("| Checking for periodic visits and return-to-work  |\n");
                printf("| appointments...                                  |\n");
                schedule_periodic_return(employeeRecords, &nextDayQueue, currentDate, currentTimeInt);
                printf("| Check complete. View next day's queue            |\n");
                printf("| to see any new appointments.                     |\n");
                printf("+-------------------------------------------------+\n");
                break;

            case 8:
                do {
                    printf("+-------------------------------------------------+\n");
                    printf("|           EMPLOYEE RECORD MANAGEMENT            |\n");
                    printf("+-------------------------------------------------+\n");
                    printf("| 1. View all employee records                    |\n");
                    printf("| 2. Find employee by ID                          |\n");
                    printf("| 3. Add new employee                             |\n");
                    printf("| 4. Update employee information                  |\n");
                    printf("| 5. Delete employee                              |\n");
                    printf("| 6. Return to main menu                          |\n");
                    printf("+-------------------------------------------------+\n");
                    printf("Enter your choice (1-6): ");

                    if (scanf("%d", &choice) != 1) {
                        printf("Invalid input. Please enter a number.\n");
                        flush_input();
                        continue;
                    }
                    flush_input();
                    clear_screen(); // Clear screen after submenu selection

                    switch (choice) {
                        case 1:
                            printf("+-------------------------------------------------+\n");
                            printf("|             ALL EMPLOYEE RECORDS                |\n");
                            printf("+-------------------------------------------------+\n");
                            if (employeeRecords == NULL) {
                                printf("| No employee records found.                      |\n");
                                printf("+-------------------------------------------------+\n");
                            } else {
                                printInGrp(employeeRecords);
                                flush_input();
                                getchar();
                            }
                            break;

                        case 2:
                            printf("+-------------------------------------------------+\n");
                            printf("|                 FIND EMPLOYEE                   |\n");
                            printf("+-------------------------------------------------+\n");
                            printf("Enter employee ID: ");
                            scanf("%s", userInput);
                            flush_input();

                            emp *foundEmployee = findEmp(employeeRecords, userInput);
                            if (foundEmployee != NULL) {
                                printf("+-------------------------------------------------+\n");
                                printf("|               EMPLOYEE FOUND                    |\n");
                                printf("+-------------------------------------------------+\n");
                                printEmp(foundEmployee);
                            } else {
                                printf("+-------------------------------------------------+\n");
                                printf("| Employee with ID %-27s |\n", userInput);
                                printf("| not found.                                      |\n");
                                printf("+-------------------------------------------------+\n");
                            }
                            break;

                        case 3:
                            printf("+-------------------------------------------------+\n");
                            printf("|               ADD NEW EMPLOYEE                  |\n");
                            printf("+-------------------------------------------------+\n");
                            employeeRecords = addEmp(employeeRecords);
                            printf("+-------------------------------------------------+\n");
                            printf("| Employee added successfully.                    |\n");
                            printf("+-------------------------------------------------+\n");
                            break;

                        case 4:
                            printf("+-------------------------------------------------+\n");
                            printf("|         UPDATE EMPLOYEE INFORMATION             |\n");
                            printf("+-------------------------------------------------+\n");
                            printf("Enter employee ID to update: ");
                            scanf("%s", userInput);
                            flush_input();

                            updateEmp(employeeRecords, userInput);
                            break;

                        case 5:
                            printf("+-------------------------------------------------+\n");
                            printf("|               DELETE EMPLOYEE                   |\n");
                            printf("+-------------------------------------------------+\n");
                            printf("Enter employee ID to delete: ");
                            scanf("%s", userInput);
                            flush_input();

                            deleteEmp(&employeeRecords, userInput);
                            break;

                        case 6:
                            printf("+-------------------------------------------------+\n");
                            printf("| Returning to main menu...                       |\n");
                            printf("+-------------------------------------------------+\n");
                            Sleep(1000);
                            break;

                        default:
                            printf("+-------------------------------------------------+\n");
                            printf("| Invalid choice. Please try again.               |\n");
                            printf("+-------------------------------------------------+\n");
                    }

                    if (choice != 6) {
                        printf("\nPress enter to continue...\n");
                        getchar(); // wait for user input
                        clear_screen(); // Clear screen before returning to employee submenu
                    }
                } while (choice != 6);
                choice = 0; // Reset choice to continue main menu
                clear_screen(); // Clear screen before returning to main menu
                break;

            case 9:
                printf("+-------------------------------------------------+\n");
                printf("|            SAVING DATA AND EXITING              |\n");
                printf("+-------------------------------------------------+\n");

                // Save next day's appointments
                nextDayFile = fopen("Consultations.txt", "w");
                if (nextDayFile != NULL) {
                    write_queue_to_file(nextDayFile, nextDayQueue);
                    fclose(nextDayFile);
                    printf("| Next day's appointments saved.                  |\n");
                } else {
                    printf("| Error: Could not save next day's appointments. |\n");
                }

                // Save employee records
                employeeFile = fopen("EmpRecords.txt", "w");
                if (employeeFile != NULL) {
                    saveEmp(employeeRecords, employeeFile);
                    fclose(employeeFile);
                    printf("| Employee records saved.                         |\n");
                } else {
                    printf("| Error: Could not save employee records.        |\n");
                }

                printf("| Exiting program...                              |\n");
                printf("+-------------------------------------------------+\n");
                break;

            default:
                printf("+-------------------------------------------------+\n");
                printf("| Invalid choice. Please try again.               |\n");
                printf("+-------------------------------------------------+\n");
        }

        if (choice != 9) {
            printf("\nPress enter to continue...\n");
            getchar(); // wait for user input
            clear_screen(); // Clear screen before returning to main menu
        }
    } while (choice != 9);

    // Free memory before exiting
    free_Q(&todayQueue);
    free_Q(&nextDayQueue);

    // Free employee records
    emp *current = employeeRecords;
    emp *next;
    while (current != NULL) {
        next = current->adr;
        free(current);
        current = next;
    }

    return 0;
}
