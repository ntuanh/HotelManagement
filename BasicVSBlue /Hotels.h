#ifndef HOTELS_H_
#define HOTELS_H_

typedef struct Hotels {
    int ID  ;       // capacity : 6 digits     
    char* name ;
    int price ;     //
    char* address ;
    int phone_number;   // form : "84 + number " -> example : 842312312
    int ratting ;   // from 1 to 100  
    struct Hotels *next ;
    struct Hotels *prev ;
} Hotels ;

void ShowTestHotels();

#endif 