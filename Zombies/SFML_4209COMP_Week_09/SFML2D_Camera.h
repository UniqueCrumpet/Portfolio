#pragma once
#include "SFML/Graphics.hpp"

class SFML2D_Camera
{
public:
	SFML2D_Camera(int projectileWindowWidth, int projectileWindowHeight);
	~SFML2D_Camera();

	//Function to get the visible area of the game world
	sf::FloatRect			getCameraWindow(float parallaxFactor);

	//Function to set the virtual cameras window
	void					setPosition(sf::Vector2f target);

	//Functions to increase and decrease camera's zoom level
	void					zoomUp(float elaspedTime);
	void					zoomDown(float elaspedTime);

	//Member functions to get camera view and projection
	sf::Transform			getViewTransform() const;
	sf::Transform			getProjTransform() const;

private:
	//Member attribute to store the visible area width and height
	sf::Vector2f			m_cameraWindowSize;
	//Member attribute to store the camera position
	sf::Vector2f			m_cameraPosition;

	//Member attribute to store camera zoom level to emulate height
	float					m_cameraZoom;


};

