#include "SFML_GameMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_GameMenu::SFML_GameMenu(std::string menufilename, int windowWidth, int windowHeight) {
	std::ifstream inputfile(menufilename);

	std::string redString;
	std::string greenString;
	std::string blueString;

	int redInt;
	int greenInt;
	int blueInt;

	

	//Varibles for the size of the screen
	std::string xBorderString;
	std::string yBorderString;

	int xBorderInt;
	int yBorderInt;

	if (inputfile.is_open()) {
		std::string stringLine;


		std::getline(inputfile, stringLine);
		if (inputfile.is_open()) {
			//Load the texture file and set it to the sprite
			m_backgroundTexture.loadFromFile(stringLine);
			m_backgroundSprite.setTexture(m_backgroundTexture);

			//Set the origin, texture rectangle, and position of the sprite
			sf::Vector2u textureSize = m_backgroundTexture.getSize();
			m_backgroundSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_backgroundSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_backgroundSprite.setPosition(0, 0);

			//Set rectangle texture which is centered at 0, 0
			m_backgroundRect.left = -static_cast<float> (textureSize.x / 2);
			m_backgroundRect.top = -static_cast<float> (textureSize.y / 2);
			m_backgroundRect.width = textureSize.x;
			m_backgroundRect.height = textureSize.y;
		}

		//Read the 2nd line - game logo texture
		std::getline(inputfile, stringLine);
		if (inputfile.good()) {
			//Load the texture file and set it to the sprite
			m_logo.loadFromFile(stringLine);
			m_logoSprite.setTexture(m_logo);

			//Set the origin, texture rectangle, and position of the sprite
			sf::Vector2u textureSize = m_logo.getSize();
			m_logoSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_logoSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_logoSprite.setPosition(0, m_backgroundTexture.getSize().y / 2 * 0.9f);//Set the position of the logo 90% down the screen

		}
		//Read the 3rd line - font
		std::getline(inputfile, stringLine);
		if (inputfile.good()) {
			m_gameFont.loadFromFile(stringLine);

		}

		//Read the 4th line - Normal Text Fill Colour(R, G, B)
		std::getline(inputfile, stringLine);
		if (inputfile.good()) {
			//Separate them into three strings (assuming they are separated by white spaces)
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//Convert them into integers
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			//Set the values to m_normalTextColour
			m_normalTextColor = sf::Color(redInt, greenInt, blueInt);

		}

		//Read the 5th line - Normal text outline colour
		std::getline(inputfile, stringLine);
		if (inputfile.good()) {
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_normalOutlineColour = sf::Color(redInt, greenInt, blueInt);

		}

		//Read the 6th line - Highlight text fill colour (R, G, B)
		std::getline(inputfile, stringLine);
		if (inputfile.good()) {
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightedTextColour = sf::Color(redInt, greenInt, blueInt);

		}

		//Read the 7th line - Highlight text outline colour (R, G, B)
		std::getline(inputfile, stringLine);
		if (inputfile.good()) {
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightedOutlineColour = sf::Color(redInt, greenInt, blueInt);

		}

		//Reads the 8th line - Border size of pixels
		std::getline(inputfile, stringLine);
		if (inputfile.good()) {
			std::istringstream stringStream(stringLine);
			stringStream >> xBorderString;
			stringStream >> yBorderString;

			xBorderInt = std::stoi(xBorderString);
			yBorderInt = std::stoi(yBorderString);

			m_menuItemBorder.x = xBorderInt;
			m_menuItemBorder.y = yBorderInt;

		}
		m_menuAlignment = CENTRE_JUSTIFIED;

		//Read the 9th line - Menu text position
		std::getline(inputfile, stringLine);
		if (inputfile.good()) {
			if (!std::strcmp(stringLine.c_str(), "LEFT_JUSTIFIED")) {
				m_menuAlignment = LEFT_JUSTIFIED;
			
			}else if (!std::strcmp(stringLine.c_str(), "CENTRE_JUSTIFIED")) {
				m_menuAlignment = CENTRE_JUSTIFIED;
			
			}else if (!std::strcmp(stringLine.c_str(), "RIGHT_JUSTIFIED")) {
				m_menuAlignment = RIGHT_JUSTIFIED;
			
			}
		
		}
		//Setting the text up for the first line
		sf::Text start;
		start.setFont(m_gameFont);
		start.setCharacterSize(50);
		start.setStyle(sf::Text::Bold);
		start.setFillColor(m_normalTextColor);
		start.setOutlineColor(m_normalOutlineColour);
		start.setOutlineThickness(1.0f);

		sf::Vector2f textpos;//setting position for first menu item
		if (m_menuAlignment == CENTRE_JUSTIFIED) {
			textpos.x = m_backgroundRect.left + m_backgroundRect.width / 2;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		
		}else if (m_menuAlignment == LEFT_JUSTIFIED) {
			textpos.x = m_backgroundRect.left + m_menuItemBorder.x;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		
		}else if (m_menuAlignment == RIGHT_JUSTIFIED) {
			textpos.x = m_backgroundRect.left + m_backgroundRect.width - m_menuItemBorder.x;
			textpos.y = m_backgroundRect.top + m_menuItemBorder.y;
		
		}


		

		do {
			//Read every line for each menu item
			std::getline(inputfile, stringLine);
			if (inputfile.good()) {
				//set the texts position to textpos
				start.setPosition(textpos.x, textpos.y);
				
				//Set the texts string to stringline
				start.setString(stringLine);

				//Set the texts origin to Mid-left coordinate
				sf::FloatRect textbox = start.getLocalBounds();
				if (m_menuAlignment == CENTRE_JUSTIFIED) {
					start.setOrigin(textbox.width / 2, textbox.height / 2);
					
				}else if (m_menuAlignment == LEFT_JUSTIFIED) {
					start.setOrigin(0, textbox.height / 2);
					
				}else if (m_menuAlignment == RIGHT_JUSTIFIED) {
					start.setOrigin(textbox.width, textbox.height / 2);
					
				}

				//Store the text to m_menuText array
				m_menuText.push_back(start);

				//Calculate the next text position by incrementing its y-position
				textpos.y += start.getLocalBounds().height * 1.2f;

			}else
				break;

		} while (true);
		//Initialising the highlight index for the menu select stuff
		m_highlightIndex = 0;
		m_menuText[m_highlightIndex].setFillColor(m_highlightedTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightedOutlineColour);

		m_prevDownKePressed = true;
		m_prevUpKeyPressed = true;
		m_prevReturnKeyPressed = true;

	}
	inputfile.close();
}


