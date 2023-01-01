#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../../Game/GameObjects/Camera.h"
class GameStateStart : public GameState
{
public:
	GameStateStart();
	~GameStateStart();

	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override;

private:

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
};

