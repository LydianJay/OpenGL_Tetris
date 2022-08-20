#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <GLSimp2DGraphics.h>
#include "Text.h"
#include "CommonTypes.h"

// This is getting out of hand

class GUIComponent {

public:
	GUIComponent() = default;
	GUIComponent(int w, int h);
	void setDrawFormat( GUIFORMAT guiFormat);
	void init(s2d::S2DGraphics* graphics, s2d::S2DWindow* window, Text* texRender,float x = 0, float y = 0, s2d::Texture tex = {-1,0,0});
	void setBackGround(s2d::PIXCOLOR color);
	void setForeGround(s2d::PIXCOLOR color);
	virtual void draw() = 0;
	virtual void update() = 0;

protected:
	s2d::S2DGraphics*	m_graphics = nullptr;				// graphics renderer
	s2d::S2DWindow*		m_window = nullptr;					// Window use for getting input from user
	s2d::S2DRect		m_rect;								// Component Rectangle Area
	Text*				m_texRenderer;						// text renderer
	GUIFORMAT			m_guiFormat = GUIFORMAT::LEFT;		// unused
	s2d::PIXCOLOR		m_backGroundCol = s2d::PXLCLR_WHITE;
	s2d::PIXCOLOR		m_foreGroundCol = s2d::PXLCLR_BLUE;
};



class GUIInputForm;
class GUIMenu : public GUIComponent {
public:
	GUIMenu(int w, int h);
	GUIMenu() = default;
	selectionID addSelection(std::string& str);
	selectionID	getLastSelected();
	void addForm(std::string title, std::string str, uint32_t selectID);
	GUIInputForm& getForm(uint32_t selectID);
	void draw() override;
	void update() override;
	
private:
	std::vector<std::string> m_strArry;
	std::unordered_map<uint32_t, GUIInputForm> m_forms;
	selectionID			m_lastID = 0;
	uint32_t			m_selected = 0;
	uint32_t			m_keySelected = 0;
	bool				m_isFormActive = false;
	
};


class GUIInputForm : public GUIComponent {
public:
	GUIInputForm() = default;
	GUIInputForm(std::string title, std::string str);
	void setTextFieldValue(std::string str);
	std::string getTextFieldValue();
	void initForm(std::string title, std::string str);
	void draw() override;
	void update() override;
	
	void setFormActiveState(bool state);
	bool getFormActiveState();

private:
	std::string			m_title;
	std::string			m_str;
	std::string			m_textFieldValue = "";
	bool				m_thisFormActive = false;
};