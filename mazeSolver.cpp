/*
 * mazeSolver.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: frankchu
 */
#include <stdio.h>
#include "mazeCells.h"

#define TESTING 1

int main(){


	// read file
	FILE *mazeData;
	mazeData = fopen("sampleMaze.dat", "r");
	if(mazeData == NULL){
		printf("Error 01: unable to read File main()");
		return 0;
	}

	char buf;
	int fileMaze[33][33];
	int tempRow=0;
	int tempCol=0;
	while ((buf = fgetc(mazeData) )!= EOF){

		if((tempCol >= 33 && buf != '\n') || tempRow >= 33){
			printf("Error 02: maze of incorrect size main()");
			return 0;
		}

		if(buf == '\n'){
			printf("\n");
			tempRow += 1;
			tempCol = 0;
		}
		else{
			printf("%d ", buf - '0');
			fileMaze[tempRow][tempCol] = buf - '0';
			tempCol+=1;
		}
		
	}

	fclose(mazeData);


	// define the initial maze setup
	MazeCells maze(fileMaze, 15, 0);

	maze.printMaze();

	if(TESTING){

		int movementIndex = 0;
		while(!(maze.isMazeCenter())){
			printf("			Current Location: [%d, %d], is Center? %s\n", maze.currRow, maze.currCol, maze.isMazeCenter() ? "true" : "false");

			char nextMove = maze.getNextMove();

			printf("%d. Moved: %c \n",movementIndex, nextMove);
			maze.move(nextMove);
			movementIndex += 1;
		}
		printf("			Current Location: [%d, %d], is Center? %s\n", maze.currRow, maze.currCol, maze.isMazeCenter() ? "true" : "false");

		//printf("Current Location: [%d, %d], is Center? %s\n", maze.currRow, maze.currCol, maze.isMazeCenter() ? "true" : "false");
	}

	// center of maze is 7,8
	// LOAD MAZE HERE from File!!!
	// read in values of sensors determine whether wall or not




	return 0;
}



