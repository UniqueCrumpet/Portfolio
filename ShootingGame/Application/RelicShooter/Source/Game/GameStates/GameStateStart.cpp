#include "GameStateStart.h"

#include "GameStateEnd.h"
#include "GameStateTest.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../../Source/Game/GameData/GameDataManager.h"


GameStateStart::GameStateStart()
{
}

GameStateStart::~GameStateStart()
{
	
}

GameObject* GameStateStart::GetPlayer()
{
	return nullptr;
}

void GameStateStart::Initialise()
{
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	GameStateStart* m_gameStateStart = new GameStateStart();
	m_gameStateStart->pGameStateManager->QueueGameState(m_gameStateStart);
}

void GameStateStart::Update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		pGameStateManager->QueuePop();
		GameStateTest* m_gameStateTest = new GameStateTest();
		pGameStateManager->QueueGameState(m_gameStateTest);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		pGameStateManager->QueuePop();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		pGameStateManager->QueuePop();
		GameStateEnd* m_gameStateEnd = new GameStateEnd();
		pGameStateManager->QueueGameState(m_gameStateEnd);
	}
}




