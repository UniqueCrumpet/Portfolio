#include "Collectable.h"

#include "GameObjectWithSprite.h"
#include "../../Engine/Renderer/Sprite.h"

Collectable::Collectable()
{

}

Collectable::~Collectable()
{

}

void Collectable::Initialise()
{
	m_Sprite.Initialise("sprites/spr_hud_face_raff_0.png");

}

void Collectable::Update()
{
	this->m_CollisionRect = this->m_Sprite.getGlobalBounds();

}

sf::Vector2f Collectable::GetPosition()
{
	return m_Sprite.getPosition();
}

void Collectable::SetPosition(float px, float py)
{
	m_Sprite.setPosition(px, py);
}

void Collectable::SetPosition(sf::Vector2f ppos)
{
	m_Sprite.setPosition(ppos);
}

void Collectable::GetPosition(float& x, float& y)
{
	x = m_Sprite.getPosition().x;
	y = m_Sprite.getPosition().y;
}

void Collectable::OnCollision(Collider2D* pCollider2D)
{
	m_Sprite.setScale(0.1f, 0.1f);
}
