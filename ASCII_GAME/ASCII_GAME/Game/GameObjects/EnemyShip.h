#pragma once

#ifndef _ENEMYSHIP_H
#define _ENEMYSHIP_H
#include "../../Core/Renderer/AnimatedSprite.h"

//class ASCIIRenderer;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

const int ENEMY_SPRITE_ANIMATION_FRAMES = 4;

class EnemyShip : public AnimatedSprite
{
public:
	EnemyShip();
	~EnemyShip();

	void Initialise(Vector2& position, int fireRate, int sprite, int scoreValue, float initialTime = 0.0f);
	bool Update(float deltaTime);
	void Render(ASCIIRenderer* pRenderer);

	void Meow(); //explode 
	bool Active() { return m_Active; }
	void Approach(); //move towards player

	int GetScoreValue() { return m_ScoreValue; };

private:
	bool m_bInitialised;
	float m_AnimationTimer;
	bool m_Active;
	int m_ScoreValue;
	bool ShouldFire();

	int m_FireRate;

};
#endif

