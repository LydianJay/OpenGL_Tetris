#include "Player.h"
#include <iostream>

unsigned char PlayerInputSetting::ROT_L = 0;
unsigned char PlayerInputSetting::ROT_R = 1;
unsigned char PlayerInputSetting::HRD_DRP = 2;
unsigned char PlayerInputSetting::LEFT = 3;
unsigned char PlayerInputSetting::RIGHT = 4;
unsigned char PlayerInputSetting::DOWN = 5;


void Player::input(s2d::S2DWindow* window){

	s2d::KeyState key = window->GetKeyState();


	if (key.state == S2D_KEY_PRESSED) {


		if (key.key == m_playerInputSetting.inputs[PlayerInputSetting::ROT_R]) {
			m_playFieldptr->rotate(true);
		}
		else if(key.key == m_playerInputSetting.inputs[PlayerInputSetting::ROT_L]) {
			m_playFieldptr->rotate(false);
		}
		else if (key.key == m_playerInputSetting.inputs[PlayerInputSetting::LEFT]) {
			m_playFieldptr->move(-1, 0);
		}
		else if (key.key == m_playerInputSetting.inputs[PlayerInputSetting::RIGHT]) {
			m_playFieldptr->move(1, 0);
		}
		else if (key.key == m_playerInputSetting.inputs[PlayerInputSetting::DOWN]) {
			m_playFieldptr->move(0, 1);
		}
		else if (key.key == m_playerInputSetting.inputs[PlayerInputSetting::HRD_DRP]) {
			m_playFieldptr->tetroHardDrop();
		}
	

	}


}

void Player::update(float fElapseTime) {

	m_playFieldptr->draw();
	m_playFieldptr->update(fElapseTime);
	
}

void Player::reset(){
	m_nScore = 0;
	m_playFieldptr->reset();
}

void Player::init(float x, float y, s2d::S2DGraphics* graphics, int panelWidth, int panelHeight) {

	m_playFieldptr = new PlayField;
	m_playFieldptr->init(x, y, graphics, panelWidth, panelHeight);

	// default player input
	m_playerInputSetting.inputs[PlayerInputSetting::HRD_DRP] = VK_SPACE;
	m_playerInputSetting.inputs[PlayerInputSetting::LEFT] = 'A';
	m_playerInputSetting.inputs[PlayerInputSetting::RIGHT] = 'D';
	m_playerInputSetting.inputs[PlayerInputSetting::ROT_L] = 'Q';
	m_playerInputSetting.inputs[PlayerInputSetting::ROT_R] = 'E';
	m_playerInputSetting.inputs[PlayerInputSetting::DOWN] = 'S';
}
void Player::setSprSheet(s2d::S2DSpriteSheet& spr) {

	if (m_playFieldptr != nullptr)
		m_playFieldptr->setSpriteSheet(spr);
}
void Player::setCharacterRenderer(Text& tex) {

	if (m_playFieldptr != nullptr)m_playFieldptr->setCharacterRenderer(tex);

}
unsigned char Player::getInputSetting(unsigned char input)
{
	if (input >= 6)return 0xFF;

	return m_playerInputSetting.inputs[input];
}
void Player::setPlayerInputSetting(unsigned char inputID, unsigned char key) {
	if (inputID >= 6) return;

	m_playerInputSetting.inputs[inputID] = key;

}
Player::~Player() {

	if (m_playFieldptr != nullptr)delete m_playFieldptr;
	m_playFieldptr = nullptr;
}