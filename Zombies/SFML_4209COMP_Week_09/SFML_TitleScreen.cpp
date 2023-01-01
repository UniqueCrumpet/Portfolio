#include "SFML_TitleScreen.h"

SFML_TitleScreen::SFML_TitleScreen(std::string texturefilename, int windowWidth, int windowHeight) {
	m_TitleScreenTexture.loadFromFile(texturefilename);

	m_TitleScreenSprite.setTexture(m_TitleScreenTexture);

	sf::Vector2u bkTextureSize = m_TitleScreenTexture.getSize();	
	m_TitleScreenSprite.setTextureRect(sf::IntRect(0, 0, bkTextureSize.x, bkTextureSize.y));

	m_TitleScreenSprite.setPosition(0, 0);//Setting the position of the sprite to the top left corner

	m_messageTexture.loadFromFile("Media/Textures/continue.png");
	m_messageSprite.setTexture(m_messageTexture);

	//Setting the position of the message 
	m_messageSprite.setPosition(windowWidth * 0.5f, windowHeight * 0.75f);
	//Centering the text
	sf::Vector2u msgTextureSize = m_messageTexture.getSize();
	m_messageSprite.setOrigin(msgTextureSize.x / 2, msgTextureSize.y / 2);
	m_messageSprite.setTextureRect(sf::IntRect(0, 0, msgTextureSize.x, msgTextureSize.y));
	m_messageSprite.setColor(sf::Color(255, 0, 0));

	//Controlling the flashing of the text
	m_timeSinceLastFlash = sf::Time::Zero;
	m_flashingTime = sf::seconds(0.2f);


}

SFML_TitleScreen::~SFML_TitleScreen() {

}

void SFML_TitleScreen::update(sf::Time elapseTime) {
	m_timeSinceLastFlash += elapseTime;

	if (m_timeSinceLastFlash > m_flashingTime) {
		m_flashon = !m_flashon;
		m_timeSinceLastFlash -= m_flashingTime;

		if (m_flashon) {
			m_messageSprite.setColor(sf::Color(255, 255, 255));

		}else {
			m_messageSprite.setColor(sf::Color(255, 0, 0));
		
		}
	
	}

}

void SFML_TitleScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(m_TitleScreenSprite);
	target.draw(m_messageSprite);

}