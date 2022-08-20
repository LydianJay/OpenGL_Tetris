#pragma once
#include <GLSimp2DGraphics.h>
#include <string>
class Text {
public:

	void init(int strChr, int endChar, int strNm, int endNm, s2d::S2DGraphics* graphics, s2d::S2DSpriteSheet& spr);
	void setCharSize(float w, float h);
	void drawString(float x, float y, std::string& str, s2d::PIXCOLOR color);
	void drawString(s2d::Vec2f pos, s2d::Vec2f size,std::string& str, s2d::PIXCOLOR color = s2d::PXLCLR_WHITE);
	s2d::Vec2f getStringSize(std::string& str);
	s2d::Vec2f getSize();

private:
	s2d::S2DGraphics* m_graphics = nullptr;
	s2d::S2DSpriteSheet m_spriteSheet;
	float m_width = 25, m_height = 25;
	int m_strChrIndx, m_endChrIndx, m_strNmIndx, m_endNmIndx;

};

