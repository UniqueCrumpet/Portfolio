#include "TileMap.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "../GameData/SpritesheetDef.h"
#include "../../../Source/Game/GameData/GameDataManager.h"
#include "../../Game/GameStates/GameStateTest.h"

#include <cmath>

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

void TileMap::Initialise()
{
}

void TileMap::Update()
{
}



sf::Vector2f TileMap::GetPosition()
{
	return TileMap::getPosition();
}

void TileMap::GetPosition(float& x, float& y)
{
	this->GetPosition(x, y);
}

void TileMap::SetPosition(float px, float py)
{
	this->SetPosition(px, py);
}

void TileMap::SetPosition(sf::Vector2f ppos)
{
	this->SetPosition(ppos);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//apply the transform (to position the tile map
	states.transform *= getTransform();

	//apply the tile set texture (to the shader)
	states.texture = m_pTileSet;

	// draw the vertex array
	target.draw(m_Vertices, states); 
}


bool TileMap::LoadFromSpriteSheetDef(SpritesheetDef* pSpriteSheetDef, const int* tiles, unsigned width, unsigned height)
{
	if (!pSpriteSheetDef)
	{
		return false;
	}
		

	auto* pAssetManager = C_SysContext::Get<AssetManager>();
	m_pTileSet = &pAssetManager->GetTexture(pSpriteSheetDef->m_Filename.c_str());

	std::vector<sf::IntRect> frames;
	for(auto& m_pSpriteDef : pSpriteSheetDef->m_pSpriteDefs)
	{
		sf::IntRect rect(m_pSpriteDef.m_PosX, m_pSpriteDef.m_PosY, m_pSpriteDef.m_Width, m_pSpriteDef.m_Height);
		frames.push_back(rect);
	}

	int numTiles = 0;

	for (unsigned int i = 0; i < width * height; i++)
	{
		const unsigned int tileNumber = tiles[i];
		if(tileNumber < 0 || tileNumber >= frames.size())
			continue;

		numTiles++;
	}
	m_Vertices.setPrimitiveType(sf::Quads);

	m_Vertices.resize(numTiles * 4);

	int quadNum = 0;
	for(unsigned int i = 0; i < width; ++i)
	{
		for(unsigned int j = 0; j < height; ++j)
		{
			const unsigned int tileNo = tiles[i + j * width];

			if(tileNo < 0 || tileNo >= frames.size())
				continue;
			

			const int tu1 = frames[tileNo].left;
			const int tv1 = frames[tileNo].top;
			const int tu2 = tu1 + frames[tileNo].width;
			const int tv2 = tv1 + frames[tileNo].height;

			const int tstartvertindex = quadNum * 4;
			sf::Vertex* quad = &m_Vertices[tstartvertindex];

			//define its 4 corners
			quad[0].position = sf::Vector2f(sf::Vector2i(i * frames[tileNo].width, j * frames[tileNo].height));
			quad[1].position = sf::Vector2f(sf::Vector2i((i+1) * frames[tileNo].width, j * frames[tileNo].height));
			quad[2].position = sf::Vector2f(sf::Vector2i((i+1) * frames[tileNo].width, (j+1) * frames[tileNo].height));
			quad[3].position = sf::Vector2f(sf::Vector2i(i * frames[tileNo].width, (j+1) * frames[tileNo].height));

			//define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(sf::Vector2i(tu1, tv1));
			quad[1].texCoords = sf::Vector2f(sf::Vector2i(tu2, tv1));
			quad[2].texCoords = sf::Vector2f(sf::Vector2i(tu2, tv2));
			quad[3].texCoords = sf::Vector2f(sf::Vector2i(tu1, tv2));

			//add to the total number of tiles
			quadNum++;
		}
	}

	//add this game object to the rendermanager (object is sub class of sf::drawable
	C_SysContext::Get<RenderManager>()->AddRenderObject(this);

	return true;
}

void TileMap::LoadFromFile(const int width, const int height, const char* fileLocation)
{
	mapHeight = height;
	mapWidth = width;
	
	
	auto* pGDM = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSSDef = pGDM->GetSpritesheetDef("backgrounds/bg_desert.xml");

	// Read the file and store the value into our map 
	std::ifstream file{};
	file.open(fileLocation);
	if (file.is_open())
	{
		int* pMap = new int[width * height];
		int tileinput;
		for (int i = 0; i < width * height; i++)
		{
			file >> tileinput;
			pMap[i] = tileinput;
			mapBase.push_back(tileinput);
		}
		file.close();
		LoadFromSpriteSheetDef(pSSDef, pMap, width, height);
		TileIndexAtPosition(width, height);
		delete[] pMap;
		
	}
	else
	{
		char message[1024];
		strerror_s(message, 1024, errno);
		std::cerr << "Error: " << message;
	}

	
}

void TileMap::LoadCollisionMap(const int width, const int height, std::vector<int> map)
{
	mapHeight = height;
	mapWidth = width;


	auto* pGDM = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSSDef = pGDM->GetSpritesheetDef("backgrounds/bg_desert.xml");

		int* pMap = new int[width * height];
		int tileinput;
		for (int i = 0; i < width * height; i++)
		{
			pMap[i] = map[i];
			mapBase.push_back(tileinput);
		}
		LoadFromSpriteSheetDef(pSSDef, pMap, width, height);
		TileIndexAtPosition(width, height);
		delete[] pMap;


}

bool TileMap::CollidesWith(TileCollisionBlock* pTileCollisionBlock)
{
	return false;
}

int TileMap::TileIndexAtPosition(float width, float height)
{
		int tileinput;
		for (int i = 0; i < mapBase.size(); i++)
		{
			if (mapBase[i] == 11 || mapBase[i] == 3 || mapBase[i] == 4 || mapBase[i] == 6 || mapBase[i] == 8 || mapBase[i] == 5 || mapBase[i] == 7 || mapBase[i] == 9 || mapBase[i] == -1 || mapBase[i] == 2 )
			{
				mapCollision.push_back(1);
			}
			else
			{
				mapCollision.push_back(0);
			}
		}
	return 0;
}

std::vector<int> TileMap::GetMap()
{
	return mapBase;
}
std::vector<int> TileMap::GetMapCollision()
{
	return mapCollision;
}

bool TileMap::CollidesWith(Collider2D* pCollider2D)
{
	return pCollider2D->CollidesWith(this);
}

bool TileMap::CollidesWith(BoxCollider2D* pBoxCollider2D)
{
	//This is where the collision detection code goes
	
	int x = std::floor(((playerPos->GetPosition().x)/64));
	int y = std::floor(((playerPos->GetPosition().y+110)/64))-1;

	if (mapCollision[(32*y + x)] == 1)
		return true;
	if (mapCollision[(32*y + x)] == 0)
		return false;

}

bool TileMap::CollidesWith(CircleCollider2D* pCircleCollider2D)
{
	return false;
}

bool TileMap::CollidesWith(TileMap* pTileMap)
{
	return false;
}


void TileMap::OnCollision(Collider2D* pCollider2D)
{
	bool ttrue = true;
}

void TileMap::GetPlayerPosition(GameObject* player)
{
	playerPos = player;
}
