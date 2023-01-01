#pragma once
#include "SFML/Graphics.hpp"
#include "SFML_TitleScreen.h"
#include "SFML_GameMenu.h"
#include "SFML_GameWorldLayer.h"
#include "SFML_GameWorld.h"

class SFML_Application:
	public sf::NonCopyable
{
public:

	SFML_Application(int windowWidth, int windowHeight);//constructor
	~SFML_Application();//Deconstructor

	//Methods
	void run();

private:

	//Methods
	void update(sf::Time elapsedTime);
	void render();

	//Method to update FPS data
	void updateFPS(sf::Time elapsedTime);

	//True of the application has been initialized successfully
	bool m_intialised;

	//Attributes for the size of the window
	sf::RenderWindow m_window;
	std::size_t m_screenWidth;
	std::size_t m_screenHeight;

	//Member attributes for capturing events
	sf::Event m_event;

	//Application state enumeration
	enum AppState {
		TITLESCREEN,
		MAINMENU,
		GAMEPLAYING,
		EXITING,
		OPTIONMENU
	};

	//Objects?/Attributes
	sf::Font m_textFont;
	sf::Text m_messageText;

	AppState m_appState;

	SFML_TitleScreen m_titleScreen;

	SFML_GameMenu m_mainMenu;

	bool m_previousDownKeyPressed;
	bool m_previousUpKeyPressed;

	//Member attributes for FPS data
	sf::Time				m_timeCounter;
	sf::Time				m_desiredUpdateTime;
	std::size_t				m_FPSCounter;

	//Game wolrd object that contains m_gameWorldLayerList and m_camera
	SFML_GameWorld			m_gameWorld;

	

};

