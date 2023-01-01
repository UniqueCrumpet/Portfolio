#pragma once
#include "SFML_GameWorldLayer.h"
#include "SFML_SpriteObject.h"
#include "SFML_AnimatedSpriteObject.h"
#include "SFML_NPCSpriteObject.h"
#include "SFML_BulletSpriteObject.h"
#include "SFML_PlayableSpriteObject.h"

class SFML_GameWorld:
	public sf::Drawable
{
public:
	SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow);//Constructor
	~SFML_GameWorld();//Deconstructor

	void					update(float elapsedTime);
	
	

private:
	void					processEvents(float elapsedTime);
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//Member attributes to store render window dimension
	int											m_windowWidth;
	int											m_windowHeight;


	//The array to store the game world layers
	std::vector<SFML_GameWorldLayer*>			m_gameWorldLayerList;

	//The member attribute to store the camera object
	SFML2D_Camera								m_camera;

	//The member attribute to store the camera position
	sf::Vector2f								m_cameraPosition;

	SFML_SpriteObject							m_spriteObject;

	sf::RenderWindow*							m_parentWindow;

	//static function to be used to sort SFML_GameWorldLayer Array
	static bool layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b);

	//The array to store the game sprites
	std::vector<SFML_SpriteObject*>				m_spriteObjectList;

	int											m_selectecSpriteObjectID;
	bool										m_prevLeftButtonPressed;

	SFML_AnimatedSpriteObject*					m_animatedObject;
	int											m_idleAnimationID;

	std::vector<SFML_NPCSpriteObject*>			m_zombieCharacterList;
	int											m_numberOfZombies;

	SFML_PlayableSpriteObject*					m_playerCharacter;
	std::vector<SFML_BulletSpriteObject*>		m_bulletList;

};

