#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Keyword
{
    char* keyword;          // keyword - name of command
    char* description;      // keyword - name of command
    struct Keyword* next;   // next keyword in linked list
};

// Create Keyword
struct Keyword* keyword(char* keyword, char* description, struct Keyword* next);

// Get keyword from given node in linked list
char* get_keyword(struct Keyword* node);

// Get keyword's description from given node in linked list
char* get_keyword_description(struct Keyword* node);

// Get next node from given node in linked list
struct Keyword* get_keyword_next(struct Keyword* node);

// Add keyword to list
void add_keyword(struct Keyword* head, struct Keyword* keywordToAdd);

// Drop keyword from list
struct Keyword* drop_keyword(struct Keyword* head, char* name);

// Return true (1) if keyword is found in linked list, and false (0) otherwise
int find_keyword(char* keyword, struct Keyword* head);

// Print out list of all keywords
void print_all_keywords(struct Keyword* head);
