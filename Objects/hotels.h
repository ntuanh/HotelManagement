#ifndef HOTEL_H
#define HOTEL_H

typedef struct DataHotel  
{
    int rating  ;   // from 1 to 100 
    int available_room ;    // from 0 
    char* name  ;       
    char* location ;
    int hotline ;
    int past_guests; // The number of guests who have stayed at a hotel
} DataHotel;

typedef struct DHotel
{
    DataHotel data ;
    struct DHotel *nextL , *nextR ;
} DHotel;

typedef DHotel* PDHotel;

typedef struct ListHotel
{
    PDHotel H ;
    PDHotel T ;
}* ListHotel ;

// Function prototypes 
void showTestHotels();
ListHotel createListHotel() ;
ListHotel addHotel(ListHotel list , DataHotel data );
PDHotel searchByNameHotel(ListHotel List , const char* name );
void deleteByNameHotel(ListHotel list, const char* name);
void showListHotel(ListHotel list);
void swapDataHotel(ListHotel list, PDHotel a, PDHotel b) ;
PDHotel PartitionHotel(ListHotel list, PDHotel first, PDHotel last) ;
void QuicksortHotel(ListHotel list, PDHotel first, PDHotel last) ;


#endif // HOTEL_H
