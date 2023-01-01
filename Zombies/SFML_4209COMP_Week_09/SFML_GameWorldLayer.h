#pragma once
#include "SFML/Graphics.hpp"
#include "SFML2D_Camera.h"

class SFML_GameWorldLayer :
	public sf::Drawable
{
public:
	SFML_GameWorldLayer(std::string textureFileName, float parallaxFactor, int viewportWidth, int viewportHeight);//Constructor
	~SFML_GameWorldLayer();//Deconstructor

	//Methods
	void followCamera(SFML2D_Camera* camera);

	//Member method to set parallax factor after object creation
	void setParallaxFactor(float parallaxFactor);
	//Member method to ger the layer's current parallax factor
	float getParallaxFactor();

	//Method to set the scroll speed
	void setScrollSpeed(sf::Vector2f scrollSpeed);

	void update(float elapsedTime);


private:
	//Methods
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	//Attributes
	sf::Texture				m_layerTexture;
	sf::VertexArray			m_layerVertices;
	float					m_parallaxFactor;

	sf::Vector2f			m_offset;
	sf::Vector2f			m_scrollSpeed;

};

