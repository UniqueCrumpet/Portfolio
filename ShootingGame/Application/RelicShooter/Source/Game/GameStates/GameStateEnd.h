#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../../Game/GameObjects/Camera.h"
class GameStateEnd : public GameState
{
public:
	GameStateEnd();
	~GameStateEnd();

	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override;

private:

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
};

