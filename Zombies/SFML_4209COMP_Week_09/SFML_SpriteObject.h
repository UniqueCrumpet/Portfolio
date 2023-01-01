#pragma once
#include "SFML//Graphics.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class SFML_SpriteObject:
	public sf::Drawable, public sf::Transformable
{
public:
			SFML_SpriteObject();
	virtual	~SFML_SpriteObject();

	//Member fucntions to load and set default texture to use
	bool			setDefaultTexture(std::string textureFilename);
	bool			setDefaultTexture(std::string textureFilename, std::string spriteInfoFilename);

	//Member function to set tint colour
	void			setColour(const sf::Color& color);

	//Member function to get the objects world position
	sf::Vector2f	getWorldPosition();

	//Member function to get the object screen position
	sf::Vector2f	getScreenPosition(sf::Transform cameraScreenTransform);

	//Member function to get the object's global and local bounding rectangles
	sf::FloatRect	getLocalBounds() const;
	sf::FloatRect	getGlobalBounds() const;

	virtual void	update(float elapsedTime);

protected:
	//Member attribute to store the SFML sprite
	sf::Sprite	 m_sprite;

	//Member attribute that points to the current used texture
	sf::Texture* m_spriteTexture;

	//Member attribute to store texture rectangle
	sf::IntRect	 m_textureRectangle;

	//Member attribute to store the origin point
	sf::Vector2f m_spriteOrigin;

	//To help us keep track if the sprite has intialised correctly
	bool		 m_intialised;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//Member attribute for default texture layer
	sf::Texture* m_defaultTexture;


};

