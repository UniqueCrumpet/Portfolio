#pragma once
#include "SFML/Graphics.hpp"

class SFML_GameMenu :
	public sf::Drawable, public sf::Transformable
{
public:
	SFML_GameMenu(std::string menufilename, int windowWidth, int windowHeight);//Constructor
	~SFML_GameMenu();//Deconstrunctor

	//Methods
	int update(sf::Time elapsedTime);

private:
	//Methods
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//Attributes
	sf::Texture	m_logo;
	sf::Sprite m_logoSprite;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	sf::FloatRect m_backgroundRect;

	sf::Font				m_gameFont;
	sf::Color				m_highlightedTextColour;
	sf::Color				m_normalOutlineColour;
	sf::Color				m_normalTextColor;
	sf::Color				m_highlightedOutlineColour;
	sf::Vector2f			m_menuItemBorder;
	std::vector<sf::Text>   m_menuText;

	//Different attributes
	int						m_highlightIndex;
	bool					m_prevDownKePressed;
	bool					m_prevUpKeyPressed;
	bool					m_prevReturnKeyPressed;

	enum MENU_ALIGNMENT {
		LEFT_JUSTIFIED,
		CENTRE_JUSTIFIED,
		RIGHT_JUSTIFIED

	};

	MENU_ALIGNMENT			m_menuAlignment;



};

