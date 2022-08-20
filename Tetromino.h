#pragma once
#include "CommonTypes.h"
#include <cstdlib>
#include <ctime>
class Tetromino{

public:
	
	void rotate(bool isClockwise);
	void move(int x, int y);
	void setPos(int x, int y);
	void setBlock(int x, int y, Block block);
	int getX(); int getY();
	void initBlocks(std::string block);
	
	Block& getBlock(int x, int y);
	

private:
	Block m_blocks[4*4];
	int m_xPos, m_yPos;

};

