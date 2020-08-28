#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Linked list of items
struct Item
{
    char* name; // Item's name
    char* description; // Item's description
    struct Item* next; // Next
};

// Create Item
struct Item* item(char* name, char* description, struct Item* next);

// Add item into linked list
void add_item(struct Item* list, struct Item* itemToAdd);

// Remove item from linked list
struct Item* drop_item(struct Item* head, char* name);

// Set Item's name
void set_item_name(struct Item* node, char* name);

// Get Item's name
char* get_item_name(struct Item* node);

// Get Item's next node given current node
struct Item* get_item_next(struct Item* node);

// Set Item's description
void set_item_description(struct Item* node, char* description);

// Get Item's description
char* get_item_description(struct Item* node);

// Return the number of items in linked list
int item_count(struct Item* head);

// Print out list of all items in linked list
void print_all_items(struct Item* head);

// Find item from list (Found, return 1; Not found, return 0)
int find_item(struct Item* head, char* name);
