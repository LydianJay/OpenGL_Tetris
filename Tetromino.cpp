#include "Tetromino.h"

void Tetromino::rotate(bool isClockwise){

	Tetromino temp = *this;
	int x2 = 0;
	int y2 = 0;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			if (isClockwise) {
				x2 = 3 - y;
				y2 = x;
			}
			else {
				x2 = y;
				y2 = 3 - x;
			}



			Block block = temp.getBlock(x, y);
			setBlock(x2, y2, block);
		}
	}
	



}



void Tetromino::move(int x, int y){

	m_xPos += x;
	m_yPos += y;

}



void Tetromino::setPos(int x, int y) {

	m_xPos = x;
	m_yPos = y;
}

void Tetromino::setBlock(int x, int y, Block block){
	m_blocks[x + y * 4] = block;
}

int Tetromino::getX()
{
	return m_xPos;
}

int Tetromino::getY()
{
	return m_yPos;
}

void Tetromino::initBlocks(std::string block) {
	
	srand(time(0));
	unsigned char r = (rand() % 255) + 50, g = (rand() % 255) + 50, b = (rand() % 255) + 50;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			char t = block[x + y * 4];

			if (t == '#') {
				m_blocks[x + y * 4].state = State::ACTIVE;
				m_blocks[x + y * 4].type = BLOCK_TYPE::BLOCK;
				m_blocks[x + y * 4].color ={r, g, b, 255};
				m_blocks[x + y * 4].x = x;
				m_blocks[x + y * 4].y = y;
			}
			else {
				m_blocks[x + y * 4].state = State::INACTIVE;
				m_blocks[x + y * 4].type = BLOCK_TYPE::EMPTY;
				m_blocks[x + y * 4].color = s2d::PXLCLR_BLACK;
				m_blocks[x + y * 4].x = x;
				m_blocks[x + y * 4].y = y;
			}
		}
	}

}

Block& Tetromino::getBlock(int x, int y){
	return m_blocks[x + y * 4];
}