SFML_GameMenu::~SFML_GameMenu() {
	//Clear the menu item list
	m_menuText.clear();

}

void SFML_GameMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(m_backgroundSprite, states);
	target.draw(m_logoSprite, states);	

	for (std::size_t count = 0; count < m_menuText.size(); count++) {
		target.draw(m_menuText[count], states);
	
	}

}

int SFML_GameMenu::update(sf::Time elapsedTime) {
	bool m_currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool m_currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool m_currentReturnKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

	//Checking if the down arrow has been pressed recently
	if (m_currentDownKeyPressed && !m_prevDownKePressed) {
		//Set the colour of the CURRENT highlighted menu item to normal colour
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColor);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		//Increment the highlighted index by one, modulated by the number of menu items	
		m_highlightIndex++;
		m_highlightIndex = m_highlightIndex % m_menuText.size();

		//Set the colour of the New highlighted menu item to highlight colour
		m_menuText[m_highlightIndex].setFillColor(m_highlightedTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightedOutlineColour);

	}else if (m_currentUpKeyPressed && !m_prevUpKeyPressed) {
		//Set the colour of the CURRENT highlighted menu item to normal colour
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColor);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		//Increment the highlighted index by one, if it becomes negative then add the number of menu items to it	
		m_highlightIndex--;
		if (m_highlightIndex < 0) {
			m_highlightIndex = m_highlightIndex + m_menuText.size();
		
		}

		//Set the colour of the New highlighted menu item to highlight colour
		m_menuText[m_highlightIndex].setFillColor(m_highlightedTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightedOutlineColour);
	
	}

	m_prevDownKePressed = m_currentDownKeyPressed;
	m_prevUpKeyPressed = m_currentUpKeyPressed;

	//Event for the return key press
	bool hasSelected = false;

	if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed) 
		hasSelected = true;

	m_prevReturnKeyPressed = m_currentReturnKeyPressed;
		
	if (hasSelected)
		return m_highlightIndex;
	else
		return -1;

}

