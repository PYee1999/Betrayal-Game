#include "rooms.h"
#include "items.h"

// Create a Room
struct Room* room(char* description, struct Item* items,
                  int omenFound, char* event,
                  struct Room* north, struct Room* south,
                  struct Room* east, struct Room* west,
                  struct Room* up, struct Room* down)
{
    // Create new Room
    struct Room* newRoom;
    newRoom = (struct Room *) malloc(sizeof(struct Room));
    
    // Assign all of the variables in Room Struct to newRoom
    newRoom->description = description;
    newRoom->items = items;
    newRoom->omenFound = omenFound;
    newRoom->event = event;
    newRoom->north = north;
    newRoom->south = south;
    newRoom->east = east;
    newRoom->west = west;
    newRoom->up = up;
    newRoom->down = down;
    
    return newRoom;
}

// Set desciption of current room
void set_room_description(struct Room* current, char* description)
{
    current->description = description;
}

// Get desciption of current room
char* get_room_description(struct Room* current)
{
    return current->description;
}

// Set item list to current room
void set_room_item(struct Room *current, struct Item* items)
{
    current->items = items;
}

// Get item list of current room
struct Item* get_room_item(struct Room* current)
{
    return current->items;
}

// Add item to current room's item list, return item being added
void add_to_room_item(struct Room* current, struct Item* itemToAdd)
{
    add_item(get_room_item(current), itemToAdd);
}

// Drop item from current room's item list, return item being removed (Returns NULL is item cannot be found)
struct Item* drop_from_room_item(struct Room* current, char* nameOfItemToDrop)
{
    return drop_item(get_room_item(current), nameOfItemToDrop);
}

// Return boolean whether omen is found in current room
int omen_found(struct Room* current)
{
    return current->omenFound;
}

// Set event to current room
void set_room_event(struct Room* current, char* event)
{
    current->event = event;
}

// Get event of current room
char* get_room_event(struct Room* current)
{
    return current->event;
}

// Get north of current room
struct Room* get_north_room(struct Room* current)
{
    return current->north;
}

// Set north room of current room
void set_north_room(struct Room* current, struct Room* north)
{
    current->north = north;
}

// Get south of current room
struct Room* get_south_room(struct Room* current)
{
    return current->south;
}

// Set south room of current room
void set_south_room(struct Room* current, struct Room* south)
{
    current->south = south;
}

// Get east of current room
struct Room* get_east_room(struct Room* current)
{
    return current->east;
}

// Set east room of current room
void set_east_room(struct Room* current, struct Room* east)
{
    current->east = east;
}

// Get west of current room
struct Room* get_west_room(struct Room* current)
{
    return current->west;
}

// Set west room of current room
void set_west_room(struct Room* current, struct Room* west)
{
    current->west = west;
}

// Get up of current room
struct Room* get_up_room(struct Room* current)
{
    return current->up;
}

// Set up room of current room
void set_up_room(struct Room* current, struct Room* up)
{
    current->up = up;
}

// Get down of current room
struct Room* get_down_room(struct Room* current)
{
    return current->down;
}

// Set down room of current room
void set_down_room(struct Room* current, struct Room* down)
{
    current->down = down;
}

// Attach other Room to NORTH of current Room
void link_to_north(struct Room* current, struct Room* other)
{
    set_north_room(current, other); // Set current room's north to other room
    set_south_room(other, current); // Set other room's south to current room
}

// Attach other Room to SOUTH of current Room
void link_to_south(struct Room* current, struct Room* other)
{
    set_south_room(current, other); // Set current room's south to other room
    set_north_room(other, current); // Set other room's north to current room
}

// Attach other Room to EAST of current Room
void link_to_east(struct Room* current, struct Room* other)
{
    set_east_room(current, other); // Set current room's east to other room
    set_west_room(other, current); // Set other room's west to current room
}

// Attach other Room to WEST of current Room
void link_to_west(struct Room* current, struct Room* other)
{
    set_west_room(current, other); // Set current room's west to other room
    set_east_room(other, current); // Set other room's east to current room
}

// Attach other Room to UP of current Room
void link_to_up(struct Room* current, struct Room* other)
{
    set_up_room(current, other);   // Set current room's up to other room
    set_down_room(other, current); // Set other room's down to current room
}

// Attach other Room to DOWN of current Room
void link_to_down(struct Room* current, struct Room* other)
{
    set_down_room(current, other); // Set current room's down to other room
    set_up_room(other, current);   // Set other room's up to current room
}
