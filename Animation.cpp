#include "Animation.h"
#include <thread>
#include <chrono>
void Animation::initAnimation(s2d::S2DSpriteSheet& spr, s2d::S2DGraphics* graphics, int start, int end, float time) {

	m_graphics = graphics;
	m_sprSheet = spr;
	m_frameStartIndex = start;
	m_frameEndIndex = end;
	m_fFrameTime = time;

}

void Animation::animate(float x, float y, float w, float h, float fElapseTime) {

	m_fTimeAccum += fElapseTime;

	if (m_fTimeAccum >= m_fFrameTime) {
		m_fTimeAccum = 0;
		


		if(m_currentIndex <= m_frameEndIndex)
		m_currentIndex++;
	}

	m_graphics->drawRect(x, y, w, h, s2d::PXLCLR_WHITE, m_sprSheet.getTexture(m_currentIndex, 0, false, false));

}

void Animation::resetFrames() {
	m_currentIndex = 0;
	m_fTimeAccum = m_frameStartIndex;

}

bool Animation::isAnimationDone()
{

	if (m_currentIndex >= m_frameEndIndex)return true;
	return false;
}


