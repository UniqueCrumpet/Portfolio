#pragma once
#include "SFML/Graphics.hpp"

class SFML_TitleScreen:
	public sf::Drawable
{
public:
	SFML_TitleScreen(std::string texturefilename, int windowWidth, int windowHeight);//Constructor
	~SFML_TitleScreen();//Destructor

	//methods
	void update(sf::Time elapseTime);


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//Attributes
	sf::Texture m_TitleScreenTexture;
	sf::Sprite m_TitleScreenSprite;

	sf::Texture m_messageTexture;
	sf::Sprite m_messageSprite;

	sf::Time m_flashingTime;
	sf::Time m_timeSinceLastFlash;
	bool m_flashon;

};

