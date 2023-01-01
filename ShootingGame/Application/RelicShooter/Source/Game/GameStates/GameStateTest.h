#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../../Game/GameObjects/Camera.h"
#include "../../Game/GameObjects/GameObjectWithAnimatedSprite.h"
#include "../../Game/GameObjects/Player.h"
class GameStateTest : public GameState
{

	
public:

	GameStateTest();
	~GameStateTest();

	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override;

	
private:
	
	Camera* m_Camera;
	//GameObjectWithAnimatedSprite* playerObject;
	Player* playerObject;
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
};

