#include "items.h"
#include "rooms.h"
#include "keyword.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

struct Avatar
{
    int omen;               // Has omen
    struct Item* inventory; // Has inventory of Items
    struct Room* location;  // Keep track of where the avatar is located
};

// Global Variables
struct Avatar* player;      // Player
struct Item* item1;         // 3 Items
struct Item* item2;
struct Item* item3;
char* event1;               // 3 Events
char* event2;
char* event3;
int roomListLength = 6;     // Length of room list
struct Room* roomList[6];   // List of rooms
struct Room* bedroom1;      // 7 Rooms
struct Room* bedroom2;
struct Room* bathroom1;
struct Room* bathroom2;
struct Room* hallway1;
struct Room* hallway2;
struct Room* mainroom;
struct Keyword* keywordList; // Keywords

// Create a Room
struct Room* room(char* description, struct Item* items,
                  int omenFound, char* event,
                  struct Room* north, struct Room* south,
                  struct Room* east, struct Room* west,
                  struct Room* up, struct Room* down);

// Create Item
struct Item* item(char* name, char* description, struct Item* next);

// Create Avatar
struct Avatar* avatar(int omen, struct Item* inventory, struct Room* location)
{
    struct Avatar* avatar;
    avatar = (struct Avatar *) malloc(sizeof(struct Avatar));
    
    avatar->omen = omen;
    avatar->inventory = inventory;
    avatar->location = location;
    
    return avatar;
}

// Update that the avatar has an omen (increment by 1)
void update_avatar_omen(struct Avatar* avatar)
{
    avatar->omen++;
}

// Get avatar's omen (whether it has it or not: 1 = True, 0 = False)
int get_avatar_omen(struct Avatar* avatar)
{
    return avatar->omen;
}

// Get avatar's inventory
struct Item* get_avatar_inventory(struct Avatar* avatar)
{
    return avatar->inventory;
}

// Get avatar's current room location
struct Room* get_avatar_location(struct Avatar* avatar)
{
    return avatar->location;
}

// Set avatar's current room location
void set_avatar_location(struct Avatar* avatar, struct Room* location)
{
    avatar->location = location;
}

// Move avatar north to the next Room
void move_avatar_north(struct Avatar* avatar, struct Room* newRoom)
{
    link_to_north(get_avatar_location(avatar), newRoom); // Link new room north of current room
    set_avatar_location(avatar, newRoom); // Set avatar to new room
}

// Move avatar east to the next Room
void move_avatar_east(struct Avatar* avatar, struct Room* newRoom)
{
    link_to_east(get_avatar_location(avatar), newRoom); // Link new room east of current room
    set_avatar_location(avatar, newRoom); // Set avatar to new room
}

// Move avatar west to the next Room
void move_avatar_west(struct Avatar* avatar, struct Room* newRoom)
{
    link_to_west(get_avatar_location(avatar), newRoom); // Link new room west of current room
    set_avatar_location(avatar, newRoom); // Set avatar to new room
}

// Move avatar up to the next Room
void move_avatar_up(struct Avatar* avatar, struct Room* newRoom)
{
    link_to_up(get_avatar_location(avatar), newRoom); // Link new room above current room
    set_avatar_location(avatar, newRoom); // Set avatar to new room
}

// Move avatar down to the next Room
void move_avatar_down(struct Avatar* avatar, struct Room* newRoom)
{
    link_to_down(get_avatar_location(avatar), newRoom); // Link new room below current room
    set_avatar_location(avatar, newRoom); // Set avatar to new room
}

// Move avatar north to the next Room (If room exist; return 1 if successful, 0 otherwise)
int can_move_north(struct Avatar* avatar)
{
    if (get_north_room(get_avatar_location(avatar)) != NULL) // If there exist a room north of the current room,
    {
        return 1;
    }
    return 0;
}

// Move avatar east to the next Room (If room exist; return 1 if successful, 0 otherwise)
int can_move_east(struct Avatar* avatar)
{
    if (get_east_room(get_avatar_location(avatar)) != NULL) // If there exist a room east of the current room,
    {
        return 1;
    }
    return 0;
}

