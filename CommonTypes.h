#pragma once
#include <string>
#include <GLSimp2DTypes.h>
#include <iostream>




typedef uint32_t selectionID;


enum class State {
	ACTIVE, INACTIVE
};


enum class BLOCK_TYPE {

	WALL, BLOCK, EMPTY, BOMB
};


enum class GAME_STATE {
	ON_ANIMATION, ON_PAUSE, ON_NORMAL

};

enum class APP_STATE {

	ON_MENU, ON_CREATE_SV, ON_JOIN_SV, ON_SETTINGS_MENU, ON_KEY_SETTINGS_MENU, ON_CLASSIC, ON_MULTIPLAYER
};


struct PlayerInputSetting {
	static unsigned char ROT_L, ROT_R, HRD_DRP, LEFT, RIGHT, DOWN; // index for the inputs
	unsigned char inputs[6];
};




struct Block {
	s2d::PIXCOLOR color;
	State state;
	BLOCK_TYPE type;
	unsigned char x, y;
};



enum class TetrominoType{
	T_TYPE, L_TYPE, L_INV_TYPE, Z_TYPE, Z_INV_TYPE, QUAD_TYPE, LINE_TYPE
};


enum class GUIFORMAT {
	CENTERED, LEFT, RIGHT
};


static const std::string tetrominoTemplate[] = {

	" #  "	
	" #  "	
	" #  "	
	" #  " ,

	"    "	
	"#   "	
	"### "	
	"    ",

	"    "	
	"  # "	
	"### "	
	"    ",

	"    "	
	" ## "	
	" ## "	
	"    ", 

	"    "	
	" ## "	
	"##  "	
	"    ", 

	"    "	
	"##  "	
	" ## "	
	"    ", 

	"    "
	" #  "
	"### "
	"    "
};

