//  Created by Andres Quinones
//  Copyright (c) 2015 Andres Quinones. All rights reserved.
//	hw3.cpp
//  MazeSolver Program : Reads a mazefile and prints a path through it.
//							Can find one path or Find all paths
// Date Created : April 5 2015
// Date Finalized : April 15 2015

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Struct to hold the "x" and "y" coordinates of a cell in maze (or any 2D Array)
struct cell
{
	//The "x" coordinate
	int i;
	//The "y" coordinate
	int j;
	//The default constructor
	cell(){}
	//The constructor to initialize i and j at once
	cell(int x, int y)
	{  i=x; j=y;  }
	//Overloaded == operator to allow comparisons between cells
	// @return if both cells contain the same i and j values then return true else false
	bool operator==(cell c) const
	{
		if (this->i == c.i && this->j == c.j)
			return true;
		return false;
	}
	//Overloaded assignment operator to allow cell a = cell b
	void operator=(cell c)
	{this->i = c.i; this->j = c.j;}
};

/*
@pre None
@param 	cell a : a cell in a 2D array
		largestI: largest possible i value for a cell
		largestJ: smallest possible j value for a cell
@return true if the cell is within the bounds passed
		false if it is not
*/
bool WithinBounds(cell a, int largestI, int largestJ)
{
	if(a.i>=0 && a.i <= largestI && a.j>=0 && a.j <= largestJ)
		return true;
	return false;
}

/*
@pre None
@param a_cell : a cell to check for
		path : a path to check
@return true if a_cell is in path
		 false if a_cell is not
*/
bool inPath(cell a_cell,vector<cell> path)
{
	for (int i = 0; i<path.size();i++)
		if(a_cell==path[i])
			return true;
	return false;
}

/*
@pre Cells in path are within the bounds of maze
@post path through contents of maze are numbered and displayed
@param maze : a maze
		path : a path through maze
NOTE : Format only looks nice when maze is a 2D array of strings where each element is a string of size 2
*/
void displayPath(string ** maze, vector<cell> path, int rows, int columns)
{
	//Number the cells that are in the path from 0 - n (the size of path-1)
	for (int i =0; i<path.size(); i++)
	{
		// numbers 0-9 fall here
		if(i<10)
			maze[path[i].i][path[i].j] = " " + to_string(i) ;
			// " " + string(i) because 1 digit numbers are a string
			//  of size 1 but we want to maintain each of size 2

		// 3 Digit numbers that are not multiples of 100 fallhere
		else if (i >100 && i%100 !=0 )
		{
			// If the number has 3 digits only store the last 2 digits of the number
			string s = to_string(i);
			string to_put = s.substr(s.length()-2,s.length()-1);
			
			maze[path[i].i][path[i].j] = to_put;
		}

		// Multiples of 100 and numbers 10-99 fall here
		else
			// We can store the converted string as is
			maze[path[i].i][path[i].j] = to_string(i);
	}

	//print contains of changed array
	for (int i=0;i<rows;i++)
		{
			for (int j=0;j<columns;j++)
				cout << " " << maze[i][j];
			cout << endl;
		}

	// revert contents back to normal
	for (int i =0; i<path.size(); i++)
		maze[path[i].i][path[i].j] = " .";
}
/*
@pre pathTraversed is an empty vector<cells> (needed for the recursion)
@post None
@param maze : a maze
		orgin : where to begin search
		destination : where to end search
		pathTraversed : a path through maze
		maxR : maximum number of rows in maze
		maxC : maximum number of columns in maze
@return path contained in a vector<cells> 
			path will be empty if no path was found
*/
vector<cell> GetAPath(string ** maze_, cell origin, cell destination, vector<cell> pathTraversed, int maxR, int maxC)
{
	pathTraversed.push_back(origin);
	// Base Case 1: if the cell passed is outside the maze or is not " ." then return 
	if(!WithinBounds(origin,maxR-1, maxC-1) || 
			maze_[origin.i][origin.j] != " .")
	{
		vector<cell> empty;
		return empty;
	}
	//At this point the cell might be in the path so push
	// Base Case 2: if destination is reached return the path to this point
	if(origin == destination)
		return pathTraversed;

	//Generate array of neighbors. Can be at max 4
	cell neighbors[4];
	neighbors[0].i = origin.i -1; neighbors[0].j = origin.j; //neighbor above
	neighbors[1].i = origin.i +1; neighbors[1].j = origin.j; //neighbor below
	neighbors[2].i = origin.i; neighbors[2].j = origin.j-1; //neighbor on left
	neighbors[3].i = origin.i; neighbors[3].j = origin.j+1; //neighbor on right


	vector<cell> to_Return;
	for (int i=0; i<4;i++)
	{
		vector<cell> on_Return;
		// if a neighbor is not an already visited cell (a cell in path traversed)
		// then call GetAPath on that neighbor
		if(!inPath(neighbors[i], pathTraversed))
			on_Return = GetAPath(maze_, neighbors[i], destination, pathTraversed, maxR,maxC);
		//If returned is not empty then a path was found so stop checking other neighbors. BREAK OUT
		if(!on_Return.empty())	
		{
			to_Return = on_Return;
			break;
		}
	}

	//Return empty vector of cells if all neighbors was checked for this cell yet no path was found
	//Return a path if one was found
	return to_Return;
}

