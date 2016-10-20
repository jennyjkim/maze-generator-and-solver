#ifndef MYMAZEGENERATOR_CPP
#define MYMAZEGENERATOR_CPP

#include <ics46/factory/DynamicFactory.hpp>
#include "mymazegenerator.hpp"
#include <iostream>
#include <vector>
#include "Maze.hpp"



ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, 
	MyMazeGen, "Jenny Kim's Generator (Required)");

MyMazeGen :: MyMazeGen () {}

int MyMazeGen :: randnum(int x) {
	int num = rand() % x;
	return num;
}

void MyMazeGen :: print_maze() {
	for (int i = 0; i < maze_height; ++i)
	{
		for (int j = 0; j < maze_width; ++j)
		{
			std::cout << unvisited[i][j];
		}
		std::cout << std::endl;
	}
}

void MyMazeGen :: set_row_and_col(Maze& maze)
{
	maze_width = maze.getWidth();
	maze_height = maze.getHeight();
}


 void MyMazeGen :: recursive_func (int x_var, int y_var, Maze& maze)
 {
 	
 	bool complete = true;
 	for (int x = 0; x < maze_height; ++x)
 	{
 		for (int y=0; y < maze_width; ++y)
 		{
 			if (unvisited[x][y]==0 )
 			{
 				complete = false;
 			}
 		}
 	}

 	if (complete == true)
 	{
 		print_maze();
 		return;
 	}

 	unvisited[y_var][x_var] = 1;

	// CHECK WHICH AVAILABLE DIRECTIONS ARE POSSIBLE
	std::vector<Direction> allowed_directions = {Direction::up, Direction::left, Direction::down, Direction::right};
	std::random_shuffle(allowed_directions.begin(), allowed_directions.end());
		
	int x_new;
	int y_new;
	for (int i=0; i < 4; ++i) 
	{
		//CHECKING UP
		if (allowed_directions[i] == Direction::up)
		{
			if (((y_var-1) >= 0) && (unvisited[y_var-1][x_var]) == 0) 
			{
				maze.removeWall(x_var, y_var, Direction::up);
				x_new = x_var;
				y_new = y_var-1;
				recursive_func(x_new, y_new, maze);
			}
		}

		// CHECKING RIGHT
		if (allowed_directions[i]== Direction::right)
		{
			if (((x_var + 1) < maze.getWidth()) && (unvisited[y_var][x_var+1])==0)
			{
				maze.removeWall(x_var, y_var, Direction::right);
				x_new = x_var+1;
				y_new = y_var;
				recursive_func(x_new, y_new, maze);
			}
		}

		if (allowed_directions[i] == Direction::down)
		{
			if (((y_var + 1) < maze.getHeight()) && (unvisited[y_var+1][x_var]) == 0 )
			{

				maze.removeWall(x_var, y_var, Direction::down);
				x_new = x_var;
				y_new = y_var+1;
				recursive_func(x_new, y_new, maze);
			}
		}

		if (allowed_directions[i] == Direction::left) 
		{
			if (((x_var - 1) >= 0) && (unvisited[y_var][x_var-1]) == 0)
			{
				maze.removeWall(x_var,y_var, Direction::left);
				x_new = x_var-1;
				y_new = y_var;
				recursive_func(x_new, y_new, maze);
			}
		}

	}
	
	return;
 }


void MyMazeGen :: generateMaze(Maze& maze) {
	// ========= CREATING MAZE OUTLINE ==========
	maze.addAllWalls();
	set_row_and_col(maze);

	//========= CREATING UNVISITED MATRIX =========

	unvisited.resize(maze_height);
	for (int i=0; i < maze_height; ++i) 
	{
		unvisited[i].resize(maze_width);
	}

	for (int i = 0; i < maze_height; ++i)
	{
		for (int j = 0; j < maze_width; ++j)
		{
			unvisited[i][j] = 0;
		}
	}


	// GETTING THE STARTING POINT TO BE FALSE (empty)
	int y_var = randnum(maze_height);
	int x_var = randnum(maze_width);
	recursive_func(x_var, y_var, maze);
	return;
}

MyMazeGen :: ~MyMazeGen() {}

#endif //MYMAZEGENERATOR_CPP //