#include "items.h"

// Create Item
struct Item* item(char* name, char* description, struct Item* next)
{
    struct Item* newItem;
    newItem = (struct Item *) malloc(sizeof(struct Item));
    
    newItem->name = name;
    newItem->description = description;
    newItem->next = next;
    
    return newItem;
}

// Add item to list
void add_item(struct Item* list, struct Item* itemToAdd)
{
    if (itemToAdd == NULL) return; // Return nothing if the itemToAdd is NULL
    
    itemToAdd->next = list->next;
    list->next = itemToAdd;
}

// Drop item from list
struct Item* drop_item(struct Item* head, char* name)
{
    struct Item *current = head;
    
    while (current->next != NULL)
    {
        if (strcmp(get_item_name(current->next), name) == 0)
        {
            struct Item* returnItem = current->next;
            current->next = current->next->next;
            return returnItem;
        }
        
        current = current->next;
    }

    return NULL; // Return NULL if the item was never found in the list in the first place
}

// Set Item's name
void set_item_name(struct Item* node, char* name)
{
    node->name = name;
}

// Get Item's name
char* get_item_name(struct Item* node)
{
    return node->name;
}

// Get Item's next node given current node
struct Item* get_item_next(struct Item* node)
{
    return node->next;
}

// Set Item's description
void set_item_description(struct Item* node, char* description)
{
    node->description = description;
}

// Get Item's description
char* get_item_description(struct Item* node)
{
    return node->description;
}

// Return the number of items in linked list
int item_count(struct Item* head)
{
    struct Item* ptr = head;
    int count = 0;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }
    return count;
}

// Print out list of all items in linked list
void print_all_items(struct Item* head)
{
    struct Item* ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(ptr->name, "\0") != 0)
        {
            printf("- %s: %s\n", ptr->name, ptr->description); // Print item's name and description
        }
        ptr = ptr->next;
    }
}

// Find item from list (Found, return 1; Not found, return 0)
int find_item(struct Item* head, char* name)
{
    struct Item *current = head;
    
    while (current->next != NULL)
    {
        if (strcmp(get_item_name(current->next), name) == 0)
        {
            return 1; // If item has been found, return 1 (True)
        }
        current = current->next;
    }

    return 0; // If item has NOT been found, return 0 (False)
}