// Move avatar west to the next Room (If room exist; return 1 if successful, 0 otherwise)
int can_move_west(struct Avatar* avatar)
{
    if (get_west_room(get_avatar_location(avatar)) != NULL) // If there exist a room west of the current room,
    {
        return 1;
    }
    return 0;
}

// Move avatar up to the next Room (If room exist; return 1 if successful, 0 otherwise)
int can_move_up(struct Avatar* avatar)
{
    if (get_up_room(get_avatar_location(avatar)) != NULL) // If there exist a room up of the current room,
    {
        return 1;
    }
    return 0;
}

// Move avatar down to the next Room (If room exist; return 1 if successful, 0 otherwise)
int can_move_down(struct Avatar* avatar)
{
    if (get_down_room(get_avatar_location(avatar)) != NULL) // If there exist a room down of the current room,
    {
        return 1;
    }
    return 0;
}

// Remove all of the adjacent rooms that surround the avatar's current room
void remove_all_avatar_adjacent_rooms(struct Avatar* avatar)
{
    // If any of the adjacent rooms are present, disconnect link from adjacent room to player's current room
    if (get_north_room(get_avatar_location(avatar)) != NULL)
    {
        set_south_room(get_north_room(get_avatar_location(avatar)), NULL);
    }
    if (get_south_room(get_avatar_location(avatar)) != NULL)
    {
        set_north_room(get_south_room(get_avatar_location(avatar)), NULL);
    }
    if (get_east_room(get_avatar_location(avatar)) != NULL)
    {
        set_west_room(get_east_room(get_avatar_location(avatar)), NULL);
    }
    if (get_west_room(get_avatar_location(avatar)) != NULL)
    {
        set_east_room(get_west_room(get_avatar_location(avatar)), NULL);
    }
    if (get_up_room(get_avatar_location(avatar)) != NULL)
    {
        set_down_room(get_up_room(get_avatar_location(avatar)), NULL);
    }
    if (get_down_room(get_avatar_location(avatar)) != NULL)
    {
        set_up_room(get_down_room(get_avatar_location(avatar)), NULL);
    }
    
    // Disconnect link from player's current room to any of the adjacent rooms
    set_north_room(get_avatar_location(avatar), NULL);
    set_south_room(get_avatar_location(avatar), NULL);
    set_east_room(get_avatar_location(avatar), NULL);
    set_west_room(get_avatar_location(avatar), NULL);
    set_up_room(get_avatar_location(avatar), NULL);
    set_down_room(get_avatar_location(avatar), NULL);
}

// Print all items in the current room of avatar
void print_items_in_room(struct Avatar* avatar)
{
    printf("Items in %s: ", get_room_description(get_avatar_location(avatar)));
    print_all_items(get_room_item(get_avatar_location(avatar)));
}

// Gets random room from list of rooms TODO: CLEAN UP!!!
struct Room* get_random_room()
{
    if (roomListLength <= 0) // If the length is empty, return NULL
    {
        return NULL;
    }
    
    srand(time(NULL));
    int index = (rand() % (roomListLength)); // Randomly generate list index number (0 to length-1)
    
    struct Room* room = roomList[index]; // Get random room from list
        
    if (index != roomListLength-1)  // If the index is not the last element in array,
    {
        struct Room* tempRoom = roomList[index];        // Swap room of randomly picked index with last
        roomList[index] = roomList[roomListLength-1];   // index.
        roomList[roomListLength-1] = tempRoom;          // Otherwise, skip this if statement.
    }
    roomListLength--;   // Decrement roomListLength
    
    return room; // Return randomly attained room
}

// Free functions to free allocated memory (Keywords, Avatar, Rooms, Items)
void free_keyword(struct Keyword* head) // Free list of Keywords
{
    if (get_keyword_next(head) != NULL)
    {
        free_keyword(get_keyword_next(head));
    }
    free(head);
}

