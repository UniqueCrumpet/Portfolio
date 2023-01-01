#pragma once
#include "../../Engine/System/GameState/GameState.h"

class GameStateTest : public GameState
{
public:
	GameStateTest();
	~GameStateTest();
	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override;

};

