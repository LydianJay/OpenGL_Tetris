#include "GUIComponent.h"

GUIComponent::GUIComponent(int w, int h){
	m_rect.setSize(w, h);
}


void GUIComponent::setDrawFormat(GUIFORMAT guiFormat) {
	m_guiFormat = guiFormat;
}



void GUIComponent::init(s2d::S2DGraphics* graphics, s2d::S2DWindow* window, Text* texRender, float x, float y, s2d::Texture tex) {
	m_graphics = graphics;
	m_window = window;
	m_rect.setRect(x, y, m_rect.getRect().z, m_rect.getRect().w);
	m_rect.setTexture(tex);
	m_texRenderer = texRender;
}

void GUIComponent::setBackGround(s2d::PIXCOLOR color) {
	m_backGroundCol = color;
}

void GUIComponent::setForeGround(s2d::PIXCOLOR color) {
	m_foreGroundCol = color;
}








GUIMenu::GUIMenu(int w, int h) : GUIComponent(w, h) { m_guiFormat = GUIFORMAT::CENTERED; }

selectionID GUIMenu::addSelection(std::string& str)
{
	uint32_t t = str.size();
	m_strArry.push_back(std::move(str));
	float w = (t + 2) * m_texRenderer->getSize().x;
	float h = (m_strArry.size() + 2) * m_texRenderer->getSize().y;
	float fx = m_rect.getRect().x;
	if (w < m_rect.getRect().z) w = m_rect.getRect().z;
	else {
		float fDif = w - m_rect.getRect().z;
		fx -= fDif / 2;
	}
	

	m_rect.setRect(fx, m_rect.getRect().y, w, h);
	
	

	return t;
}

selectionID GUIMenu::getLastSelected() {

	selectionID id = m_lastID;
	m_lastID = 0;
	return id;
}

void GUIMenu::addForm(std::string title, std::string str, uint32_t selectID) {

	GUIInputForm form;
	form.init(m_graphics, m_window, m_texRenderer, m_rect.getRect().x, m_rect.getRect().y);
	form.initForm(title, str);
	m_forms.insert(std::make_pair(selectID, std::move(form)));
	
}

GUIInputForm& GUIMenu::getForm(uint32_t selectID) {
	
	
	if (m_forms.find(selectID) == m_forms.end()) {

		throw std::exception("Invalid Index");
		return (GUIInputForm&)GUIInputForm();
	}
	
	
	return m_forms.at(selectID);
}


void GUIMenu::draw() {

	if (m_isFormActive)return;

	m_graphics->drawRect(m_rect, m_backGroundCol);
	float fHeight = m_rect.getRect().w;
	float totalHeight = m_texRenderer->getSize().y * m_strArry.size();
	float fY = ((fHeight - totalHeight) / 2.0f);
	// need to resize if overlap
	float fWidth = 0;
	for (std::string& str : m_strArry) {

		float temp = m_texRenderer->getStringSize(str).x;

		if (temp > fWidth)fWidth = temp;

	}
	
	int i = 0; float h = m_texRenderer->getSize().y;
	for (std::string& str : m_strArry) {
		s2d::PIXCOLOR color;
		if (i == m_selected) {
			color = s2d::PXLCLR_RED;
		}
		else {
			color = s2d::PXLCLR_BLUE;
		}

		m_texRenderer->drawString(m_rect.getRect().x, (fY + (i * h)) + m_rect.getRect().y, str, color);
		i++;
	}




}

void GUIMenu::update() {
	
	if (m_window == nullptr)return;


	if (m_isFormActive) {


		if (m_forms.find(m_keySelected) == m_forms.end()) {
			m_isFormActive = false;
			return;
		}
		GUIInputForm& i = m_forms.at(m_keySelected);
		
 		i.draw();
		i.update();

		if (!i.getFormActiveState()) {
			m_isFormActive = false;

		}
		return;
	}


	s2d::KeyState ks = m_window->GetKeyState();


	if (ks.state != S2D_KEY_PRESSED) {
		return;
	}
	
	

	switch (ks.key) {


	case 'W':
	case VK_UP:
		m_selected--;
		break;

	case 'S':
	case VK_DOWN:
		m_selected++;
		break;
	case VK_RETURN:
	case VK_SPACE:
		m_lastID = m_selected + 1;
		m_keySelected = m_selected + 1;
		if (m_forms.find(m_keySelected) != m_forms.end()) {
			m_isFormActive = true;
			m_forms.at(m_keySelected).setFormActiveState(true);
			return;
		}
		break;


	}
	if (m_selected >= m_strArry.size()) m_selected = 0;
}

GUIInputForm::GUIInputForm(std::string title, std::string str) {
	initForm(title, str);
}

void GUIInputForm::setTextFieldValue(std::string str) {

	m_textFieldValue = str;
}

std::string GUIInputForm::getTextFieldValue() {
	return m_textFieldValue;
}

void GUIInputForm::initForm(std::string title, std::string str) {
	m_str = str;
	m_title = title;
	float w = (str.size() + 10) * m_texRenderer->getSize().x;
	float h = 4 * m_texRenderer->getSize().y;


	float fx = m_rect.getRect().x;
	if (w < m_rect.getRect().z) w = m_rect.getRect().z;
	else {
		float fDif = w - m_rect.getRect().z;
		fx -= fDif / 2;
	}

	m_rect.setRect(fx, m_rect.getRect().y, w, h);


}

void GUIInputForm::draw() {
	if (!m_thisFormActive)return;

	m_graphics->drawRect(m_rect, m_backGroundCol);
	m_texRenderer->drawString(m_rect.getRect().x, m_rect.getRect().y, m_title, m_foreGroundCol);
	s2d::Vec2f strSize = m_texRenderer->getStringSize(m_str);
	float fy = m_texRenderer->getSize().y + m_rect.getRect().y;
	m_texRenderer->drawString(m_rect.getRect().x, fy, m_str, m_foreGroundCol);

	float x = strSize.x + m_rect.getRect().x + m_texRenderer->getSize().x;
	m_graphics->drawRect(x, fy, m_texRenderer->getStringSize(m_textFieldValue).x, m_texRenderer->getSize().y, m_foreGroundCol);
	m_texRenderer->drawString(x, fy, m_textFieldValue, m_backGroundCol);

}

void GUIInputForm::update() {
	
	if (!m_thisFormActive)return;

	s2d::KeyState ks = m_window->GetKeyState();

	if (ks.state == S2D_KEY_PRESSED) {


		if (ks.key == VK_ESCAPE) {

			m_thisFormActive = false;
			return;
		}


		std::string k = " ";
		k.at(0) = ks.key;
		setTextFieldValue(k);
	}


}

void GUIInputForm::setFormActiveState(bool state) { m_thisFormActive = state; }

bool GUIInputForm::getFormActiveState(){ return m_thisFormActive; }

