/*
 * mazeCells.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: frankchu
 */

#include <stdio.h>
#include <math.h>
#include "mazeCells.h"

MazeCells::MazeCells(int x, int y){ //define starting and end
	currRow = x;
	currCol = y;

	for(int row = 0; row<16; row++){
		for(int col = 0; col<16; col++){
			
			//default values for all cells
			maze[row][col].walls[0] = false;
			maze[row][col].walls[1] = false;
			maze[row][col].walls[2] = false;
			maze[row][col].walls[3] = false;

			maze[row][col].isCenter = false;
			maze[row][col].tick = 0;
			maze[row][col].distance = MazeCells::getDistance(row, col);

			// top row and bottom row walls are made
			if(row == 0)
				maze[row][col].walls[0] = true; // north
			else if(row == 15)
				maze[row][col].walls[2] = true; // south

			// east col and west col walls are made
			if(col == 0)
				maze[row][col].walls[3] = true; // west
			else if(col == 15)
				maze[row][col].walls[1] = true; // east

			if(row == 7 && col == 8 || row == 7 && col == 7 || row == 8 && col == 7 || row == 8 && col == 8)
				maze[row][col].isCenter = true;

		}
	}


	//set tick at maze location
	maze[currRow][currCol].tick = 1;

}

MazeCells::MazeCells(int mazeFile[33][33], int x, int y){
	currRow = x;
	currCol = y;

	//set defaul
	for(int row = 0; row<16; row++){
		for(int col = 0; col<16; col++){
			
			//default values for all cells
			maze[row][col].walls[0] = false; //north
			maze[row][col].walls[1] = false; //east
			maze[row][col].walls[2] = false; //south
			maze[row][col].walls[3] = false; //west

			maze[row][col].isCenter = false;
			maze[row][col].tick = 0;
			maze[row][col].distance = MazeCells::getDistance(row, col);

			if(row == 7 && col == 8 || row == 7 && col == 7 || row == 8 && col == 7 || row == 8 && col == 8)
				maze[row][col].isCenter = true;
		}



	}

	for(int row = 0; row<33; row++){
		for(int col = 0; col<33; col++){

			if(mazeFile[row][col] == 0){

				if((row + 1)% 2 != 0 || (col + 1)% 2 != 0){
					printf("Error 06: maze 0 value is not even - mazeCells.cpp");
				}

				int setRow = row/2;
				int setCol = col/2;

				if(mazeFile[row - 1][col] == 1) // north
					maze[setRow][setCol].walls[0] = true;
				else if(mazeFile[row - 1][col] == 2)
					maze[setRow][setCol].walls[0] = false;
				else
					printf("Error 05: invalid maze value not 1 or 2 when selecting 0 - mazeCells.cpp\n");

				if(mazeFile[row][col + 1] == 1) // east
					maze[setRow][setCol].walls[1] = true;
				else if(mazeFile[row][col + 1] == 2)
					maze[setRow][setCol].walls[1] = false;
				else
					printf("Error 05: invalid maze value not 1 or 2 when selecting 0 - mazeCells.cpp\n");

				if(mazeFile[row + 1][col] == 1) // south
					maze[setRow][setCol].walls[2] = true;
				else if(mazeFile[row + 1][col] == 2)
					maze[setRow][setCol].walls[2] = false;
				else
					printf("Error 05: invalid maze value not 1 or 2 when selecting 0 - mazeCells.cpp\n");

				if(mazeFile[row][col - 1] == 1) // west
					maze[setRow][setCol].walls[3] = true;
				else if(mazeFile[row][col - 1] == 2)
					maze[setRow][setCol].walls[3] = false;
				else
					printf("Error 05: invalid maze value not 1 or 2 when selecting 0 - mazeCells.cpp\n");

			}

		}
	}


}

