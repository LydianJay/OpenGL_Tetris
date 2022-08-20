#include "socklib.h"
#include <iostream>
#include "Player.h"
#include "GUIComponent.h"
#include <chrono>
#include <thread>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>




constexpr unsigned short PORT_NUM = 1322;


class TetrisGame {

public:
	TetrisGame() {

		m_window = new s2d::S2DWindow(m_width, m_height, "Tetris", S2D_NO_RESIZE);
		m_graphics = new s2d::S2DGraphics(*m_window);

		stbi_set_flip_vertically_on_load(true);
		
		m_player[0].init(0, 0, m_graphics, m_width, m_height);

		m_graphics->setBlendingState(true);

		int x, y, bpp;
		unsigned char* buffer = stbi_load("res/tetrisSprite.png", &x, &y, &bpp, 4);

		if (buffer == nullptr) {
			m_isRunning = false;
			MessageBox(NULL, "Loading assets failed!", "ERROR", MB_OK);
			return;
		}

		s2d::Texture texture = m_graphics->createTexture(buffer, x, y);
		m_sprSheet.createSpriteSheet(texture, 16, 16);
		free(buffer);

		m_player[0].setSprSheet(m_sprSheet);
		
		s2d::S2DSpriteSheet sp;
		buffer = stbi_load("res/characters.png", &x, &y, &bpp, 4);
		if (buffer == nullptr) {
			m_isRunning = false;
			MessageBox(NULL, "Loading assets failed!", "ERROR", MB_OK);
			return;
		}


		texture = m_graphics->createTexture(buffer,x,y);
		sp.createSpriteSheet(texture, 16, 16);
		m_charRenderer.init(0, 25, 30, 39, m_graphics, sp);
		m_player[0].setCharacterRenderer(m_charRenderer);



		m_mainMenu.init(m_graphics, m_window, &m_charRenderer, m_width/2, m_height/2);
		m_settingsMenu.init(m_graphics, m_window, &m_charRenderer, m_width / 2, m_height / 2);
		m_keyMenu.init(m_graphics, m_window, &m_charRenderer, m_width / 2, m_height / 2);
		m_keyInputForm.init(m_graphics, m_window, &m_charRenderer, m_width / 2, m_height / 2);


		m_keyInputForm.initForm("CHANGE KEY", "ROTATE L");
		m_keyMenu.addForm("CHANGE KEY", "ROTATE L KEY ", 1);
		std::string str = "  ";
		str.at(0) = m_player[0].getInputSetting(PlayerInputSetting::ROT_L);
		m_keyMenu.getForm(1).setTextFieldValue(str);


		m_mainMenu.addSelection((std::string&)std::string("Classic"));
		m_mainMenu.addSelection((std::string&)std::string("Create Server"));
		m_mainMenu.addSelection((std::string&)std::string("Join Server"));
		m_mainMenu.addSelection((std::string&)std::string("Settings"));
		m_mainMenu.addSelection((std::string&)std::string("Exit"));
	
		
		m_settingsMenu.addSelection((std::string&)std::string("Change Key"));
		m_settingsMenu.addSelection((std::string&)std::string("Back"));


		m_keyMenu.addSelection((std::string&)std::string("ROTATE L"));
		m_keyMenu.addSelection((std::string&)std::string("ROTATE R"));
		m_keyMenu.addSelection((std::string&)std::string("HARD DROP"));
		m_keyMenu.addSelection((std::string&)std::string("MOVE LEFT"));
		m_keyMenu.addSelection((std::string&)std::string("MOVE RIGHT"));
		m_keyMenu.addSelection((std::string&)std::string("SOFT DROP"));
		m_keyMenu.addSelection((std::string&)std::string("Back"));

	}

	int main() {
		float fElapseTime = 0, accum = 0;
		uint64_t fps = 0;
		while (!m_window->WindowShouldClose() && m_isRunning) {

			auto t1 = std::chrono::high_resolution_clock::now();
			


			switch (m_appState) {

			case APP_STATE::ON_CLASSIC:

				for (int i = 0; i < m_numOfPlayerActive; i++) {
					m_player[0].input(m_window);
					m_player[0].update(fElapseTime);
				}

				break;

			case APP_STATE::ON_MENU: {


				m_mainMenu.draw();
				m_mainMenu.update();

				selectionID selected = m_mainMenu.getLastSelected();


				switch (selected) {

				case 1:
					m_appState = APP_STATE::ON_CLASSIC;
					break;

				case 2:	// create server

					break;	// join server
				case 3:

					break; // option 
				case 4:
					m_appState = APP_STATE::ON_SETTINGS_MENU;
					break;
				case 5:
					m_isRunning = false;
					break;
				}

			}
				break;

			case APP_STATE::ON_SETTINGS_MENU: {

			
				m_settingsMenu.draw();
				m_settingsMenu.update();

				selectionID s = m_settingsMenu.getLastSelected();



				switch (s) {

				case 1:
					m_appState = APP_STATE::ON_KEY_SETTINGS_MENU;
					break;

				case 2:	
					m_appState = APP_STATE::ON_MENU;
					break;
				}


			}
				break;
			

			case APP_STATE::ON_KEY_SETTINGS_MENU: {


				m_keyMenu.draw();
				m_keyMenu.update();

				selectionID s = m_keyMenu.getLastSelected();
				
				

				switch (s) {

				

				case 7:
					m_appState = APP_STATE::ON_SETTINGS_MENU;
					break;
				}

				std::stringstream ss;
				ss << m_keyMenu.getForm(1).getTextFieldValue().c_str();
				unsigned char key;
				ss >> key;
				m_player[0].setPlayerInputSetting(PlayerInputSetting::ROT_L, key);
			}
				break;

			
			}


			



		

			m_graphics->flushBuffer();
			m_window->ProcessMessage();
			m_window->SwapWindowBuffers();

			fps++;
			auto t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> duration = t2 - t1;
			fElapseTime = duration.count();
			accum += fElapseTime;
			if (accum >= 1.0f) {
				accum = 0;
				std::cout << "FPS: " << fps << '\n';
				fps = 0;
			}

		}

		return 0;
	}


	

	~TetrisGame() {

		if (m_clientNetInterfaceptr != nullptr) {
			delete m_clientNetInterfaceptr;
			m_clientNetInterfaceptr = nullptr;
		}

		if (m_serverNetInterfaceptr != nullptr) {
			delete m_serverNetInterfaceptr;
			m_serverNetInterfaceptr = nullptr;
		}


	}

	


private:
	s2d::S2DGraphics*	m_graphics = nullptr;
	s2d::S2DWindow*		m_window = nullptr;
	const uint16_t		m_width = 1200, m_height = 800;
	s2d::S2DSpriteSheet m_sprSheet;
	Text				m_charRenderer;
	Player				m_player[2];
	uint8_t				m_numOfPlayerActive = 1;
	bool				m_isRunning = true;
	GUIMenu				m_mainMenu;
	GUIMenu				m_settingsMenu;
	GUIMenu				m_keyMenu;
	GUIInputForm		m_keyInputForm;
	INetClient*			m_clientNetInterfaceptr = nullptr;
	INetServer*			m_serverNetInterfaceptr = nullptr;
	APP_STATE			m_appState = APP_STATE::ON_MENU;
};



int main() {

	TetrisGame game;
	return game.main();

}