#ifndef HEALTH_SYSTEM_FUNCTIONS_H
#define HEALTH_SYSTEM_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>


/*---------------------------------TYPE DEFINITIONS------------------------------*/



/*structure of a linked lists cell will be used  as a queue of consultations inserted based on priority*/

typedef struct consultation consultation ;
 struct consultation
 {
    char Employee_ID[9];
    char Employee_Name[50];
    char Consultation_Time[6];         /*in the format HH:MM*/
    char Consultation_Reason[21] ;


 };

typedef struct cell typeCell;           /*type of an element in the list*/


struct cell {
    consultation conslt;
    typeCell *addr;                      /*address of next*/
    int priority ;                       /*priority of the appointement*/
};


/*dynamic implementation of the queue*/
struct typeQueue
{
    typeCell *h ;                          /*pointer to the head of the queue*/
    typeCell *t ;                          /*pointer to the tail of the queue*/
};
typedef struct typeQueue typeQueue ;       /*define queue as a type */


struct emp {
    char id[9];
    int consult_num;
    char last_consult[11];
    char return_work[11];
    char name[35];
    char history[5][25];
    struct emp *adr;
};

//type of a cell in the linked list
typedef struct emp emp ;

//global variables
extern int processed_count ;        //to keep track of the number of appointments processed during the day
extern int maximum ;                    //maximum number of appointments per day (to allow the user to modify it )

/*-------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------Functions Headers----------------------------------------------------------*/

/*---------------------linked lists model---------------------*/

/*allocate a memory space return its address in p*/
void Allocate(typeCell **p);

/*gives the address of the next cell after p*/
typeCell* Next(typeCell *p);

/*assigns the consultation field into *k an  element of the list */
void Ass_consultation(typeCell **k , consultation c);

/*assigns the address field into *k an  element of the list */
void Ass_addr(typeCell **p , typeCell *q);

/*displays an element of type consultation*/
void display_consultation(typeCell k);


/*returns the consultation field inside the list element k*/
consultation consultation_info(typeCell *k);

/*-----------------helper functions ------------------------------*/

/*returns the priority of consultation reasons from 1 to 3 . returns -1 for invalid reasons*/
int reason_priority(char reason[21]);

//returns 1 if the ID is unique in the list and 0 else
int unique_ID(emp* head, char *ID);

//clear the screen
void clear_screen();

// clear input from the file from newlines 
void flush_input();
/*displays the queue*/
void display_queue(typeQueue Q);

/*reads data from text file given by a pointer into a queue*/
void read_file_to_queue(FILE *file,typeQueue *Q);

//prints the content of Q into file
void write_queue_to_file(FILE *file , typeQueue Q);

 //clear input buffer
 void clear();

/*converts time from int to string */
char* time_string(int time);

/*converts time from a string to an int HHMM format , returns -1 if an invalid time is passed*/
int time_int(char* str_time);

//gets the current date from the system and converts it into a string DD/MM/YYYY
char* get_date(int *day ,int *month , int *year);

//gets the current time from the system and converts it into a string HHhMM
char* get_time();

//free Queue
void free_Q(typeQueue *Q);

//returns in p and q the address of the cell containing the employye_id = ID and the previous cell respectivly
void access_consultation(typeQueue Q , char* ID, typeCell** q, typeCell** p);

//assignes the fields of src to dest
void Ass_consultation_type(consultation *dest , consultation src);

//counts the number of appointments in the queue for the day
int size_of_queue(typeQueue Q);

//return 1 if the queue has more than max elements
int full_queue_day(typeQueue Q);

//returns in p the address of the last element with priority greater or equal than prio , and its previous in q
void access_by_priority(typeQueue Q , int prio , typeCell **p ,typeCell **q);

//assigns the available visit time based on priority to c
int assign_time(typeQueue Q, consultation *c, int current_time);


/*---------------------------------Queue's functionalities-------------------*/

/* deletes an appointment of the queue given the employee iD returns 1 if the appointment was found and 0 else*/
int cancel_appointment(typeQueue *Q , char* ID);

//add an appointment from the user's input
void add_appointment(typeQueue *Q , typeQueue *Next_day_Q);


//reschedules by moving least priority appointment to next day
void reschedule(typeQueue *Q,typeQueue *Next_day_Q,consultation c);

//automatically schedules return to work appointments and periodic examinations to the next day
void schedule_periodic_return(emp *head , typeQueue *Next_day_Q ,char* current_date ,int current_time);


//closes an appointment appointment and update the corresponding employee record returns 1 if successful
int close_appointment(typeQueue *Q,emp *head);


//reschedules an appointment given its ID from the stdin to next day
void reschedule_manual(typeQueue *Q , typeQueue *Next_day_queue);


/*-------------------------------Queue's abstract machine------------------*/

//initialize the queue
typeQueue createQueue();

/*returns 1 if the list is empty and 0 otherwise*/
int emptyQueue(typeQueue Q);

/*inserts based on priority ( the queue is ordered)*/
void enqueue(typeQueue *Q , consultation new_conslt);

//dequeue the highest priority element in the queue and store the information in dequeued_consultation
void dequeue(typeQueue *Q , consultation *dequeued_conslt );
/*------------------------------------------------------------------------------------------------*/

/* Employee Record Operations */

struct emp* createEmp();

struct emp* findEmp(struct emp *h, char id[]);

void updateHistory(struct emp *h, char id[], char reason[]);

void changeConsultNum(int n, char id[], struct emp *h);

void changeLastConsult(char lastConsult[], char id[], struct emp *h);

void changeReturnWork(char returnWork[], char id[], struct emp *h);

void updateEmp(struct emp *h, char id[]);

void deleteEmp(struct emp **h, char deleted_id[]);

// adds a new employee to the linked list by collecting user input for all fields
struct emp* addEmp(struct emp *h);

void readLine(struct emp *p, char *line);

struct emp* loadEmp(FILE *f);

void printEmp(struct emp *p);

void printInGrp(struct emp *h);

void saveEmp(struct emp *h, FILE *f);

void addNewEmp(consultation *q, struct emp **h);

void subAutoUpdate(struct emp *h, char id[], char reason[], char date[]);

void updateSingleEmp(struct emp **h, typeQueue *q, char id[], char date[]);

#endif
