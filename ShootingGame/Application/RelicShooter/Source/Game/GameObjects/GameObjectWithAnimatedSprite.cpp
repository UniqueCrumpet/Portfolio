#include "GameObjectWithAnimatedSprite.h"

GameObjectWithAnimatedSprite::GameObjectWithAnimatedSprite()
{
}

GameObjectWithAnimatedSprite::~GameObjectWithAnimatedSprite()
{
}

void GameObjectWithAnimatedSprite::Initialise()
{

	
	std::vector<sf::IntRect> rectSize;
	for(int i = 0; i < 6; i++)
	{
		rectSize.push_back(sf::IntRect(256 * i, 0, 256, 256));
	}

		std::vector<sf::Vector2f> originVect(64);
	
	m_AnimatedSprite.AddAnimation(1, "sprites/spritesheet_test.png", rectSize, originVect, 10, true);

	m_AnimatedSprite.SetCurrentAnimation(1);

}

void GameObjectWithAnimatedSprite::Update()
{
	m_AnimatedSprite.Animate();
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_AnimatedSprite.move(0, -2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_AnimatedSprite.move(0, 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_AnimatedSprite.move(-2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_AnimatedSprite.move(2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_AnimatedSprite.rotate(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		m_AnimatedSprite.rotate(1);
	}*/

	m_AnimatedSprite.setScale(0.5, 0.5);

}

sf::Vector2f GameObjectWithAnimatedSprite::GetPosition()
{
	return m_AnimatedSprite.getPosition();
}

void GameObjectWithAnimatedSprite::SetPosition(float px, float py)
{
	m_AnimatedSprite.setPosition(px, py);
}

void GameObjectWithAnimatedSprite::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);
}

void GameObjectWithAnimatedSprite::GetPosition(float& x, float& y)
{
	x = m_AnimatedSprite.getPosition().x;
	y = m_AnimatedSprite.getPosition().y;
}