void MazeCells::printMaze(){
	printf("\nmaze map completed\n");

	for(int row = 0; row<16; row++){
		for(int col = 0; col<16; col++){
			if(maze[row][col].walls[0])
				printf("__");
			else
				printf("..");
		}
		printf("\n");
		printf("|");
		for(int col = 0; col<16; col++){
			printf("0");
			if(maze[row][col].walls[1])
				printf("|");
			else
				printf(":");

		}
		printf("\n");
	}
	for(int col = 0; col<16; col++){
		if(maze[15][col].walls[2])
			printf("__");
		else
			printf("..");
	}
	printf("\n");

}

Cell MazeCells::getCell(){
	return maze[currRow][currCol];
}

double MazeCells::getDistance(int row, int col){
	return sqrt((row - 7)*(row - 7) + (col - 7)*(col - 7)); // finds distance to top left center. If necessary implement min(tr, tl, br, bl)
}

bool MazeCells::isMazeCenter(){
	return maze[currRow][currCol].isCenter;
}

void MazeCells::makeWalls(bool east, bool south, bool west, bool north){
	maze[currRow - 1][currCol].walls[0] = north; // north
	maze[currRow][currCol + 1].walls[1] = east; // east
	maze[currRow + 1][currCol].walls[2] = south; // south
	maze[currRow][currCol - 1].walls[3] = west; // west
}

//after make walls is done for that cell!
char MazeCells::getNextMove(){

	//possibly want to use pointer vectors or malloc

	int numFreeCells = 0;
	for(int i=0; i<4; i++){
		if(maze[currRow][currCol].walls[i] == false)
			numFreeCells += 1;
	}

	//TESTING
	printf("Number of Free Cells: %d\n", numFreeCells);

	char directionCells[numFreeCells];
	Cell availableCells[numFreeCells];

	int tempCounter = 0;
	for(int i=0; i<4; i++){
		if(maze[currRow][currCol].walls[i] == false){
			switch (i){
			case 0: //north	
				directionCells[tempCounter] = 'n';
				availableCells[tempCounter] = maze[currRow - 1][currCol];
				break;
			case 1: //east
				directionCells[tempCounter] = 'e';
				availableCells[tempCounter] = maze[currRow][currCol + 1];
				break;
			case 2: //south
				directionCells[tempCounter] = 's';
				availableCells[tempCounter] = maze[currRow + 1][currCol];
				break;
			case 3: //west
				directionCells[tempCounter] = 'w';
				availableCells[tempCounter] = maze[currRow][currCol - 1];
				break;
			default:
				printf("Error 66: I dont even know how you can get this error\n");
				break;
			}
			tempCounter += 1;
		}
	}

	// directionCells have directions which are open.
	// give each direction a value in valueCells
	// smallest value is selected
	//		-- ticks
	// 		-- distance 



	double valueCells[numFreeCells];

	for(int i=0; i<numFreeCells; i++){
		valueCells[i] = availableCells[i].distance + (double)20*availableCells[i].tick;
	}

	//TESTING
	for(int i=0; i<numFreeCells; i++){
		printf("%c -> %f\n", directionCells[i], valueCells[i]);
	}

	int minIndex = 0;
	if(numFreeCells > 1){
		for(int i=1; i<numFreeCells; i++){
			if(valueCells[i] < valueCells[minIndex])
				minIndex = i;
		}
	}

return directionCells[minIndex];

}

bool MazeCells::isValidCell(int row, int col){

	if(row > 15 || row < 0 || col > 15 || col < 0)
		return false;
	else
		return true;
}

void MazeCells::move(char loc){

	int nextRow = currRow;
	int nextCol = currCol;

	switch (loc){
	case 'e':
		nextCol += 1;
		break;
	case 's':
		nextRow += 1;
		break;
	case 'w':
		nextCol -= 1;
		break;
	case 'n':
		nextRow -= 1;
		break;
	default:
		printf("Error 03: Invalid Movement 93-mazecells.cpp \n");
		break;
	}

	// if valid .. move
	if (MazeCells::isValidCell(nextRow, nextCol)){
		currRow = nextRow;
		currCol = nextCol;
		maze[currRow][currCol].tick += 1;
		printf("Movedment accepted...\n");
	}
	else{
		printf("Error 04: Invalid Movement 103-mazecells.cpp \n");
	}

}


