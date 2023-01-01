#pragma once
#include "../../Engine/Core/GameObject.h"
#include <SFML\Graphics.hpp>
class Camera : public GameObject
{
public:

	Camera();
	~Camera();

	void Initialise() override;
	void Update() override;
	sf::Vector2f GetPosition() override;
	void GetPosition(float& x, float& y) override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void SetAsCurrentCamera();
	void RemoveCamera();
private:
	sf::View	m_View;
	bool		m_Active;

};

