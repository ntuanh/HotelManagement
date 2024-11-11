#ifndef History_H_
#define History_H_

typedef struct History {
    int ID  ;       // capacity : 6 digits     
    char* name ;
    int price ;     //
    char* address ;
    int phone_number;   // form : "84 + number " -> example : 842312312
    int ratting ;   // from 1 to 100  
} History ;

void ShowTestHistory();

#endif 