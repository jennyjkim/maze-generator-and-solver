#ifndef MYMAZESOLVER_HPP
#define MYMAZESOLVER_HPP
#include "MazeSolver.hpp"
#include <iostream>
#include <vector>


class MyMazeSolver : public MazeSolver
{

public:
	MyMazeSolver();
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	void set_width_and_height (MazeSolution& mazeSolution);
	void recursive_func (const Maze& maze, MazeSolution& mazeSolution, int x, int y);
	~MyMazeSolver();

private:
	int maze_width; 
	int maze_height;
	std::vector<std::vector<int>> unvisited;

};

#endif //MYMAZESOLVER_HPP//