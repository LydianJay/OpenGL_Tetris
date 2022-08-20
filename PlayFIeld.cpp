#include "PlayField.h"

s2d::Texture PlayField::m_tetroTexture;

void PlayField::update(float fElapseTime){

	if (m_isGameOver) { std::cout << "Game Over!\n"; return; }


	switch (m_gameState) {

	case GAME_STATE::ON_NORMAL: {
			m_fTimeAccum += fElapseTime;


			if (m_fTimeAccum >= m_fTimePerTick) {

				m_fTimeAccum = 0;


				m_currentTetro.move(0, 1);
				checkIfGameOver();
				if (!isValidState()) {
					m_currentTetro = m_prevState;
					lockTetromino();
					uint8_t yLevel = findLine();

					if (yLevel != 0) {
						m_gameState = GAME_STATE::ON_ANIMATION;
					}

				}
			}
		}
		break;

	case GAME_STATE::ON_ANIMATION:

		uint8_t yLevel = findLine();
		if (m_animation.isAnimationDone()) {
			
			deleteLine(yLevel);
			m_animation.resetFrames();
		}
		
		animateDestruction(yLevel, fElapseTime);
		
		
		if (yLevel == 0)m_gameState = GAME_STATE::ON_NORMAL;
		break;

	}


		

}



void PlayField::init(float x, float y, s2d::S2DGraphics* graphics, int panelWidth, int panelHeight){

	srand(time(0));

	m_xPos = x; m_yPos = y;
	m_graphics = graphics;
	
	m_blockWidth = (float)panelWidth / 25;
	m_blockHeight = (float)panelHeight / 25;
	m_grid = new Block[m_gridHeight * m_gridWidth];

	const char* tempMap =
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"#          #"
		"############";

	for (int y = 0; y < m_gridHeight; y++) {
		for (int x = 0; x < m_gridWidth; x++) {
			char t = tempMap[x + y * m_gridWidth];
			Block temp;
			if (t == '#') {

				
				temp.color = { 115, 115, 115, 255};
				temp.type = BLOCK_TYPE::WALL;
				temp.x = x;
				temp.y = y;

				m_grid[x + y * m_gridWidth] = temp;

			}
			else {

				temp.color = s2d::PXLCLR_BLACK;
				temp.type = BLOCK_TYPE::EMPTY;
				temp.x = x;
				temp.y = y;

				m_grid[x + y * m_gridWidth] = temp;

			}
		}
	}

	initTetromino();
	m_prevState = m_currentTetro;
}

void PlayField::rotate(bool isClockWise){

	if (m_gameState != GAME_STATE::ON_NORMAL)return;


	//Tetromino temp = m_currentTetro;
	m_prevState = m_currentTetro;

	m_currentTetro.rotate(isClockWise);

	
	if (!isValidState()) {				// check if rotation is valid

		m_currentTetro = m_prevState;	// if not valid revert back to the last state/rotation
	}

}

void PlayField::tetroHardDrop() {
	if (m_gameState != GAME_STATE::ON_NORMAL)return;

	while (isValidState()) {		// move downward until hit the ground
		m_prevState = m_currentTetro;
		m_currentTetro.move(0, 1);
	}

	m_currentTetro = m_prevState;	// reset to the last position/state

}



void PlayField::move(int x, int y){
	if (m_gameState != GAME_STATE::ON_NORMAL)return;
	m_prevState = m_currentTetro;		// save the state
	m_currentTetro.move(x, y);			// move 
	
	if (!isValidState()) {	// check if that move is valid
		m_currentTetro = m_prevState;	// returns to last state if not valid
	}

}

uint8_t PlayField::findLine(){
	for (int y = m_gridHeight - 2; y >= 4; y--) {
		bool isALine = true;
		for (int x = 1; x < m_gridWidth - 1; x++) {
			if (m_grid[x + y * m_gridWidth].type == BLOCK_TYPE::EMPTY) { // find a gap in a horizontal line
				isALine = false;
				break;
			}
		}

		if (isALine) {
			return y;
		}
	}

	return 0;
}

void PlayField::drawScore() {

	char buffer[16] = {0};
	_itoa_s(m_score, buffer, 10);
	std::string tex = "Score:" + std::string(buffer);
	m_charRenderer.drawString(m_blockWidth * (m_gridWidth + 1), 0, tex, s2d::PXLCLR_RED);
}

void PlayField::deleteLine(uint8_t yLevel){
	m_score += 5;
	for (int y = yLevel; y >= 4; y--) {
		for (int x = 1; x < m_gridWidth - 1; x++) {
			m_grid[x + y * m_gridWidth] = m_grid[x + (y - 1) * m_gridWidth];
		}
	}
}

