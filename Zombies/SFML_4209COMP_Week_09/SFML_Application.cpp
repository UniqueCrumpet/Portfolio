#include "SFML_Application.h"
#include "SFML_GameMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_Application::SFML_Application(int windowWidth, int windowHeight)
	:m_window(sf::VideoMode(windowWidth, windowHeight), "SFML Application", sf::Style::Fullscreen)
	, m_intialised(true)
	, m_screenWidth(windowWidth)
	, m_screenHeight(windowHeight)
	, m_previousDownKeyPressed(false)
	, m_previousUpKeyPressed(false)
	, m_appState(TITLESCREEN)
	,m_mainMenu("Media/MenuInfo/main-menu.txt", windowWidth, windowHeight)
	,m_titleScreen("Media/Textures/title-screen2.png", windowWidth, windowHeight)
	,m_gameWorld(windowWidth, windowHeight, &m_window)
	,m_desiredUpdateTime(sf::seconds(1.f / 60.f))
	,m_timeCounter(sf::seconds(0))
	,m_FPSCounter(0)
	
{
	m_intialised = m_textFont.loadFromFile("Media/Fonts/SegoeMarker.ttf");
	m_messageText.setFont(m_textFont);

	//Setting the scale of the menu
	m_mainMenu.setScale(0.85f, 0.85f);
	m_mainMenu.setPosition(m_screenWidth / 2, m_screenHeight / 2);

	

}

SFML_Application::~SFML_Application() {


}

void SFML_Application::run() {
	if(!m_intialised)
		return;

	sf::Clock clock;

	//Variable to track the last time since update() was last executed
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen()) {
		//Get the elasped time since the last loop
		sf::Time elapsedTime = clock.restart();

		timeSinceLastUpdate += elapsedTime;

		while(timeSinceLastUpdate > m_desiredUpdateTime){
			//Update application states
			update(m_desiredUpdateTime);

			//Subtract m_desiredUpdateTime from timeSinceLastUpdate
			timeSinceLastUpdate -= m_desiredUpdateTime;

		}
		//Calculate FPS
		updateFPS(elapsedTime);

		//Render result to the screen
		render();
	
	}

}

void SFML_Application::update(sf::Time elapsedTime) {
	//Check if the players has closed the window, if so close the application
	bool validEventPoll = m_window.pollEvent(m_event);

	if (m_event.type == sf::Event::Closed && validEventPoll) {
		m_window.close();

	}

	
	//Checking for the keys the are pressed
	bool currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool currentEscapeKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

	//Variables
	int selection;

	//Switching the the states of the game
	switch (m_appState) {
		

		case TITLESCREEN:
			if (currentDownKeyPressed && !m_previousDownKeyPressed) {
				m_appState = MAINMENU;
				

			}else if (currentEscapeKeyPressed) {
				m_appState = EXITING;

			}

			m_previousDownKeyPressed = currentDownKeyPressed;
			m_previousUpKeyPressed = currentUpKeyPressed;

			m_titleScreen.update(elapsedTime);
			break;
		case MAINMENU:
			selection = m_mainMenu.update(elapsedTime);
			if (selection >= 0) {
				if (selection == 0)
					m_appState = GAMEPLAYING;
				else if (selection == 1)
					m_appState = OPTIONMENU;
				else if (selection == 2)
					m_appState = EXITING;
			
			}

			m_previousDownKeyPressed = currentDownKeyPressed;
			m_previousUpKeyPressed = currentUpKeyPressed;

			m_messageText.setString("Main Menu Screen");
			break;
		case OPTIONMENU:
			if (currentDownKeyPressed && !m_previousDownKeyPressed) {
				
				m_appState = GAMEPLAYING;
				

			}else if (currentUpKeyPressed && !m_previousUpKeyPressed) {
				m_appState = MAINMENU;
			
			}else if (currentEscapeKeyPressed) {
				m_appState = EXITING;
			
			}

			m_previousDownKeyPressed = currentDownKeyPressed;
			m_previousUpKeyPressed = currentUpKeyPressed;

			m_messageText.setString("Option Menu Screen");
			break;
		case GAMEPLAYING:
			if (currentEscapeKeyPressed) 
				m_appState = EXITING;

			m_gameWorld.update(elapsedTime.asSeconds());

			break;

		case EXITING:
			m_window.close();
			
			 break;
	}

	m_messageText.setPosition(300, 50);
	m_messageText.setCharacterSize(30);
	
	//Centering the text
	sf::FloatRect textbox = m_messageText.getLocalBounds();
	m_messageText.setOrigin(textbox.width / 2, textbox.height / 2);

}

void SFML_Application::render() {	
	m_window.clear();

	switch (m_appState){
		case TITLESCREEN:
			m_window.draw(m_titleScreen);

			break;
		case MAINMENU:
			m_window.draw(m_mainMenu);

			break;
		case GAMEPLAYING:
			m_window.draw(m_gameWorld);
			m_window.draw(m_messageText);

			break;
		case EXITING:	

			break;
		case OPTIONMENU:
			m_window.draw(m_messageText);

			break;
	}
	m_window.display();

}

void SFML_Application::updateFPS(sf::Time elapsedTime){
	//Increment the time counter by the time since the last render
	m_timeCounter += elapsedTime;

	//Increment FPS counter by one
	m_FPSCounter += 1;

	//If one second has passed
	if(m_timeCounter >= sf::seconds(1.0f)){
		//Set the message text
		m_messageText.setString(
			"Refresh Rate = " + std::to_string(m_FPSCounter) +
			" fps \n" +
			"Time between screen refreshes = " +
			std::to_string(m_timeCounter.asMicroseconds() / m_FPSCounter) +
			" microseconds \n"
		);

		//Take away one second from the time counter
		m_timeCounter -= sf::seconds(1.0f);

		//Reset the FPS counter
		m_FPSCounter = 0;

	}

}
