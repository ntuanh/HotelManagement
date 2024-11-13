#ifndef USERS_H_
#define USERS_H_

typedef struct Users {
    int ID  ;       // capacity : 6 digits     
    char* name ;
    int birth ;     //form : year + month + date -> example : 20050705 
    char* email ;   
    int phone_number;   // form : "84 + number " -> example : 842312312
    struct Users *next ;
    struct Users *prev ;
} Users ;

void ShowTestUsers();

#endif 