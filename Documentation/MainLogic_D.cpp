/*The program uses SFML as its graphics library to generate the GUI
The original program was going to be a game, but turned out a database.
Program Logic:

In order to implement GUI I decided to use an FSM to navigate between windows (enum fsm).
The fsm is set to Main Menu at start time just after SimpleDB.Init is called, 
then the window is rendered and Main Menu Logic starts.
As long as the window remains open, the event queue is checked for triggers, if appropriate trigger is
found, action is taken based on its type.

Main Menu Logic:

I'm utilizing the event queue to poll for changes made by the user,
if up/down key is pressed, the MoveUp/MoveDown methods are being called, to enable menu navigation.
else if the Enter key is pressed, based on the current position, the appropriate menu is opened (fsm changes)
if Exit is the current selection, SimpleDB.Save_Exit is called and the program terminates.


Display Menu Logic:

This mostly works like the menu above, with the exception of the been_in_choice check, which makes sure
that before an entity is displayed, new input has been placed in the wybor Textbox.
The textbox can be accesed with the Enter key, and exited with the Esc key.

Add Menu Logic:
Works like main menu, but has additional loop which facilitates input of data to record, to navigate out
of input, the Esc key needs to be pressed, to go back to the primary row, End key needs to be pressed.

Delete Menu Logic:
Works like main menu, only addition is a field to display the current amount of records available,
if deletion is triggered, the number will update, and if available, the record with current index 1 will 
be removed from the vector.


*/