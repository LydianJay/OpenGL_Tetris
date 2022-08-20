#include "Text.h"

void Text::init(int strChr, int endChar, int strNm, int endNm, s2d::S2DGraphics* graphics, s2d::S2DSpriteSheet& spr) {

	m_endChrIndx = endChar;
	m_endNmIndx = endNm;
	m_strChrIndx = strChr;
	m_strNmIndx = strNm;


	m_graphics = graphics;
	m_spriteSheet = spr;

}

void Text::setCharSize(float w, float h) {
	m_width = w;
	m_height = h;
}


// 65 - 90, 97 - 122, 48 - 57
void Text::drawString(float x, float y, std::string& str, s2d::PIXCOLOR color) {
	
	
	uint32_t size = str.size();
	for (uint16_t i = 0; i < size; i++) {

		char t = str.at(i);
		
		if (t >= 65 && t <= 90) {
			int index = t - 65;
			m_graphics->drawRect(x + (i * m_width), y, m_width, m_height, color, m_spriteSheet.getTexture(index, true));

		}

		else if (t >= 97 && t <= 122) {
			int index = t - 97;
			m_graphics->drawRect(x + (i * m_width), y, m_width, m_height, color, m_spriteSheet.getTexture(index, true));
		}
		if (t >= 48 && t <= 57) {
			int index = t - 48;
			m_graphics->drawRect(x + (i * m_width), y, m_width, m_height, color, m_spriteSheet.getTexture(index,3, true, false));
		}

	}




}

void Text::drawString(s2d::Vec2f pos, s2d::Vec2f size, std::string& str, s2d::PIXCOLOR color) {


	uint32_t length = str.size();
	for (uint16_t i = 0; i < length; i++) {

		char t = str.at(i);

		if (t >= 65 && t <= 90) {
			int index = t - 65;
			m_graphics->drawRect(pos.x + (i * size.x), pos.y, size.x, size.y, color, m_spriteSheet.getTexture(index, true));

		}

		else if (t >= 97 && t <= 122) {
			int index = t - 97;
			m_graphics->drawRect(pos.x + (i * size.x), pos.y, size.x, size.y, color, m_spriteSheet.getTexture(index, true));
		}
		if (t >= 48 && t <= 57) {
			int index = t - 48;
			m_graphics->drawRect(pos.x + (i * size.x), pos.y, size.x, size.y, color, m_spriteSheet.getTexture(index, 3, true, false));
		}

	}

}

s2d::Vec2f Text::getStringSize(std::string& str)
{
	uint32_t size = str.size();


	return { m_width * (size - 1), m_height };

}

s2d::Vec2f Text::getSize()
{
	return {m_width, m_height};
}
