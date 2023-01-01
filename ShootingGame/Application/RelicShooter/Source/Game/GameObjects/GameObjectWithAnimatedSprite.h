#pragma once

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
class GameObjectWithAnimatedSprite : public GameObject
{
public:
	GameObjectWithAnimatedSprite();
	~GameObjectWithAnimatedSprite() override;

	void Initialise() override;
	void Update() override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void GetPosition(float& x, float& y) override;


private:
	AnimatedSprite m_AnimatedSprite;
};