void PlayField::draw(){

	
	int xPos = m_currentTetro.getX();
	int yPos = m_currentTetro.getY();
	
	for (int y = 4; y < m_gridHeight; y++) {
		for (int x = 0; x < m_gridWidth; x++) {
			s2d::PIXCOLOR color = m_grid[x + y * m_gridWidth].color;
			m_graphics->drawRect(m_blockWidth * x + m_xPos, m_blockHeight * (y - 4) + m_yPos, m_blockWidth, m_blockHeight, color, m_tetroTexture); // draw playfield tiles/blocks
		
			
			if ( (x >= xPos && x < xPos + 4) && (y >= yPos && y < yPos + 4) ) { // check for the tetromino tiles/blocks

				int indX = x - xPos;		// calculate index y and x
				int indY = y - yPos;			

				Block block = m_currentTetro.getBlock(indX, indY); // get the block/tile

				

				
				if (block.type != BLOCK_TYPE::EMPTY) {			// dont draw tile/block if its empty
					s2d::PIXCOLOR colorP = block.color;
					
					m_graphics->drawRect(m_blockWidth * x + m_xPos, m_blockHeight * (y - 4) + m_yPos, m_blockWidth, m_blockHeight, colorP, m_tetroTexture);

				}
					

			}


			
		
		}
	}

	drawScore();
}

void PlayField::reset(){


	for (int y = 0; y < m_gridHeight; y++) {
		for (int x = 0; x < m_gridWidth; x++) {
			
			Block temp;
			if (m_grid[x + y * m_gridWidth].type != BLOCK_TYPE::WALL ) {


				temp.color = s2d::PXLCLR_BLACK;
				temp.type = BLOCK_TYPE::EMPTY;
				temp.x = x;
				temp.y = y;

				m_grid[x + y * m_gridWidth] = temp;

			}
		}
	}
	

	initTetromino();
	m_isGameOver = false;

}

void PlayField::setSpriteSheet(s2d::S2DSpriteSheet& spr) {
	m_tetroTexture = spr.getTexture(0,0, false, false);
	m_animation.initAnimation(spr, m_graphics, 1, 7, 1.2f);
}

void PlayField::setCharacterRenderer(Text& text) {
	m_charRenderer = text;
}

PlayField::~PlayField(){

	if(m_grid != nullptr)
	delete[] m_grid;
	m_grid = nullptr;

}

void PlayField::checkIfGameOver() {


	for (int x = 1; x < 10; x++) {

		if (m_grid[x + 4 * m_gridWidth].type != BLOCK_TYPE::EMPTY) {
			m_isGameOver = true;
		}

	}


}

void PlayField::animateDestruction(int yLevel, float fElapseTime) {

	for (int x = 1; x < m_gridWidth - 1; x++) {
		s2d::PIXCOLOR color = m_grid[x + yLevel * m_gridWidth].color;
		m_animation.animate(m_blockWidth * x + m_xPos, m_blockHeight * (yLevel - 4) + m_yPos, m_blockWidth, m_blockHeight, fElapseTime);
	}
}

bool PlayField::isValidState(){

	
	int xPos = m_currentTetro.getX();
	int yPos = m_currentTetro.getY();
	int indexX = 0, indexY = 0;
	for (int y = yPos; y < 4 + yPos; y++) {
		for (int x = xPos; x < 4 + xPos; x++) {
			Block block = m_currentTetro.getBlock(indexX, indexY);


			s2d::PIXCOLOR color = block.color;

			if (
				m_grid[x + y * m_gridWidth].type != BLOCK_TYPE::EMPTY
				&&
				block.type != BLOCK_TYPE::EMPTY
				) {

				return false;

			}

			indexX++;
		}
		indexY++;
		indexX = 0;
	}

	return true;


}

void PlayField::initTetromino(){

	int index = rand() % 7;
	
	Tetromino temp;
	temp.setPos(6, 0);

	temp.initBlocks(tetrominoTemplate[index]);

	m_currentTetro = temp;
	m_prevState = m_currentTetro;

}

void PlayField::lockTetromino(){

	int xPos = m_currentTetro.getX();
	int yPos = m_currentTetro.getY();
	int indexX = 0, indexY = 0;
	for (int y = yPos; y < 4 + yPos; y++) {
		for (int x = xPos; x < 4 + xPos; x++) {
			Block block = m_currentTetro.getBlock(indexX, indexY);

			if(block.type == BLOCK_TYPE::BLOCK)
				m_grid[x + y * m_gridWidth] = block;

			indexX++;
		}
		indexY++;
		indexX = 0;
	}


	initTetromino();

}
