/*
Main Menu:
The program uses SFML as its graphics library to generate the GUI
This class is the central point of the program, here you can select the next move to make, i.e. choose
which menu comes next. It is also the base for the rest of the menus.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
GENERIC ITEMS:
-The constructor takes 2 arguments of type float, which are the width and height of the display window.
-The draw and MoveUp/Down methods work based off of ItemIndex, they change the color of displayed text 
to indicate choice and increments/decrements ItemIndex to allow for actual choice making. See MainLogic_D
 GetPressedItem simply returns the value of ItemIndex.
-Font
-Text

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ADDITIONAL ITEMS
Textbox - class that allows to dynamically gather user input (from keyboard) and print it to the screen
at the same time. Works as an input field, allows for deletion. See Textbox_D.cpp


SwitchToInput/SwitchBack - methods to navigate to the second column of the menu and back,
work by switching to SecondRowIndex.















*/