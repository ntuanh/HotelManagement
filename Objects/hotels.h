#ifndef HOTEL_H
#define HOTEL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct DataHotel  
{
    char* name  , location ;
    int available_room , total_visitors  , hotline ;
    float rating  ;   // from 0 to 5 
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

// Functions
ListHotel createListHotel() ;
ListHotel addHotel(ListHotel hotels , DataHotel data );
PDHotel searchByNameHotel(ListHotel hotels , const char* name );
void showHotel(PDHotel hotel);
void deleteByNameHotel(ListHotel hotels, const char* name);
void showListHotel(ListHotel hotels);
int getNumberHotels(ListHotel hotels);
void swapDataHotel(ListHotel hotels, PDHotel a, PDHotel b) ;
PDHotel PartitionHotel(ListHotel hotels, PDHotel first, PDHotel last) ;
void QuicksortHotel(ListHotel hotels, PDHotel first, PDHotel last) ;
void freeMemoryHotel(ListHotel hotels);
void readHotelData(ListHotel hotels);
void writeHotelData(ListHotel hotels , DataHotel data , bool endline );

#endif // HOTEL_H
