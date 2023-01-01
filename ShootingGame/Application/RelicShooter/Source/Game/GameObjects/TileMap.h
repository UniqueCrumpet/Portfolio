#pragma once
#include <istream>

#include "../../Engine/Core/GameObject.h"
#include <SFML\Graphics.hpp> 
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine/Physics/Collider2D.h"
#include "../../Game/GameStates/GameStateTest.h"

struct SpritesheetDef;

class TileMap : public GameObject, public sf::Transformable, public sf::Drawable, public Collider2D
{
public:

	TileMap();
	~TileMap();

	void Initialise() override;
	void Update() override;
	sf::Vector2f GetPosition() override;
	void GetPosition(float& x, float& y) override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void LoadFromFile(const int width, const int height, const char* fileLocation);
	void LoadCollisionMap(const int width, const int height, std::vector<int> map);
	int TileIndexAtPosition(float width, float height);
	std::vector<int> GetMap();
	std::vector<int> GetMapCollision();
	void GetPlayerPosition(GameObject* player);

	bool CollidesWith(Collider2D* pCollider2D) override;
	bool CollidesWith(BoxCollider2D* pBoxCollider2D) override;
	bool CollidesWith(CircleCollider2D* pCircleCollider2D) override;
	bool CollidesWith(TileMap* pTileMap) override;
	bool CollidesWith(TileCollisionBlock* pTileCollisionBlock) override;
	void OnCollision(Collider2D* pCollider2D) override;

	bool LoadFromSpriteSheetDef(SpritesheetDef* pSpriteSheetDef, const int* tiles, unsigned int width, unsigned int height);
	
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::VertexArray m_Vertices;
	sf::Texture*	m_pTileSet;
	std::string m_spriteSheetDef;
	Sprite	m_collisionBlock;
	std::vector<int> mapBase;
	std::vector<int> mapCollision;
	GameObject* playerPos;

	sf::Rect<int> collisionBlock;

	int mapHeight;
	int mapWidth;
	int tileWidth = 64;
	int tileHeight = 64;
	int tileIndices;

	
	
};

