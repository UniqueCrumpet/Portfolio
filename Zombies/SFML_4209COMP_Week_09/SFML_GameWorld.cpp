#include "SFML_GameWorld.h"
#include <stdlib.h>

SFML_GameWorld::SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow)
	:m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_camera(windowWidth, windowHeight)
{
	//Create a gameworld layer object using the wall.png texture
	SFML_GameWorldLayer* background = new SFML_GameWorldLayer("Media/Textures/dirt.png", 1.0f, windowWidth, windowHeight);
	SFML_GameWorldLayer* fog = new SFML_GameWorldLayer("Media/Textures/fog.png", 0.8f, windowWidth, windowHeight);
	SFML_GameWorldLayer* foreground = new SFML_GameWorldLayer("Media/Textures/wire.png", 0.3f, windowWidth, windowHeight);

	//Sort the game world in descending order
	std::sort(m_gameWorldLayerList.begin(), m_gameWorldLayerList.end(), layerSortFunction);

	//Inserting it into the array
	m_gameWorldLayerList.push_back(background);
	m_gameWorldLayerList.push_back(fog);
	m_gameWorldLayerList.push_back(foreground);

	m_cameraPosition = sf::Vector2f(0, 0);

	//Store the address of the parent render window to m_parentWindow
	m_parentWindow = parentWindow;

	m_numberOfZombies = 3;
	for (int i = 0; i < m_numberOfZombies; i++) {
		SFML_NPCSpriteObject* npcSprite = new SFML_NPCSpriteObject();
		npcSprite->setIdleAnimation("Media/Textures/zombie-idle.png", "Media/SpriteInfo/zombie-idle.txt", 1.0f);
		npcSprite->setWalkingAnimation("Media/Textures/zombie-move.png", "Media/SpriteInfo/zombie-move.txt", 1.0f);
		npcSprite->setAttackingAnimation("Media/Textures/zombie-attack.png", "Media/SpriteInfo/zombie-attack.txt", 1.0f);

		npcSprite->setPosition(rand() % 4000 - 2000, rand() % 4000 - 2000);
		npcSprite->setTargetLocation(sf::Vector2f(rand() % 4000 - 2000, rand() % 4000 - 2000));
		m_zombieCharacterList.push_back(npcSprite);
	}

	//Initializing the hero sprite
	m_playerCharacter = new SFML_PlayableSpriteObject();
	//Hero flashlight sprite
	m_playerCharacter->setFlashlightIdleAnimation("Media/Textures/hero_flashlight_idle.png", "Media/SpriteInfo/hero_flashlight_idle.txt", 1.0f);
	m_playerCharacter->setFlashlightWalkingAnimation("Media/Textures/hero_flashlight_move.png", "Media/SpriteInfo/hero_flashlight_move.txt", 1.0f);
	m_playerCharacter->setFlashlightMeleeAnimation("Media/Textures/hero_flashlight_melee.png", "Media/SpriteInfo/hero_flashlight_melee.txt", 1.0f);

	//Hero melee sprite
	m_playerCharacter->setKnifeIdleAnimation("Media/Textures/hero_knife_idle.png", "Media/SpriteInfo/hero_knife_idle.txt", 1.0f);
	m_playerCharacter->setKnifeWalkingAnimation("Media/Textures/hero_knife_move.png", "Media/SpriteInfo/hero_knife_move.txt", 1.0f);
	m_playerCharacter->setKnifeMeleeAnimation("Media/Textures/hero_knife_melee.png", "Media/SpriteInfo/hero_knife_melee.txt", 1.0f);

	//Hero gun sprite
	m_playerCharacter->setPistolIdleAnimation("Media/Textures/hero_pistol_idle.png", "Media/SpriteInfo/hero_pistol_idle.txt", 1.0f);
	m_playerCharacter->setPistolWalkingAnimation("Media/Textures/hero_pistol_move.png", "Media/SpriteInfo/hero_pistol_move.txt", 1.0f);
	m_playerCharacter->setPistolMeleeAnimation("Media/Textures/hero_pistol_melee.png", "Media/SpriteInfo/hero_pistol_melee.txt", 1.0f);
	m_playerCharacter->setPistolShootAnimation("Media/Textures/hero_pistol_shoot.png", "Media/SpriteInfo/hero_pistol_shoot.txt", 1.0f);

	m_playerCharacter->equipFlashlight();
	m_playerCharacter->equipKnife();
	m_playerCharacter->equipPistol();
	m_playerCharacter->toIdleState();

	m_playerCharacter->setPosition(0, 0);

}

