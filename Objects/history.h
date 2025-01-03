#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct DataHistory
{
    char *name_hotel;
    char *location;
    int date; // year month date ex : 241211
} DataHistory;

typedef struct DHistory

{
    DataHistory data;
    struct DHistory *nextL, *nextR;
} DHistory;

typedef DHistory *PDHistory;

typedef struct ListHistory
{
    int id;           // match user
    int phone_number; // phone number of user started by 84
    PDHistory H;
    PDHistory T;
    struct ListHistory *nextL, *nextR;
} *ListHistory;

typedef struct historyManager
{
    ListHistory H;
    ListHistory T;
} *historyManager;

// Function prototypes for List History
void showTestHistorys();
ListHistory createListHistory();
ListHistory addHistory(ListHistory list, DataHistory data);
PDHistory searchByNameHistory(ListHistory List, const char *name);
void deleteByNameHistory(ListHistory list, const char *name);
void showListHistory(ListHistory list);
void swapDataHistory(ListHistory list, PDHistory a, PDHistory b);
PDHistory PartitionDate(ListHistory list, PDHistory first, PDHistory last);
void QuicksortByDate(ListHistory list, PDHistory first, PDHistory last);

// Function propotypes for History Manager

historyManager createHistoryManager();
historyManager addListHistory(historyManager list, ListHistory history );
ListHistory searchByIDHistory(historyManager list, int id);
void deleteByIDHistory(historyManager list, int id);
void showHistoryManager(historyManager list);
void freeMemoryHistory(ListHistory list) ;
void freeMemoryHistoryManager(historyManager manager);
void readHistoryData(historyManager historyManager );
void writeHistoryData(historyManager list, int id, int phone_number, DataHistory data);

#endif