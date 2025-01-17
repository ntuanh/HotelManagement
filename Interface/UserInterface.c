#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "../Objects/history.h"
#include "../Objects/hotels.h"
#include "../Objects/users.h"
#include "UserInterface.h"
#include "HotelInterface.h"

void showHotel(PDHotel hotel);

DataUser signInUser()
{
    bool check_sign_in = false ;
    int id ;
    char *name = (char *) malloc(50 * sizeof(char));
    printf("Enter your id : ");
    scanf("%d",&id);
    printf("Enter your name : ");
    scanf("%s", name);

    FILE* file ;
    file = fopen("users.txt", "r");
    char line[256];

    // Read the file line by line
    while (fgets(line, sizeof(line), file) )
    if(strlen(line) != 0){
        int id_file ;
        char *name_file = (char *)malloc(50 * sizeof(char));

        // Tokenize the line
        char *token;
        token = strtok(line, "|");
        id_file = atoi(token); // Convert string to int

        token = strtok(NULL, "|");
        strncpy(name_file, token, 49); // Copy name safely
        name_file[49] = '\0';          // Ensure null termination

        name_file[strcspn(name_file, "\n")] = '\0';         // Remove newline from name

        if (id == id_file && strcmp(name, name_file) == 0)
        {
            printf("SIGN IN SUCCESSFULLY! Welcome, %s.\n", name_file);

            DataUser my_user = {id , name_file };
            free(name);
            return my_user;
        }
        free(name_file);
    }
    printf("NOT FOUND !!! \n");
    free(name);
    fclose(file);
    return (DataUser){-1, "..."};
}

DataUser signUpUser( historyManager manager)
{
    int id , phone_number ;
    char *name = (char *) malloc(50 * sizeof(char));

    printf("Enter your id :" );
    scanf("%d",&id);
    printf("Enter your name : ");
    scanf("%s", name);
    printf("Enter your phone number : ");
    scanf("%d",&phone_number);
    
    DataUser my_user = {id , name};

    // Add information to history manager 
    ListHistory list = createListHistory();
    list->phone_number = phone_number ;
    list->id = id ;
    manager = addListHistory(manager , list) ;

    writeUserData(my_user);
    return my_user;

}

int getTime()
{
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    return (tm_info->tm_year - 100) * 10000 + ++tm_info->tm_mon * 100 + tm_info->tm_mday;
}

void saveHistory(historyManager list, int id, DataHistory data)
{
    ListHistory my_history = searchByIDHistory( list , id );
    if (my_history != NULL)
    {
        addHistory(my_history, data);
        writeHistoryData(list , id , my_history->phone_number , data);
    }else return ;
    printf("Save your information done \n");

} 

int userInterface(historyManager manager, ListHotel hotels, ListUser users)
{
    printf("WELCOME TO USERINTERFACE \n");
    
    printf("Do you have an account [Y/N] = [1/0]? \n");
    DataUser my_user;
    int check_account ;
    scanf("%d",&check_account);
    if (check_account == 1 ) my_user = signInUser();
    else my_user = signUpUser(manager);
    if (my_user.id == -1) return 0 ;

    printf("Do you want to search by Hotel Location [Y/N] = [1/0]?\n");

    int confirm_search_by_location;
    printf("Enter in here: ");
    scanf("%d", &confirm_search_by_location);

    // If user choose option 1 , display more information about the hotel .
    // Then , check whether they want to book or not .
    if (confirm_search_by_location == 1)
    {
        //printf("Your choose : %d \n", confirm_search_by_location );
        char *name_hotel = (char*)malloc(50* sizeof(char));
        printf("Enter hotel's name in here : ");
        scanf("%s", name_hotel);

        PDHotel hotel = searchByNameHotel(hotels, name_hotel);

        printf("Show detail hotel's information :\n");
        if ( hotel->data.available_room == 0 )
        {
            printf("Sorry ! The hotel is fully booked. Please try again ! \n");
            return 1 ;
        }
        if ( hotel != NULL ) showHotel( hotel ) ; 
        else 
        { 
            printf("Hotel not found !\n");
            free(name_hotel);
            return 0 ;
        }

        // Check whether the user wants to book or not.
        printf("And do you book this hotel ? [Y/N] = [1/0]\n");

        int check_book_user ;
        scanf("%d", &check_book_user);

        if ( check_book_user == 1)
        {
            printf("Welcome to %s hotel \n" , hotel->data.name);

            DataHistory my_data = {hotel->data.name , hotel->data.location , getTime()};
            
            // Update hotel 
            int new_rating ;
            printf("Enter your rating in here : ");
            scanf("%d", &new_rating);

            // Calculate new rating 
            new_rating = new_rating + hotel->data.rating * hotel->data.total_visitors ;
            hotel->data.total_visitors += 1 ;
            new_rating = new_rating / hotel->data.total_visitors ;

            // Update value 
            hotel->data.rating = new_rating ;
            hotel->data.available_room -= 1;

            // save file hotels.txt 
            saveHotelInfo(hotels , hotel->data);

            // save History
            saveHistory(manager, my_user.id, my_data);
        }
        free(name_hotel);
    }
    return -1;
}


