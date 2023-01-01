#pragma once

#include "Source/Engine/Renderer/Sprite.h"
#include "Source/Engine/Core/GameObject.h"
#include "Source/Engine/Physics/BoxCollider2D.h"

class Collectable : public GameObject, public BoxCollider2D
{
public:
	Collectable();
	~Collectable() override;

	void Initialise() override;
	void Update() override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void GetPosition(float& x, float& y) override;
	void OnCollision(Collider2D* pCollider2D) override;

private:
	Sprite m_Sprite;
};



