#pragma once
#include "PlayField.h"
#include "Text.h"
class Player{
public:

	void input(s2d::S2DWindow* window);
	void update(float fElapseTime);
	void reset();

	void init(float x, float y, s2d::S2DGraphics* graphics, int panelWidth, int panelHeight);
	void setSprSheet(s2d::S2DSpriteSheet& spr );
	void setCharacterRenderer(Text& tex);

	unsigned char getInputSetting(unsigned char input);
	void setPlayerInputSetting(unsigned char inputID, unsigned char key);
	Player() = default;
	Player(Player& copy) = delete;
	Player(Player&& move) = delete;
	~Player();

	Player& operator=(Player&) = delete;

private:
	PlayField*				m_playFieldptr = nullptr;
	uint32_t				m_nScore = 0;
	PlayerInputSetting		m_playerInputSetting;

};

