#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"history.h"

void showTestHistory()
{
    printf("Test History Successful ! \n");
}

ListHistory createListHistory()
{
    ListHistory list = (ListHistory)malloc(sizeof(struct ListHistory));
    if (list == NULL)
    {
        // Handle memory allocation failure
        return NULL;
    }
    list->H = NULL; // Initialize the head pointer to NULL
    list->T = NULL; // Initialize the tail pointer to NULL
    return list;    // Return the initialized list
}

ListHistory addHistory(ListHistory list, DataHistory data)
{
    PDHistory newHistory = (PDHistory)malloc(sizeof(DHistory)); // Allocate memory for a new History
    if (newHistory == NULL)
    {
        printf("Memory allocation failed\n");
        return list; // Return the unchanged list
    }

    newHistory->data = data;  // Set the data for the new History
    newHistory->nextL = NULL; // Initialize left pointer to NULL
    newHistory->nextR = NULL; // Initialize right pointer to NULL

    if (list->H == NULL)
    {                       // If the list is empty
        list->H = newHistory; // Set the new History as the head
        list->T = newHistory; // Set the new History as the tail
    }
    else
    {
        list->T->nextR = newHistory; // Link the new History to the end of the list
        newHistory->nextL = list->T; // Link the new History back to the current tail
        list->T = newHistory;        // Update the tail to the new History
    }
    return list; // Return the modified list
}

PDHistory searchByNameHistory(ListHistory list, const char *name)
{
    PDHistory iterator = list->H; // Initialize an iterator to the head of the list
    while (iterator != NULL)    // Traverse the list until the end
    {
        // Check if the name of the current History matches the given name
        if (iterator->data.name_hotel == name)
            return iterator; // Return the History if the name matches

        iterator = iterator->nextR; // Move to the next History in the list
    }
    return NULL; // Return NULL if no History with the given name is found
}

// Function to delete a History by name
void deleteByNameHistory(ListHistory list, const char *name)
{
    PDHistory deleteNode = searchByNameHistory(list, name); // Search for the History by name
    if (!deleteNode)
    {
        printf("History with name '%s' not found.\n", name); // If not found, print a message
        return;
    }

    // If the History to delete is the first History
    if (deleteNode == list->H)
    {
        list->H = deleteNode->nextR; // Update head to the next History
        if (list->H)
        {                          // If there are other Historys
            list->H->nextL = NULL; // Update the previous pointer of the new head
        }
        else
        {                   // If this was the only History
            list->H = NULL; // Set head to NULL
        }
    }
    // If the History to delete is the last History
    else if (deleteNode == list->T)
    {
        list->T = deleteNode->nextL; // Update tail to the previous History
        if (list->T)
        {                          // If there are other Historys
            list->T->nextR = NULL; // Update the next pointer of the new tail
        }
    }
    // If the History is in the middle
    else
    {
        deleteNode->nextL->nextR = deleteNode->nextR; // Bypass the node to delete
        deleteNode->nextR->nextL = deleteNode->nextL; // Bypass the node to delete
    }

    // Free dynamically allocated memory for the deleted History
    free(deleteNode);
}

void showListHistory(ListHistory list)
{
    PDHistory current = list->H; // Start from the head

    while (current != NULL)
    {
        printf("Name : %s \t location %s \n", current->data.name_hotel, current->data.location);
        printf("Date %d \n", current->data.date);
        current = current->nextR;
    }
    printf("\t =============== \t");
}

// Function to swap data between two Historys
void swapDataHistory(ListHistory list, PDHistory a, PDHistory b)
{
    DataHistory temp = a->data; // Store data of History a in temp
    a->data = b->data;        // Assign data of History b to History a
    b->data = temp;           // Assign temp (original data of History a) to History b
}

// Function to partition the list for quicksort
PDHistory PartitionDate(ListHistory list, PDHistory first, PDHistory last)
{
    if (first == last)
        return NULL; // If the list has only one element, return NULL

    bool check_smaller = false; // Check if j < i
    bool check_equal = false;   // Check if j = i

    bool check_i = true; // Check if i is over last
    bool check_j = true; // Check if j is over first

    PDHistory i = first->nextR;       // Start i from the next of first
    PDHistory j = last;               // Start j from last
    int pivot = first->data.date; // Set pivot as the id of the first History

    while (!check_smaller)
    {
        // Iterate i index
        while ((!check_smaller && i->data.date <= pivot) && check_i)
        {
            if (i == last)
                check_i = false;
            else
                i = i->nextR; // Move i to the right
        }

        // Iterate j index
        while ((!check_smaller && j->data.date > pivot) && check_j)
        {
            if (i == j)
                check_smaller = true; // If i and j meet, set check_smaller to true
            if (i != j && check_equal)
                check_smaller = true;
            if (j == first)
                check_j = false;
            else
                j = j->nextL; // Move j to the left
        }

        if (!check_smaller)
        {
            if (i == j)
            {
                if (!check_i)
                    check_smaller = true; // If i has reached the end, set check_smaller to true
            }
            else
            {
                swapDataHistory(list, i, j); // Swap data between i and j
            }
        }
    }
    return j; // Return the partition index
}

// Function to perform quicksort on the list
void QuicksortByDate(ListHistory list, PDHistory first, PDHistory last)
{
    if (first != last)
    {
        PDHistory j = PartitionDate(list, first, last); // Find the partition index
        swapDataHistory(list, first, j);                 // Swap the pivot with the partition index

        if (j != NULL)
        {
            if (j->nextL != NULL)
            {
                if (j != first)
                    QuicksortByDate(list, first, j->nextL); // Sort the left partition
            }
            if (j->nextR != NULL)
            {
                if (j != last)
                    QuicksortByDate(list, j->nextR, last); // Sort the right partition
            }
        }
    }
    else
        return; // If first equals last, return
}