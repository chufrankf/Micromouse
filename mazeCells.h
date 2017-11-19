#ifndef MAZECELLS_H
#define MAZECELLS_H

/*
1. Make the map
2. Make current location
3. Identify current location
4. Map the sides and front. (back assumed open)
4. Distance to nearest center location
5. Identify direction that minimizes distance
6. running track of how many are in cell. (use struct?)
*/

#include <stdio.h>

typedef struct Cell{
	bool walls[4]; //north, east, west, south
	bool isCenter;
	int tick;
	double distance;

} Cell;


class MazeCells
{
	private:
		int mazeSize;
		Cell maze[16][16];
	public:
		int currRow;
		int currCol;

		// makes the maps
		MazeCells(int x, int y);

		MazeCells(int mazeFile[33][33], int x, int y);

		void printMaze();

		// get current location
		Cell getCell();

		//gets distance
		double getDistance(int row, int col);

		//checks if the location is in center
		bool isMazeCenter();

		// maps the sides and front
		void makeWalls(bool east, bool south, bool west, bool north);
		
		// determines next move
		char getNextMove();

		// determines validity of movement
		bool isValidCell(int row, int col);

		// moves to next location
		void move(char loc);

};


#endif
