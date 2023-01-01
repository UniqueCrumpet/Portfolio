#include "GameStateTest.h"

#include <iostream>

#include "../../Engine/Core/GameObject.h"
#include "../../Game/GameObjects/GameObjectWithSprite.h"
#include "../../Game/GameObjects/GameObjectWithAnimatedSprite.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../../Source/Game/GameData/GameDataManager.h"
#include "../GameData/SpritesheetDef.h"
#include "../../Game/GameObjects/TileMap.h"
#include "../../Game/GameObjects/MainMenuBackground.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Game/GameObjects/TileCollisionBlock.h"
#include  "../../Game/GameObjects/Player.h"
#include "../../Game/GameObjects/WeaponBase.h"
#include "../../Game/GameObjects/Collectable.h"

GameStateTest::GameStateTest()
{

}

GameStateTest::~GameStateTest()
{

}

void GameStateTest::Initialise()
{

	this->m_Camera = new Camera();
	this->m_Camera->Initialise();
	m_GameObjects.push_back(this->m_Camera);

	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSSDef = pGameDataManager->GetSpritesheetDef("backgrounds/bg_desert.xml");

	MainMenuBackground* gameBackground = new MainMenuBackground();
	gameBackground->Initialise();
	m_GameObjects.push_back(gameBackground);

	TileMap* pTileMap2 = new TileMap();
	pTileMap2->Initialise();
	pTileMap2->LoadFromFile(32, 32, "levels/BackgroundMap.txt");
	m_GameObjects.push_back(pTileMap2);

	//TileCollisionBlock* map = new TileCollisionBlock();
	//pTileMap2->LoadCollisionMap(16, 32, pTileMap2->GetMapCollision());
	//auto mapArray = pTileMap2->GetMapCollision();
	//float x = 0.0f;
	//float y = 0.0f;
	//sf::Vector2f pos(x, y);
	//for (int i = 0; i < mapArray.size(); i++)
	//{
	//	if (i % 15 == 0)
	//	{
	//		pos.y += 64;
	//		pos.x = 0;
	//	}
	//	if (mapArray[i] == 1)
	//	{
	//		map->Initialise();
	//		map->SetPosition(pos.x, pos.y);
	//		m_GameObjects.push_back(map);
	//		pos.x += 64;
	//	}
	//	else if (mapArray[i] == 0)
	//	{
	//		pos.x += 64;
	//	}

	//}

	//Adding gun sprite in
	BlitzWeapon* gun = new BlitzWeapon();
	m_GameObjects.push_back(gun);

	//Adding animated player sprite in
	Player* player = new Player();
	player->Initialise();
	m_GameObjects.push_back(player);
	
	playerObject = player;

	pTileMap2->GetPlayerPosition(player);

	/*GameObjectWithSprite* test = new GameObjectWithSprite();
	test->Initialise();
	m_GameObjects.push_back(test);*/

	Collectable* collectable = new Collectable();
	collectable->Initialise();
	collectable->SetPosition(1000, 500);
	m_GameObjects.push_back(collectable);
	


	Camera* acamera = new Camera();
	acamera->Initialise();
	m_GameObjects.push_back(acamera);
	m_Camera = acamera;

	acamera->SetAsCurrentCamera();

	GameState* pGameStateTest = new GameStateTest();
	pGameStateManager->QueueGameState(pGameStateTest);

}

void GameStateTest::Update()
{
	GameState::Update();
	m_Camera->SetPosition(playerObject->GetPosition());
}

GameObject* GameStateTest::GetPlayer()
{
	return m_GameObjects.at(2);

}
