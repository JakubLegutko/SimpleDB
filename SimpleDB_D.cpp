/*	The program uses SFML as its graphics library to generate the GUI
The original program was going to be a game, but turned out a database.

The SimpleDB class is the core of the program.
It contains 2 major data fields: the Dane_pola struct, which is used to hold a single record of data,
and a vector of such structs, which is used as storage for the records while the program is running.
Every time I'm refering to data fields from now on, I'm going to talk about members of Dane_pola.
Class methods:

Get_amount_of_records - returns the size of vector containing data structures.

Read_DB - the method takes the record number, and handles to temporary data fields as arguments.
The latter are later used in Read Logic (see MainLogic_D > Read Logic)


Write_Data - the method takes data fields as arguments and fills a temporary data struct, then pushes it to the end
of the data vector.

Init - this starts the database, reading the DB.txt file using a filestream, if exists, and filling the vector with found data.
In order to delimit the data correctly, I decided to make the last data field mandatory, I.E. if this 
data field is left empty, the record will not be read.


Save_Exit - this is called upon correct exit sequence, it reads the whole memory vector, pushing data
to DB.txt file, and popping pushed data from the program vector.


Delete - this takes record number as argument , if the record exists, it deletes it (pops it from memory vector).











*/