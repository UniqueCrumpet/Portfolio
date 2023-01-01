#include "GameStateEnd.h"
#include "../../Engine/System/Context/SysContextProvider.h"

GameStateEnd::GameStateEnd()
{
}

GameStateEnd::~GameStateEnd()
{
}

void GameStateEnd::Initialise()
{
	exit(0);
}

void GameStateEnd::Update()
{
	GameState::Update();
}

GameObject* GameStateEnd::GetPlayer()
{
	return nullptr;
}
