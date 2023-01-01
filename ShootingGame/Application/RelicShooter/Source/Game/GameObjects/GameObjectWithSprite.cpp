#include "GameObjectWithSprite.h"

#include "../../Engine/Renderer/Sprite.h"

GameObjectWithSprite::GameObjectWithSprite()
{

}

GameObjectWithSprite::~GameObjectWithSprite()
{

}

void GameObjectWithSprite::Initialise()
{
	m_Sprite.Initialise("sprites/spr_hud_face_raff_0.png");

	m_CollisionRect = m_Sprite.getGlobalBounds();
}

void GameObjectWithSprite::Update()
{
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//{
	//	m_Sprite.move(0, -1);
	//}
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	m_Sprite.move(0, 1);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//{
	//	m_Sprite.move(-1, 0);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//{
	//	m_Sprite.move(1, 0);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	//{
	//	m_Sprite.rotate(-1);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	//{
	//	m_Sprite.rotate(1);
	//}
	
}

sf::Vector2f GameObjectWithSprite::GetPosition()
{
	return m_Sprite.getPosition();
}

void GameObjectWithSprite::SetPosition(float px, float py)
{
	m_Sprite.setPosition(px, py);
}

void GameObjectWithSprite::SetPosition(sf::Vector2f ppos)
{
	m_Sprite.setPosition(ppos);
}

void GameObjectWithSprite::GetPosition(float& x, float& y)
{
	x = m_Sprite.getPosition().x;
	y = m_Sprite.getPosition().y;
}

void GameObjectWithSprite::OnCollision(Collider2D* pCollider2D)
{
	m_Sprite.setScale(0.1f, 0.1f);
}
