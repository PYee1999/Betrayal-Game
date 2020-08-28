#include "keyword.h"

// Create Keyword
struct Keyword* keyword(char* keyword, char* description, struct Keyword* next)
{
    struct Keyword* newKey;
    newKey = (struct Keyword *) malloc(sizeof(struct Keyword));
    
    newKey->keyword = keyword;
    newKey->description = description;
    newKey->next = next;
    
    return newKey;
}

// Get keyword's name from given node in linked list
char* get_keyword(struct Keyword* node)
{
    return node->keyword;
}

// Get keyword's description from given node in linked list
char* get_keyword_description(struct Keyword* node)
{
    return node->description;
}

// Get next node from given node in linked list
struct Keyword* get_keyword_next(struct Keyword* node)
{
    return node->next;
}

// Add keyword to list
void add_keyword(struct Keyword* head, struct Keyword* keywordToAdd)
{
    if (keywordToAdd == NULL) return; // Do nothing if the keywordToAdd is NULL
    
    keywordToAdd->next = head->next;
    head->next = keywordToAdd;
}

// Drop keyword from list
struct Keyword* drop_keyword(struct Keyword* head, char* name)
{
    struct Keyword* current = head;
    
    while (current->next != NULL)
    {
        if (strcmp(get_keyword(current->next), name) == 0)
        {
            struct Keyword* returnItem = current->next;
            current->next = current->next->next;
            return returnItem;
        }
        
        current = current->next;
    }

    return NULL; // Return NULL if the item was never found in the list in the first place
}

// Return true (1) if keyword is found in linked list, and false (0) otherwise
int find_keyword(char* keyword, struct Keyword* head)
{
    struct Keyword* current = head;
    while (current != NULL)
    {
        if (strcmp(get_keyword(current), keyword) == 0)
        {
            return 1; // If keyword is found in linked list, return true
        }
        current = current->next;
    }
    return 0; // Otherwise, return false
}

// Print out list of all keywords
void print_all_keywords(struct Keyword* head)
{
    printf("List of keywords:\n");
    struct Keyword* ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(get_keyword(ptr), "\0") != 0)
        {
            // Print keyword's name and description
            printf("- %s: %s\n", get_keyword(ptr), get_keyword_description(ptr));
        }
        ptr = ptr->next;
    }
}
