#pragma once
#include <cstdint>
#include <ctime>
#include <cstdlib>
#include "Tetromino.h"
#include "Animation.h"
#include "Text.h"
class PlayField{

public:

	/*
		Updates the playfield
		@param fElapseTime - The delta time(time passed between a frame)
	*/
	void update(float fElapseTime);
	/*
		Initialize the PlayField
		@param x, y - the position of the playfield in the screen
		@param graphics - the pointer to the renderer
		@param panelWidth - the width of the window
		@param panelHeight - the height of the window
	*/
	void init(float x, float y, s2d::S2DGraphics* graphics, int panelWidth, int panelHeight);
	/*
		Rotates the current tetromino
		@param isClockWise - boolean flag if the wanted rotation is clockwise
	*/
	void rotate(bool isClockWise);
	/*
		Drops the current tetromino to the buttom
	*/
	void tetroHardDrop();
	/*
	
		Moves the current tetromino
		@param x - the value to increment the x position
		@param y - the value to increment the y position
	*/
	void move(int x, int y);
	/*
		Finds a line in the playfield and calls deleteLine if there is one found
	*/
	uint8_t findLine();
	/*
	
		Deletes a line in the y level provided
		@param yLevel - the y level which will be removed

	*/
	void deleteLine(uint8_t yLevel);
	
	/*
		Displays the playfield and all the tetrominos in the game
	*/
	void draw();
	/*
	* Resets the playfield starts new game
	* 
	*/
	void reset();
	void setSpriteSheet(s2d::S2DSpriteSheet& tex);

	void setCharacterRenderer(Text& text);
	~PlayField();
private:

	float						m_xPos, m_yPos;						// x and y positions of the playfield in the screen
	float						m_fTimeAccum = 0;					// time accumulator
	const float					m_fTimePerTick = 1.0f / 0.8f ;		// the delay in which the tetromino will drop
	const int					m_gridHeight = 24, m_gridWidth = 12;// the playfield row, column
	float						m_blockWidth = 50, m_blockHeight;	// the width and height of each tile/block
	Block*						m_grid = nullptr;					// the playfield grid that contains each tiles
	s2d::S2DGraphics*			m_graphics = nullptr;				// renderer pointer
	Tetromino					m_currentTetro;						// the current tetromino
	Tetromino					m_prevState;						// previous state of the current tetromino
	bool						m_isGameOver = false;				// game over state
	static s2d::Texture			m_tetroTexture;
	GAME_STATE					m_gameState = GAME_STATE::ON_NORMAL;
	Animation					m_animation;
	Text						m_charRenderer;
	float						m_fElapseTime = 0;
	uint32_t					m_score = 0;


	/*
	
		Checks if the current tetromino does not overlaps with tiles/blocks in the grid
		@return - returns true if current tetromino does not overlap with other tiles/blocks
	*/
	bool isValidState();
	/*
		Creates a new tetromino randomly and initialize its color and position
	*/
	void initTetromino();
	/*
		Locks the current tetromino in place to playfield and calls initTetromino() to create a 
		new tetromino 
	*/

	
	void lockTetromino();
	void animateDestruction(int yLevel, float fElapseTime);
	void checkIfGameOver();
	void drawScore();
};

