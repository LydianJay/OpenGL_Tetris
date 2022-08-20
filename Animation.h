#pragma once
#include <GLSimp2DGraphics.h>


class Animation {
public:
	void initAnimation(s2d::S2DSpriteSheet& spr, s2d::S2DGraphics* graphics, int start, int end, float time);
	void animate(float x, float y, float w, float h, float fElapseTile);
	void resetFrames();
	bool isAnimationDone();
	
private:
	s2d::S2DSpriteSheet m_sprSheet;
	s2d::S2DGraphics* m_graphics = nullptr;
	float m_fFrameTime = 0.2; // 0.2 secs
	float m_fTimeAccum = 0.0f;
	int m_currentIndex = 0;
	int m_frameStartIndex, m_frameEndIndex;
};

