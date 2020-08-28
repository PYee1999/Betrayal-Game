#include <stdlib.h>
#include <stdio.h>

struct Room
{
    int used; // State of Room (Already used or Not for random picking: start as false (0))
    char* description; // Description of Room
    struct Item* items; // List of Items in Room
    int omenFound; // Is there an Omen in the Room
    char* event; // Event that may occur in the Room
  
    // Adjacent Room References
    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
    struct Room* up;
    struct Room* down;
};

// Create a Room
struct Room* room(char* description, struct Item* items,
                  int omenFound, char* event,
                  struct Room* north, struct Room* south,
                  struct Room* east, struct Room* west,
                  struct Room* up, struct Room* down);

// Set desciption to current room
void set_room_description(struct Room* current, char* description);

// Get desciption of current room
char* get_room_description(struct Room* current);

// Set item linked list to current room
void set_room_item(struct Room* current, struct Item* item);

// Get item linked list of current room
struct Item* get_room_item(struct Room* current);

// Add item to current room's item list, return item being added
void add_to_room_item(struct Room* current, struct Item* itemToAdd);

// Drop item from current room's item list, return item being removed (Returns NULL is item cannot be found)
struct Item* drop_from_room_item(struct Room* current, char* nameOfItemToDrop);

// Return boolean whether omen is found in current room
int omen_found(struct Room* current);

// Set event to current room
void set_room_event(struct Room* current, char* event);

// Get event of current room
char* get_room_event(struct Room* current);

// Get north of current room
struct Room* get_north_room(struct Room* current);

// Set north room of current room
void set_north_room(struct Room* current, struct Room* north);

// Get south of current room
struct Room* get_south_room(struct Room* current);

// Set south room of current room
void set_south_room(struct Room* current, struct Room* south);

// Get east of current room
struct Room* get_east_room(struct Room* current);

// Set east room of current room
void set_east_room(struct Room* current, struct Room* east);

// Get west of current room
struct Room* get_west_room(struct Room* current);

// Set west room of current room
void set_west_room(struct Room* current, struct Room* west);

// Get up of current room
struct Room* get_up_room(struct Room* current);

// Set up room of current room
void set_up_room(struct Room* current, struct Room* up);

// Get down of current room
struct Room* get_down_room(struct Room* current);

// Set down room of current room
void set_down_room(struct Room* current, struct Room* down);

// Attach other Room to NORTH of current Room
void link_to_north(struct Room* current, struct Room* other);

// Attach other Room to SOUTH of current Room
void link_to_south(struct Room* current, struct Room* other);

// Attach other Room to EAST of current Room
void link_to_east(struct Room* current, struct Room* other);

// Attach other Room to WEST of current Room
void link_to_west(struct Room* current, struct Room* other);

// Attach other Room to UP of current Room
void link_to_up(struct Room* current, struct Room* other);

// Attach other Room to DOWN of current Room
void link_to_down(struct Room* current, struct Room* other);
