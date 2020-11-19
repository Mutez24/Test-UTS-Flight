
/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Clément MUTEZ
 * Student ID: 13689082
 * Date of submission:
 * A brief statement on what you could achieve (less than 50 words):
 *
 *
 * A brief statement on what you could NOT achieve (less than 50 words):
 *
 *
 *******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
 *******************************************************************************/
#include <stdio.h>
/*printf, scanf, fscanf, fprintf*/
#include <string.h>
/*strcmp, strcpy, strlen*/
#include <stdlib.h>
/*I don't use it*/
/*******************************************************************************
 * List preprocessing directives - you may define your own.
 *******************************************************************************/
#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
 *******************************************************************************/
struct date_time /*to create the structure data time*/
{
    int month;
    int day;
    int hour;
    int minute;
};
typedef struct date_time date_time_t;

struct flight /* to create the structure flight*/
{
    char flightcode[MAX_FLIGHTCODE_LEN+1];
    date_time_t departure_dt;
    char arrival_city[MAX_CITYCODE_LEN+1];
    date_time_t arrival_dt;
};
typedef struct flight flight_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
 *******************************************************************************/
void print_menu (void);
void printFlight(flight_t flight);
void displayFlight(flight_t tabFlight[], int tabFlightLenght);
int isGoodAnswer(int answer);
int isGoodFlightCode(char flightCode[]);
int isGoodTime(int month, int day, int hour, int minute);
int isGoodCity(char citycode[]);
flight_t addAFlight(void);
int isEqual(char answer[], char arrivalcity[]);
int saveTheFlight(flight_t tabflight[], char filename[], int tablenght);
void loadFlight(flight_t tabflight[], char filename[]);
/*******************************************************************************
 * Main
 *******************************************************************************/