SFML_GameWorld::~SFML_GameWorld()
{
	//Clear the gameworld list
	for (std::vector<SFML_GameWorldLayer*>::iterator it = m_gameWorldLayerList.begin(); it != m_gameWorldLayerList.end(); it++) {
		delete(*it);

	}
	m_gameWorldLayerList.clear();

	//Clear the spriteObject list
	for (std::vector<SFML_SpriteObject*>::iterator it = m_spriteObjectList.begin(); it != m_spriteObjectList.end(); it++) {
		delete(*it);

	}
	m_spriteObjectList.clear();

}

void SFML_GameWorld::processEvents(float elapsedTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
		m_camera.zoomUp(elapsedTime);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
		m_camera.zoomDown(elapsedTime);

	}

	m_camera.setPosition(m_cameraPosition);

	//get camera transform (world -> screen)
	sf::Transform transform;
	transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	//take inverse (screen -> world)
	sf::Transform inv = transform.getInverse();

	//get mouse position(in screen space)
	sf::Vector2f mouseScreenPosition = sf::Vector2f(sf::Mouse::getPosition(*m_parentWindow));

	//convert to world space coordinate
	sf::Vector2f wp = inv.transformPoint(mouseScreenPosition);

	SFML_BulletSpriteObject* bullet = m_playerCharacter->processEvents(elapsedTime, transform, mouseScreenPosition);
	if (bullet)
		m_bulletList.push_back(bullet);

	//collision detection
	sf::FloatRect boundingBoxPlayer = m_playerCharacter->getGlobalBounds();

	sf::FloatRect boundingBoxNPC;

	sf::FloatRect boundingBoxBullet;
	sf::Transform invBullet;


	for (unsigned int count = 0; count < m_zombieCharacterList.size(); count++) {
		boundingBoxNPC = m_zombieCharacterList[count]->getGlobalBounds();

		//Player and zombie collision
		if (boundingBoxNPC.intersects(boundingBoxPlayer))
			m_zombieCharacterList[count]->setColour(sf::Color(128, 0, 0));

		else
			m_zombieCharacterList[count]->setColour(sf::Color(255, 255, 255));

	}

}

void SFML_GameWorld::update(float elapsedTime)
{
	processEvents(elapsedTime);

	//Update the sprite object
	for (unsigned int counter = 0; counter < m_spriteObjectList.size(); counter++) {
		m_spriteObjectList[counter]->update(elapsedTime);

	}

	m_playerCharacter->update(elapsedTime);
	m_camera.setPosition(m_playerCharacter->getWorldPosition());

	//update each zombie in the list
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++) {
		m_zombieCharacterList[counter]->update(elapsedTime);

	}

	//Updating all bullets----
	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++) {
		m_bulletList[counter]->update(elapsedTime);

	}

	for (int counter = 0; counter < m_gameWorldLayerList.size(); counter++) {
		m_gameWorldLayerList[counter]->followCamera(&m_camera);
		m_gameWorldLayerList[1]->update(elapsedTime);

	}

}

void SFML_GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (unsigned int counter = 0; counter < m_gameWorldLayerList.size(); counter++) {
		if (m_gameWorldLayerList[counter]->getParallaxFactor() >= 1.0f)
			target.draw(*m_gameWorldLayerList[counter]);

	}

	//Get the camera view-projection transform and set it to the renderstate
	sf::RenderStates renderState;
	renderState.transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	//Draw each bullet object in the list
	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++) {
		target.draw(*m_bulletList[counter], renderState);

	}

	target.draw(*m_playerCharacter, renderState);

	//Draw each zombie object in the list
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++) {
		target.draw(*m_zombieCharacterList[counter], renderState);

	}

	//Render each world layer with paralax factor < 1.0
	for (unsigned int counter = 0; counter < m_gameWorldLayerList.size(); counter++) {
		if (m_gameWorldLayerList[counter]->getParallaxFactor() < 1.0f)
			target.draw(*m_gameWorldLayerList[counter]);
	
	}


}

bool SFML_GameWorld::layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b) {
	return (a->getParallaxFactor() > b->getParallaxFactor());

}
