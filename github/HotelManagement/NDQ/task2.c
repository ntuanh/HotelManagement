#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <stdbool.h> 
#include <users.h>
#include <hotels.h>

typedef struct HistoryEntry {
    char* hotelName;
    char* customerName;
    char* date; // Store the date as a string
} HistoryEntry;

typedef struct HistoryNode {
    HistoryEntry data;
    struct HistoryNode* next;
} HistoryNode;

typedef struct ListHistory {
    HistoryNode* head;
} *ListHistory;

// Function to create a new history list
ListHistory createListHistory() {
    ListHistory history = (ListHistory)malloc(sizeof(struct ListHistory));
    if (history == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    history->head = NULL;
    return history;
}

// Function to add an entry to the history list
void addHistory(ListHistory history, HistoryEntry entry) {
    HistoryNode* newNode = (HistoryNode*)malloc(sizeof(HistoryNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = entry;
    newNode->next = history->head;
    history->head = newNode;
}

ListHotel searchByLocation(ListHotel list, const char* location) {
    ListHotel result = createListHotel();
    PDHotel current = list->H;
    while (current != NULL) {
        if (strcmp(current->data.location, location) == 0) {
            addHotel(result, current->data);
        }
        current = current->nextR;
    }
    return result;
}

ListHotel searchByRating(ListHotel list, int minRating) {
    ListHotel result = createListHotel();
    PDHotel current = list->H;
    while (current != NULL) {
        if (current->data.rating >= minRating) {
            addHotel(result, current->data);
        }
        current = current->nextR;
    }
    return result;
}

bool checkBooked(PDHotel hotel) {
    return hotel->data.available_room > 0;
}

bool bookHotel(PDHotel hotel) {
    if (hotel->data.available_room > 0) {
        hotel->data.available_room--;
        return true; // Booking successful
    }
    return false; // No rooms available
}
bool bookHotel(PDHotel hotel) {
    if (hotel->data.available_room > 0) {
        hotel->data.available_room--;
        return true; // Booking successful
    }
    return false; // No rooms available
}
void addToHistory(ListHistory history, PDHotel hotel, const char* customerName) {
    if (!history || !hotel || !customerName) {
        printf("Invalid input to addToHistory\n");
        return;
    }

    HistoryEntry entry;
    entry.hotelName = hotel->data.name;
    entry.customerName = strdup(customerName); // Allocate and copy the name
    entry.date = getCurrentDate(); // Get the current date
    addHistory(history, entry);
}

void menu(ListHotel list) {
    int choice;
    char location[50];
    int minRating;
    ListHistory history = createListHistory(); 

    do {
        printf("\n1. Search by location\n");
        printf("2. Search by rating\n");
        printf("3. Book a hotel\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter location: ");
                scanf("%s", location);
                ListHotel byLocation = searchByLocation(list, location);
                showListHotel(byLocation);
                break;
            case 2:
                printf("Enter minimum rating: ");
                scanf("%d", &minRating);
                ListHotel byRating = searchByRating(list, minRating);
                showListHotel(byRating);
                break;
            case 3:
                printf("Enter hotel name to book: ");
                char hotelName[50];
                scanf("%s", hotelName);
                PDHotel hotel = searchByNameHotel(list, hotelName);
                if (hotel && bookHotel(hotel)) {
                    printf("Booking successful!\n");
                     char customerName[50];
                     printf("Nhập tên của bạn: ");
                     scanf("%s", customerName);
                     addToHistory(history, hotel, customerName);
                } 
                else {
                    printf("Booking failed. No available rooms.\n");
                }
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}