int main(void)
{
    print_menu(); /*I just do the function print_menu, because all the menu is in it*/
    return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
 *******************************************************************************/
void print_menu (void)
{
    int answer, isgood, nbOfFlightAdd = 0, exits = 0;
    /*I initialiase my variable for this function*/
    /*-answer is store the answer of the user
     -isgood is to check if the answer is good, it means between 1-5
     -nbofflight is to store the number of flight that has been enter by the
     user, and to travel throught the tab of flight
     -exits is a variable that I use to know when my program has to stop*/
    flight_t flight;/* I initialize a flight that I will use in addflight*/
    flight_t tabflight[5];
    /* I initialize the tab of flight that I will use during the all menu
     (I will call it tab for the rest of the program)*/
    while (exits == 0)
    /* it means while the user don't want to exist the program*/
    {
        do
        {
            printf("\n"                  /*this is just the menu*/
                   "1. add a flight\n"
                   "2. display all flights to a destination\n"
                   "3. save the flights to the database file\n"
                   "4. load the flights from the database file\n"
                   "5. exit the program\n"
                   "Enter choice (number between 1-5)>\n");
            scanf("%d", &answer); /* to scan the answer of the user*/
            isgood = isGoodAnswer(answer);
            /* to check if the answer is between 1 and 5*/
            if (isgood == 1)
            {
                printf("Invalid choice\n");
                /*if the answer is not good I print the error message*/
            }
            
        }while (isgood == 1);
        /* it ask the questions (menu) while the answer is not good*/
        switch (answer)/*so the number is now good, I can put it in my switch*/
        {
            case 1:
                if (nbOfFlightAdd > 4)
                {
                    printf("Cannot add more flights - memory full\n");
                    /*this 'if' check if the user has already enter 5 flight
                     (so if there are already 5 flight in the tab*/
                }
                else
                {
                    flight = addAFlight();/*this function create a flight*/
                    tabflight[nbOfFlightAdd] = flight;
                    /*this add the flight that has just been created in the
                     tab flight, at the nbofflightadd index (it begins a 0)*/
                    nbOfFlightAdd++;
                    /*because if we are here, it means that a flight has been had*/
                }
                break;
            case 2:
                displayFlight(tabflight, nbOfFlightAdd);
                /*do the displayflight funtion*/
                break;
            case 3:
                saveTheFlight(tabflight, "database.txt", nbOfFlightAdd);
                /*save the flights from the tab in database.txt*/
                break;
            case 4:
                loadFlight(tabflight, "database.txt");
                /*read the flights from the data base, then put it in the tab*/
                break;
            case 5:
                exits = 1; /* to exit the while, consequently the programm*/
                break;
        }
    }
}
/*******************************************************************************
 * This function checks if the user enter a good answer in the main,
 * it means between 1-5
 * inputs:
 * - is the answer of the user
 * outputs:
 * - the result, 0 if good, 1 otherwise
 *******************************************************************************/
int isGoodAnswer(int answer)
{
    int isgood = 0;
    if (answer != 1 && answer != 2 && answer != 3 && answer != 4 && answer != 5)
    /*check if the answer is between 1-5*/
    {
        isgood = 1;
    }
    return isgood;/*return 0 if it is a good answer, 1 if it is not*/
}
/*******************************************************************************
 * This function checks if the user enter a good answer in the main,
 * it means between 1-5
 * inputs:
 * - is the answer of the user
 * outputs:
 * - the result, 0 if good, 1 otherwise
 *******************************************************************************/
flight_t addAFlight()/*function that create a flight*/
{
    flight_t flight; /*initialize the flight that I will return*/
    int isGoodA = 1;
    /*variable that I will use to check if the answer of the user is good*/
    do
    {
        char flightcode[100];/*to conserve the answer of the user*/
        printf("Enter flight code>\n");
        scanf("%s", flightcode);/*to conserve the answer of the user*/
        isGoodA = isGoodFlightCode(flightcode);
        /*function that check if tha answer is good, if it is it return 0,
         otherwhise it return 1*/
        if (isGoodA == 0)
        {
            strcpy(flight.flightcode, flightcode);
        }
        else
        {
            printf("Invalid input\n");/*if the answer is not good*/
        }
    }while (isGoodA == 1);/*while the answer is not good, continue to ask*/
    int isGoodB = 1;/*same as goodA*/
    printf("Enter departure info for the flight leaving SYD.\n");
    do
    {
        int month, day, hour, minute;/*to conserve the answer of the user*/
        printf("Enter month, date, hour and minute separated by spaces>\n");
        scanf("%d %d %d %d",&month, &day, &hour, &minute);
        /*to conserve the answer of the user*/
        isGoodB = isGoodTime(month, day, hour, minute);
        /*function that check if tha answer is good, if it is it return 0,
         otherwhise it return 1*/
        if (isGoodB == 0)
        {
            flight.departure_dt.day = day;
            /*so the flight departure day, month,
             hour and minute become the answer*/
            flight.departure_dt.month = month;
            flight.departure_dt.hour = hour;
            flight.departure_dt.minute = minute;
        }
        else
        {
            printf("Invalid input\n");/*if the answer is not good*/
        }
    }while (isGoodB == 1);/*while the answer is not good, continue to ask*/
    
    
    printf("Enter arrival city code>\n");
    scanf("%s", flight.arrival_city);/*to conserve the answer of the user*/
    
    int isGoodD = 1;/*same as goodA*/
    printf("Enter arrival info.\n");
    do
    {
        int month, day, hour, minute;/*to conserve the answer of the user*/
        printf("Enter month, date, hour and minute separated by spaces>\n");
        scanf("%d %d %d %d",&month, &day, &hour, &minute);
        /*to conserve the answer of the user*/
        isGoodD = isGoodTime(month, day, hour, minute);
        /*function that check if tha answer is good, if it is it return 0,
         otherwhise it return 1*/
        if (isGoodD == 0)
        {
            flight.arrival_dt.day = day;
            /*so the flight arrival day, month,
             hour and minute become the answer*/
            flight.arrival_dt.month = month;
            flight.arrival_dt.hour = hour;
            flight.arrival_dt.minute = minute;
        }
        else
        {
            printf("Invalid input\n");/*if the answer is not good*/
        }
    }while (isGoodD == 1);/*while the answer is not good, continue to ask*/
    return flight;/*return the flight that has just been created here*/
}

/*******************************************************************************
 * This function checks if the user enter a good answer in the main,
 * it means a good flight code, 2 letter uppercase and 1-4 numbers
 * inputs:
 * - is the answer of the user
 * outputs:
 * - the result, 0 if good, 1 otherwise
 *******************************************************************************/
int isGoodFlightCode(char flightCode[]) /*tell if the flight code that the
                                         user have enter is well written
                                         the input is hte answer of the user,
                                         the output is the result, 0 if good,
                                         1 otherwise*/
{
    int answer = 0, i;
    /*I initialize the answer to zero (good answer)
     then check with if loops if the enswer is wrong*/
    if (flightCode[0] < 65 || flightCode[0] > 90)
    /* ASCII of a letter in uppercase, so check if it is an uppercase letter*/
    {
        answer = 1;
        /*I begin at the index O so it's the first letter of the answer*/
    }
    if (flightCode[1] < 65 || flightCode[1] > 90)
    {
        answer = 1;/*then index 2 so it's the seconde letter of the answer*/
    }
    for (i = 2; i < strlen(flightCode); i++)
    {
        if (flightCode[i] < 48 || flightCode[i] > 57)
        /*ASCII of a number between O and 9, so check if it's a number*/
        {
            answer = 1;/*then from letter 3 to the size of the flightcode*/
        }
    }
    if (strlen(flightCode) < 3 || strlen(flightCode) > 6)
    /*check the size of the answer so that the user has enter
     between 1-4 numbers, and 2 letters*/
    {
        answer = 1;
    }
    return  answer;/*return 0 if good, otherwhise 1*/
}

/*******************************************************************************
 * This function checks if the user enter a good answer in the main,
 * it means a month between 1-12, day 1-31, hour 0-23, minute 0-59
 * inputs:
 * - is the answer of the user
 * outputs:
 * - the result, 0 if good, 1 otherwise
 *******************************************************************************/
int isGoodTime(int month, int day, int hour, int minute)
/*check if the answer is good*/
{
    int answer = 0;
    /*I initialize the answer to zero (good answer) then check with
     if loops if the enswer is wrong*/
    if (month < 1 || month > 12 || day < 1 || day > 31 || hour < 0 || hour > 23
        || minute < 0 || minute > 59)
    {
        answer = 1;
        /*check if month is between 1-12, day between 1-31, hour between 0-23,
         minute between 0-59*/
    }
    return  answer;/*return 0 if good, otherwhise 1*/
}

/*******************************************************************************
 * This function print a flight
 * inputs:
 * - flight we want to print
 * outputs:
 * - none
 *******************************************************************************/
void printFlight(flight_t flight)/*function that print a flight,
                                  we assume that all the condition are good before calling this function*/
{
    printf("%-6s SYD %02d-%02d %02d:%02d %-3s %02d-%02d %02d:%02d",
           flight.flightcode, flight.departure_dt.month, flight.departure_dt.day,
           flight.departure_dt.hour, flight.departure_dt.minute, flight.arrival_city,
           flight.arrival_dt.month, flight.arrival_dt.day, flight.arrival_dt.hour,
           flight.arrival_dt.minute);/*print the flightcode*/
}

/*******************************************************************************
 * This function display the flight for the case 2
 * inputs:
 * - the tab that contain all the flights and the size of the tab, it
 *   means the number of flight that has been enter by the user
 * outputs:
 * - none
 *******************************************************************************/
void displayFlight(flight_t tabFlight[], int tabFlightLenght)
/*the function display the flight for the case 2*/
{
    char answer[10];/*to store the answer of the user*/
    int j;
    printf("Enter arrival city code or enter * to show all destinations>\n");
    scanf("%s", answer);/*to store the answer of the user*/
    if (answer[0] == '*')/*if the user enter "*"  */
    {
        if (tabFlightLenght == 0)/*if the user didn't add any flight,
                                  write no flight*/
        {
            printf("No flights\n");
        }
        else
        {
            printf("Flight Origin          Destination\n"
                   "------ --------------- ---------------\n");
            /*to print the flight as it is demand*/
            int i;
            for (i = 0; i < tabFlightLenght; i++)
            /*to print all the flight of the tab, so from index 0 to
             the number of flight add*/
            {
                tabFlight[i].arrival_city[3] = '\0';
                printFlight(tabFlight[i]);
                printf("\n");
            }
        }
    }
    else/*if the answer is not "*" */
    {
        int printedflight = 0;
        for (j = 0 ; j < tabFlightLenght ; j++)
        /*to check all the flight from the tab with the answer*/
        {
            int isSame = strcmp(answer, tabFlight[j].arrival_city);
            /*to check if the answer is the same as the city of the flight of
             tab[i], return 0 if they are the same */
            tabFlight[j].arrival_city[3] = '\0';
            if (isSame == 0)
            {
                if (printedflight == 0)
                {
                    printf("Flight Origin          Destination\n"
                           "------ --------------- ---------------\n");
                    /*si if they are the same it prints the flight*/
                }
                printFlight(tabFlight[j]);
                printedflight++;
                printf("\n");
            }
        }
        if (printedflight == 0)
        {
            printf("No flights\n");
            /*if no flight in the tab are the same as the answer,
             it prints no flight*/
        }
    }
}

/*******************************************************************************
 * This function save the tabflight in the database file
 * inputs:
 * - the input is the tab that contains all the flights, the name of the file,
 *   and the tablenght, it means the number of flight add
 * outputs:
 * - to know if the file is null or not
 *******************************************************************************/
int saveTheFlight(flight_t tabflight[], char filename[], int tablenght)
{
    int flag = 1;
    FILE* fp = fopen(filename, "w");/*open the file*/
    if (fp == NULL)
    {
        printf("Write error\n");/*in case fp is null*/
        
    }
    else
    {
        int i;
        for(i = 0; i < tablenght; i++)
        {
            /*to print all informations from a flight*/
            fprintf(fp," %s %d %d %d %d %s %d %d %d %d",
                    tabflight[i].flightcode, tabflight[i].departure_dt.month,
                    tabflight[i].departure_dt.day, tabflight[i].departure_dt.hour,
                    tabflight[i].departure_dt.minute, tabflight[i].arrival_city,
                    tabflight[i].arrival_dt.month, tabflight[i].arrival_dt.day,
                    tabflight[i].arrival_dt.hour, tabflight[i].arrival_dt.minute);
        }
        if (i < tablenght - 1)
        {
            fprintf(fp, "\n");
        }
        flag = 0;
    }
    fclose(fp);/*to close the file*/
    return flag;
}
/*******************************************************************************
 * This function load the tabflight from the database file
 * inputs:
 * - the input is the tab that contains all the flights, the name of the file,
 * outputs:
 * - none
 *******************************************************************************/
void loadFlight(flight_t tabflight[], char filename[])
{
    FILE* fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Read error\n");/*in case the file doesn't exist*/
    }
    else
    {
        int l = 0;
        while(l < MAX_NUM_FLIGHTS && fgetc(fp) != EOF)
        {
            fscanf(fp,"%s %d %d %d %d %s %d %d %d %d",tabflight[l].flightcode,
                   &tabflight[l].departure_dt.month, &tabflight[l].departure_dt.day,
                   &tabflight[l].departure_dt.hour, &tabflight[l].departure_dt.minute,
                   tabflight[l].arrival_city, &tabflight[l].arrival_dt.month,
                   &tabflight[l].arrival_dt.day, &tabflight[l].arrival_dt.hour,
                   &tabflight[l].arrival_dt.minute);
            l++;
        }
    }
    /*fclose(fp);to close the file*/
}






