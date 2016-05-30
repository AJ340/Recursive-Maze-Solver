# Recursive-Maze-Solver
CSCI 235 

README

MazeSolver program by Andres Quinones for CSCI 235

Program compiles using make
After using make these commands are processed:
	g++ -g -std=c++0x -Wall -I.   -c hw3.cpp -o hw3.o
	g++ -g -std=c++0x -Wall -o ./MazeSolver hw3.o -I.  -L/usr/lib -L/usr/local/lib -lm

Usage:
./MazeSolver <TASK_NUM> <INPUT.FILE>
	-Cannot be used any other way. Will result in error and program termination
	-Task number can be 1 or 2

Input file must be in the following format:

<#_Rows_in_Maze> <#_Columns_in_Maze>
<Rectangular grid where . denotes open cell.>

	Example:
15 15 
 . . - - - - - - - . - - - - .
 - . - - - - - - - . - - - - .
 - . - - . . . . . . - - - - .
 - . - - - . - - - . . . . . .
 - . - - - . - - - . - - - - .
 - . . . . . - - - . - - - - .
 - - - . - - . - - . - - - - .
 - - - . - - . . . . . . . . .
 - - - . - - - . - - - - - - .
 . - - . - - - . - - - - - - .
 . . . . . . . . . . . - - - .
 . - - . - - - . - - . - - - .
 . - - . - - - . - - . . . - .
 . . . . - - - - - - - - . - -
 . - - - - - - - - - - - . . .

 NOTE: Numbers on first line must match the size of the grid.
 		ALSO Anything in the grid other than . will represent a closed cell
