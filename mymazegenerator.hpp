#ifndef MYMAZEGENERATOR_HPP
#define MYMAZEGENERATOR_HPP
#include "MazeGenerator.hpp"
#include <iostream>
#include <vector>

class MyMazeGen : public MazeGenerator
{

public:
	MyMazeGen ();
	virtual void generateMaze(Maze& maze);
	int randnum(int x);
	void recursive_func (int x, int y, Maze& maze);
	void set_row_and_col(Maze& maze);
	void print_maze();
	~MyMazeGen();

private:
	int maze_width;
	int maze_height;
	std::vector<std::vector<int>> unvisited;



};








#endif //MYMAZEGENERATOR_HPP //