void free_items(struct Item* head) // Free list of Items
{
    if (get_item_next(head) != NULL)
    {
        free_items(get_item_next(head));
    }
    free(head);
}

void free_avatar(struct Avatar* head) // Free Avatar
{
    free(head);
}

void free_rooms(struct Room* head) // Free list of Rooms
{
    free(head); // Free head
}

void lower_string(char s[]) // Convert string to lowercase
{
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

// Main Method: Where the game plays
int main(void)
{
    // Omen variables
    int omenNotFound = 0;
    int omenFound = 1;
    
    // Create avatar: no omens, empty first item (dummy head), no location set (yet)
    player = avatar(0, item("\0", "\0", NULL), NULL);
    
    // Create 3 item lists
    item1 = item("red key", "a shiny red key",                // Red Key (Need to collect)
            item("pants", "a pair of blue jeans", NULL));     // Pants
    item2 = item("blue key", "a shiny blue key", NULL);       // Blue Key (Need to collect)
    item3 = item("flashlight", "a LED flashlight", NULL);     // Flashlight
    
    // Create 3 omens and 3 events (Add omen to player)
    event1 = "There is a creaking noise, but you don't know where it is coming from.";
    event2 = "You encounter a black cat; is it a sign of a bad luck?\n";
    event3 = "A spooky voice is telling you to run away, \n"
             "but you don't know who it is or where it is coming from.";
    
    // Create 7 rooms; some rooms contain the events or items created above
    bedroom1 = room("Bedroom 1", item("\0", "\0", item1), omenNotFound, NULL,
                    NULL, NULL, NULL, NULL, NULL, NULL);
    bedroom2 = room("Bedroom 2", item("\0", "\0", NULL), omenNotFound, event1,
                    NULL, NULL, NULL, NULL, NULL, NULL);
    bathroom1 = room("Bathroom 1", item("\0", "\0", NULL), omenFound, NULL,
                    NULL, NULL, NULL, NULL, NULL, NULL);
    bathroom2 = room("Bathroom 2", item("\0", "\0", item2), omenNotFound, NULL,
                    NULL, NULL, NULL, NULL, NULL, NULL);
    hallway1 = room("Hallway 1", item("\0", "\0", NULL), omenNotFound, event2,
                    NULL, NULL, NULL, NULL, NULL, NULL);
    hallway2 = room("Hallway 2", item("\0", "\0", item3), omenNotFound, event3,
                    NULL, NULL, NULL, NULL, NULL, NULL);
    mainroom = room("Main Room", item("\0", "\0", NULL), omenFound, NULL,
                    NULL, NULL, NULL, NULL, NULL, NULL);
    
    // Create list of 6 rooms
    roomList[0] = bedroom1;
    roomList[1] = bedroom2;
    roomList[2] = bathroom1;
    roomList[3] = bathroom2;
    roomList[4] = hallway1;
    roomList[5] = hallway2;
    
    // Set mainroom as default starting point
    set_avatar_location(player, mainroom);          // Set avatar in main room
    add_item(get_avatar_inventory(player), get_room_item(mainroom)); // Add mainroom's items into avatar's inventory
    update_avatar_omen(player);                     // Since mainroom has omen, increment omen count in avatar
    
    // Create keyword list
    keywordList = keyword("inventory",                  // List avatar's inventory
                          "show your current inventory of items",
                  keyword("look",                       // Look in avatar's current room (description & items)
                          "search the room you are in: see items available and adjacent rooms",
                  keyword("take",                       // Take item from current room and add to inventory
                          "take whatever item is in the room you are in",
                  keyword("drop",                       // Drop item from inventory and add to current room
                          "drop whatever item is in your inventory",
                  keyword("go",                         // Move avatar to different room
                          "move from current room",
                  keyword("keywords",                   // List keywords to use in game
                          "show the list of possible keywords to use in this game", NULL))))));
    
    // Start introduction to player
    printf("Welcome to the Escape Game!\n"
           "You are stuck in this house, and need to get out.\n"
           "You are currently located in the mainroom, but the door is locked.\n"
           "The only way to open the door is to collect 2 keys: a red key and a blue key.\n"
           "Your objective is to find the 2 keys, and return to the mainroom to escape.\n\n"
           "Type 'inventory' to show your current inventory of items.\n"
           "Type 'look' to see items and adjacent rooms in the room you are currently in.\n"
           "Type 'take (insert item in room)' to take whatever item is in the room you are in.\n"
           "Type 'drop (insert item in inventory)' to drop whatever item is in your inventory.\n"
           "Type 'go (insert direction)' to move to a different room.\n"
           "The only directions you can go is up, down, east, west, or north (You CANNOT go south).\n"
           "Type 'keywords' to show the list of possible keywords to use in this game.\n"
           "Let's begin: \n");
    
    // Create boolean variable for win or lose states
    int win = 0;
    
    // Continuous loop in game
    while(1)
    {
        /*
         Conditions for player to win:
         - Must be located at mainroom
         - Must have at least 1 omen
         - Must have at least 2 items in inventory: (Specifically "red key" and "blue key")
        */
        if (strcmp(get_room_description(get_avatar_location(player)), get_room_description(mainroom)) == 0 &&
            (get_avatar_omen(player) > 0) &&
            (find_item(get_avatar_inventory(player), "red key") == 1) &&
            (find_item(get_avatar_inventory(player), "blue key") == 1))
        {
            // If player meet criteria, player wins and break out of loop
            win = 1;
            break;
        }

        char input[50];
        printf("\nYou have %i rooms left to explore.", roomListLength);
        printf("\nInput your action: ");
        fgets(input, 50, stdin);                    // Get the player's input
        
        char* command = strtok(input, " ");         // Obtain 1st word (Command)
        char* object = strtok(0, "");               // Obtain 2nd word (Object)
        command = strtok(command, "\n");            // Remove newlines from command word
        object = strtok(object, "\n");              // Remove newlines from object word

        lower_string(command);                      // Convert command string to lowercase for comparison
        lower_string(object);                       // Convert object string to lowercase for comparison
        
        if (find_keyword(command, keywordList) == 1)     // See if player's input is in the list of keywords
        {
            if (strcmp(command, "inventory") == 0)  // Player wants to see inventory
            {
                printf("Your Inventory:\n");
                printf("- omens: %i\n", get_avatar_omen(player));   // Also show number of omens collected
                print_all_items(get_avatar_inventory(player));
            }
            else if (strcmp(command, "look") == 0)  // Player looks in current room (specifically items)
            {
                printf("You are in: %s\n", get_room_description(get_avatar_location(player)));
                printf("The room consists of:\n");
                print_all_items(get_room_item(get_avatar_location(player)));
                
                // Show adjacent rooms of player's current room
                if (can_move_north(player)) // If there is a room north of player's current room, show player
                {
                    printf("There is a room north of you: %s\n",
                           get_room_description(get_north_room(get_avatar_location(player))));
                }
                if (can_move_east(player)) // If there is a room east of player's current room, show player
                {
                    printf("There is a room east of you: %s\n",
                           get_room_description(get_east_room(get_avatar_location(player))));
                }
                if (can_move_west(player)) // If there is a room west of player's current room, show player
                {
                    printf("There is a room west of you: %s\n",
                           get_room_description(get_west_room(get_avatar_location(player))));
                }
                if (can_move_up(player)) // If there is a room up of player's current room, show player
                {
                    printf("There is a room up of you: %s\n",
                           get_room_description(get_up_room(get_avatar_location(player))));
                }
                if (can_move_down(player)) // If there is a room down of player's current room, show player
                {
                    printf("There is a room down of you: %s\n",
                           get_room_description(get_down_room(get_avatar_location(player))));
                }
            }
            else if (strcmp(command, "take") == 0)  // Player takes an item from current room and put in inventory
            {
                if (object == NULL || strcmp(object, "") == 0)  // If the second word is NULL (not inputted),
                {
                    printf("Command invalid: What do you want to take?\n"); // Command is void
                    continue;
                }
                
                if (find_item(get_room_item(get_avatar_location(player)), object) == 0) // If not found in room,
                {
                    printf("Item not found in room.\n"); // Command is void
                    continue;
                }
                else    // If item is found, remove from current room and add to inventory
                {
                    struct Item* droppedItem = drop_from_room_item(get_avatar_location(player), object);
                    add_item(get_avatar_inventory(player), droppedItem);
                    printf("You have picked up %s!\n", object);
                }
            }
            else if (strcmp(command, "drop") == 0)  // Player drops an item from inventory in current room
            {
                if (object == NULL || strcmp(object, "") == 0)   // If the second word is NULL (not inputted),
                {
                    printf("Command invalid: What do you want to take?\n"); // Command is void
                    continue;
                }
                
                if (find_item(get_avatar_inventory(player), object) == 0) // If not found in inventory,
                {
                    printf("Item not found in your inventory.\n"); // Command is void
                    continue;
                }
                else    // If item is found, remove from inventory and add to current room
                {
                    struct Item* droppedItem = drop_item(get_avatar_inventory(player), object);
                    add_to_room_item(get_avatar_location(player), droppedItem);
                    printf("You have dropped %s!\n", object);
                }
                
            }
            else if (strcmp(command, "go") == 0)    // Player wants to move...
            {
                struct Room* randomRoom = NULL;
                
                if (strcmp(object, "north") == 0)       // north
                {
                    if (can_move_north(player) != 0) // If there is an existing room north of player,
                    {
                        set_avatar_location(player, get_north_room(get_avatar_location(player))); // Move north
                    }
                    else    // Otherwise,
                    {
                        randomRoom = get_random_room(); // Randomly get room
                        
                        if (randomRoom == NULL) // If out of rooms, game ends (Player loses)
                        {
                            // Player loses and break out of loop
                            win = 0;
                            break;
                        }
                        
                        move_avatar_north(player, randomRoom);  // Move player to new room
                    }
                }
                else if (strcmp(object, "south") == 0)  // south
                {
                    printf("Sorry, but you cannot go south.\n"); // Tell player that they can't go south
                    continue;
                }
                else if (strcmp(object, "east") == 0)   // east
                {
                    if (can_move_east(player) != 0) // If there is an existing room east of player,
                    {
                        set_avatar_location(player, get_east_room(get_avatar_location(player))); // Move east
                    }
                    else    // Otherwise,
                    {
                        randomRoom = get_random_room(); // Randomly get room
                        
                        if (randomRoom == NULL) // If out of rooms, game ends (Player loses)
                        {
                            // Player loses and break out of loop
                            win = 0;
                            break;
                        }
                        
                        move_avatar_east(player, randomRoom);  // Add room
                    }
                }
                else if (strcmp(object, "west") == 0)   // west
                {
                    if (can_move_west(player) != 0) // If there is an existing room east of player,
                    {
                        set_avatar_location(player, get_west_room(get_avatar_location(player))); // Move west
                    }
                    else    // Otherwise,
                    {
                        randomRoom = get_random_room(); // Randomly get room
                        
                        if (randomRoom == NULL) // If out of rooms, game ends (Player loses)
                        {
                            // Player loses and break out of loop
                            win = 0;
                            break;
                        }
                        
                        move_avatar_west(player, randomRoom);  // Add room
                    }
                }
                else if (strcmp(object, "up") == 0)     // up
                {
                    if (can_move_up(player) != 0) // If there is an existing room up of player,
                    {
                        set_avatar_location(player, get_up_room(get_avatar_location(player))); // Move avatar up
                    }
                    else    // Otherwise,
                    {
                        randomRoom = get_random_room(); // Randomly get room
                        
                        if (randomRoom == NULL) // If out of rooms, game ends (Player loses)
                        {
                            // Player loses and break out of loop
                            win = 0;
                            break;
                        }
                        
                        move_avatar_up(player, randomRoom);  // Add room
                    }
                }
                else if (strcmp(object, "down") == 0)   // down
                {
                    if (can_move_down(player) != 0) // If there is an existing room down of player,
                    {
                        set_avatar_location(player, get_down_room(get_avatar_location(player))); // Move avatar down
                    }
                    else    // Otherwise,
                    {
                        randomRoom = get_random_room();         // Randomly get room
                        
                        if (randomRoom == NULL)  // If out of rooms, game ends (Player loses)
                        {
                            // Player loses and break out of loop
                            win = 0;
                            break;
                        }
                        
                        move_avatar_down(player, randomRoom);           // Add room
                    }
                }
                else                                    // Otherwise,
                {
                    printf("That is not a valid direction.\n"); // Notify player that the direction is not valid
                    continue;
                }
                
                printf("\nYou have moved %s into %s.\n", object,
                       get_room_description(get_avatar_location(player)));      // Print room's description
                print_all_items(get_room_item(get_avatar_location(player)));    // Print list of items in room
                
                // If player moved into a new, randomly-selected room,
                if (randomRoom != NULL)
                {
                    if (omen_found(randomRoom) != 0) // If there is an omen in the room,
                    {
                        update_avatar_omen(player); // Increment omen
                        printf("You have collected an omen! You now have %i omens.\n", get_avatar_omen(player));
                    }
                    
                    if (get_room_event(randomRoom) != NULL) // If there is an event in the room,
                    {
                        printf("Event: %s\n", get_room_event(randomRoom)); // Print room's event
                        remove_all_avatar_adjacent_rooms(player); // Remove all adjacent rooms
                        
                        // Move random room (player's current room) and link to mainroom
                        // Mainroom's north availability is not accounted for, because player cannot move south
                        if (get_south_room(mainroom) == NULL)
                        {
                            link_to_north(randomRoom, mainroom); // Link mainroom to north of random room
                            printf("The mainroom is north of your location.\n");
                        }
                        else if (get_east_room(mainroom) == NULL)
                        {
                            link_to_west(randomRoom, mainroom); // Link mainroom to west of random room
                            printf("The mainroom is west of your location.\n");
                        }
                        else if (get_west_room(mainroom) == NULL)
                        {
                            link_to_east(randomRoom, mainroom); // Link mainroom to east of random room
                            printf("The mainroom is east of your location.\n");
                        }
                        else if (get_up_room(mainroom) == NULL)
                        {
                            link_to_down(randomRoom, mainroom); // Link mainroom to down of random room
                            printf("The mainroom is down of your location.\n");
                        }
                        else if (get_down_room(mainroom) == NULL)
                        {
                            link_to_up(randomRoom, mainroom); // Link mainroom to up of random room
                            printf("The mainroom is up of your location.\n");
                        }
                    }
                }
            }
            else if (strcmp(command, "keywords") == 0)  // Player wants to see list of keywords
            {
                print_all_keywords(keywordList);
            }
        }
        else // If input is not valid, let player know and skip to end of loop, and ask for input again
        {
            printf("Command invalid: Type 'keywords' to show the list of possible keywords to use in this game.\n");
            continue;
        }
    }
    
    // When the game ends, let player know about the end result.
    if (win) // If player win,
    {
        printf("\nYOU ESCAPED THE HOUSE! YOU WIN!!!\n");
    }
    else // Otherwise, player loses
    {
        printf("\nYOU RAN OUT OF ROOM TO EXPLORE! YOU LOSE!!!\n");
    }
    
    // Free all of the memory at the end
    free_keyword(keywordList);                  // Free Keyword Linked List
    free_items(item1);                          // Free Items in all Rooms
    free_items(item2);
    free_items(item3);
    free_items(get_avatar_inventory(player));   // Free Avatar's Inventory
    free_rooms(bedroom1);                       // Free all 7 Rooms Created for Game
    free_rooms(bedroom2);
    free_rooms(bathroom1);
    free_rooms(bathroom2);
    free_rooms(hallway1);
    free_rooms(hallway2);
    free_rooms(mainroom);
    free_avatar(player);                        // Free Avatar

    return 0;
}
