#ifndef MYMAZESOLVER_CPP
#define MYMAZESOLVER_CPP
#include <iostream>
#include <vector>
#include <ics46/factory/DynamicFactory.hpp>
#include "mymazesolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, 
	MyMazeSolver, "Jenny Kim's Solver (Required)");

MyMazeSolver:: MyMazeSolver() {}

void MyMazeSolver :: set_width_and_height(MazeSolution& mazeSolution)
{
	maze_width = mazeSolution.getWidth(); 
	maze_height = mazeSolution.getHeight();
}

void MyMazeSolver :: recursive_func (const Maze& maze, MazeSolution& mazeSolution, int x_var, int y_var)
{
	if (mazeSolution.isComplete())
		return;

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
			if (((y_var-1) >= 0) && 
				!(maze.wallExists(x_var, y_var, Direction::up)) && 
				(unvisited[y_var-1][x_var]) == 0) 
			{
				if (mazeSolution.isComplete())
					return;
				mazeSolution.extend(Direction::up);
				if (mazeSolution.isComplete())
					return;
				x_new = x_var;
				y_new = y_var-1;
				recursive_func(maze, mazeSolution, x_new, y_new);
			}
		}

		// CHECKING RIGHT
		if (allowed_directions[i]== Direction::right)
		{
			if (((x_var + 1) < maze.getWidth()) && 
				!(maze.wallExists(x_var, y_var, Direction::right)) &&
				(unvisited[y_var][x_var+1])==0)
			{
				if (mazeSolution.isComplete())
					return;
				mazeSolution.extend(Direction::right);
				if (mazeSolution.isComplete())
					return;
				x_new = x_var+1;
				y_new = y_var;
				recursive_func(maze, mazeSolution, x_new, y_new);
			}
		}

		if (allowed_directions[i] == Direction::down)
		{
			if (((y_var + 1) < maze.getHeight()) && 
				!(maze.wallExists(x_var, y_var, Direction::down)) &&
				(unvisited[y_var+1][x_var]) == 0 )
			{
				if (mazeSolution.isComplete())
					return;
				mazeSolution.extend(Direction::down);
				if (mazeSolution.isComplete())
					return;
				x_new = x_var;
				y_new = y_var+1;
				recursive_func(maze, mazeSolution, x_new, y_new);
			}
		}

		if (allowed_directions[i] == Direction::left) 
		{
			if (((x_var - 1) >= 0) && 
				!(maze.wallExists(x_var, y_var, Direction::left)) &&
				(unvisited[y_var][x_var-1]) == 0)
			{
				if (mazeSolution.isComplete())
					return;
				mazeSolution.extend(Direction::left);
				if (mazeSolution.isComplete())
					return;
				x_new = x_var-1;
				y_new = y_var;
				recursive_func(maze, mazeSolution, x_new, y_new);
			}
		}

	}
	// if (x_var == mazeSolution.getEndingCell().first && 
	// 	y_var == mazeSolution.getEndingCell().second)
	// 	{
	// 		std::cout << "ALL DONE!" << std::endl;
	// 		return;
	// 	}

	if (mazeSolution.isComplete())
		return;
	mazeSolution.backUp();
	return;
}

void MyMazeSolver :: solveMaze(const Maze& maze, MazeSolution& mazeSolution) {

	mazeSolution.restart();
	set_width_and_height(mazeSolution);

	// ======= CREATING MATRIX =======
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

	recursive_func(maze, mazeSolution, 0, 0);
	return;
}

MyMazeSolver :: ~MyMazeSolver() {}
#endif //MYMAZESOLVER_CPP//