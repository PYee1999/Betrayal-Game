# Betrayal-Game
CS 250 Project #2 Betrayal
Preston Yee

This program is based on the text adventure game, "Betrayal at House on the Hill". The objective of the game is that you are stuck in a house, and you need to get out. In order to get out, you need to collect two keys (1 red key, 1 blue key), and at least one omen in order to succeed in the game. You will try exploring all of the different rooms until you can find those keys.  If you hit an event, the current room you are in will be teleported to be adjacent to the main room (the room you initially start at). You can only travel to 6 different rooms; try exploring more without getting the keys and getting to the main room, and you lose the game. However, if you arrive back to the main room with the two keys (satisfying the need for 2 items in order to win for requirement) and at least 1 omen, you win.

The program sets an array of 6 rooms (1 of the rooms are initially set as the starting room, a.k.a the Main Room), and will randomly shuffle through the 6 rooms, until you have used up all of the rooms. The program allows you to write in the following commands:

"inventory" 
- to show your current inventory of items.

"look" 
- to see items and adjacent rooms in the room you are currently in.

"take (insert item in room)" 
- to take whatever item is in the room you are in.
- NOTE: the code will check whether the item even exists or is found in room.

"drop (insert item in inventory)" 
- to drop whatever item is in your inventory.
- NOTE: the code will check whether the item even exists or is found in room.

"go (insert direction)" 
- to move to a different room.
- NOTE: The only directions you can go is up, down, east, west, or north 
- (You CANNOT go south).
- Code will also check whether the direction is valid or otherwise (Ex: won't let you go south)

"keywords"
- to show the list of possible keywords to use in this game.

Video Link: https://youtu.be/bRzf4cb_7dc
