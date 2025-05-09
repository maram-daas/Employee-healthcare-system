# Occupational Health Management System

A cross-platform C based application for managing medical consultations and employee health records in a workplace environment.

## Features

- Appointment queue system for daily and next-day consultations
- Employee record management using a linked list (add, update, delete, find)
- Automatic scheduling of periodic and return-to-work medical consultations
- saving/reading employees/consultations data from files for storage reasons. 
- interactive menu interface
- Dynamic memory allocation and custom queue implementation.
- cross-platform

## What we used

- Language: C
- Tools: GCC, Standard C Libraries
- Structures: Linked lists and priority queues

## Files

- `main.c`: menu interface
- `health_system_functions.h/c`: Helper functions for appointments and employees (header+source file)
- `EmpRecords.txt`: Employee data file (you can add employees but make sure to keep the same structure)
- `Consultations.txt`: Appointment queue data file (you can add consultations but make sure to keep the same structure)

## Authors

- **Maram Daas**  
- **Hibatallah Khadir** – [@hiba-khadir](https://github.com/hiba-khadir)

> Built as a collaboration project.

## Note

The file structure is essential for the program to function properly. Please maintain the exact formatting. If you want to leave a field empty (in the file), use ;; in its place to preserve the correct structure.

## License

This project is licensed under the [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0).