/*
@pre pathTraversed is an empty vector<cells> (needed for the recursion)
@post All paths through the maze are stored in vector<vector<cell>> allPaths
@param maze : a maze
		orgin : where to begin search
		destination : where to end search
		pathTraversed : a path through maze
		allPaths : a vector of all paths through a maze
		maxR : maximum number of rows in maze
		maxC : maximum number of columns in maze
@return
*/

void GetAllPaths(string ** maze_, cell origin, const cell &destination,
				vector<cell> pathTraversed, vector<vector<cell> > &allPaths,int maxR, int maxC)
{	
	pathTraversed.push_back(origin);
	// Base Case 1: if the cell passed is outside the maze or is not " ." then return 
	if(!WithinBounds(origin,maxR-1, maxC-1) || 
			maze_[origin.i][origin.j] != " .")
		return;
	// Base Case 2: if destination is reached push the path to destination onto all paths
	if(origin == destination)
		{
			allPaths.push_back(pathTraversed);
			return;
		}

	//Generate array of neighbors. Can be at max 4
	cell neighbors[4];
	neighbors[0].i = origin.i -1; neighbors[0].j = origin.j; //above
	neighbors[1].i = origin.i +1; neighbors[1].j = origin.j; //below
	neighbors[2].i = origin.i; neighbors[2].j = origin.j-1; //left
	neighbors[3].i = origin.i; neighbors[3].j = origin.j+1; //right

	for (int i=0; i<4;i++)
		// if a neighbor is not an already visited cell (a cell in path traversed)
		// then call GetAllPath on that neighbor
		if(!inPath(neighbors[i], pathTraversed))
			GetAllPaths(maze_, neighbors[i], destination, pathTraversed, allPaths, maxR,maxC);

	return;
}


int main(int argc, const char * argv[])
{
	//READ DATA IN MAZE.TXT

	// if program wasnt ran properly, cout error and return
	if (argc!=3)
	{
		cout << "Invalid amount of arguments" << endl;
		return 1;
	}

	//Read infomation from argument 2
	int rows,columns;
	ifstream mazeFile;
	mazeFile.open(argv[2]);
	//If file not found then cout error and return
	if(mazeFile.fail())
	{
		cout << "Error: File not found." << endl;
		return 1;
	}
	//Store first two integers in file to rows and columns (for size of 2d array
	mazeFile >> rows >> columns;

	//Create dynamically allocated 2D array
	string ** maze = new string* [rows];
	for(int i = 0; i < rows; ++i)
    	maze[i] = new string[columns];

	for (int i=0;i<rows;i++)
		for (int j=0;j<columns;j++)
		{
			//Get data from file
			string temp;
			mazeFile >>	temp;
			// At this point temp is of size 1 (due to format of file) but
			// we want to store them in strings of size 2 in order to number them later
			maze[i][j] = " " + temp;
		}
	mazeFile.close();
	cell start(0,0);
	cell end(rows-1,columns-1);

	// If 1st argument calls for task 1
	if(strcmp(argv[1],"1")== 0)
	{	
		vector<cell> path;
		cout << "Calling GetAPath function on maze."<< endl;
		path = GetAPath(maze, start, end, path, rows,columns);
		if (path.empty())
			cout << "No path found." << endl;
		else
		{
			cout << "Calling displayPath function on path found."<< endl;
			displayPath(maze, path, rows, columns);
		}
	}

	// If 1st argument calls for task 2
	else if(strcmp(argv[1],"2")==0)
	{	
		vector<cell> path;
		vector<vector<cell> > all_paths;
		cout << "Calling GetAllPaths function on maze."<< endl;
		GetAllPaths(maze, start, end, path, all_paths, rows, columns);
		if (all_paths.empty())
			cout << "No paths found." << endl;
		else
		{
			cout << "Calling displayPath function on each path found."<< endl;
			for(int i=0; i < all_paths.size();i++)
	 		{
				cout << "Path "<< i+1 << ":" << endl;
	 			displayPath(maze, all_paths[i], rows, columns);
			}
		}
	}

	for(int i = 0; i < rows; ++i)
		delete [] maze[i];
	delete [] maze;
	return 1;
}


