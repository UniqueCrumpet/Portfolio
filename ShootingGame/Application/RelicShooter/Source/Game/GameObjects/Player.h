#pragma once

#include "../../Engine/Core/GameObject.h"
#include "GameObjectWithAnimatedSprite.h"
#include "../../Engine/Input/InputManager.h"
#include "WeaponBase.h"
#include "BlitzWeapon.h"


class Player : public GameObject, public BoxCollider2D
{
public:
	Player();
	~Player() ;

	//Funtions
	void Initialise();
	virtual void Update();
	virtual void GetPosition(float& px, float& py);
	virtual sf::Vector2f GetPosition();
	virtual void SetPosition(float px, float py);
	virtual void SetPosition(sf::Vector2f ppos);

	void SetPrevPosition(sf::Vector2f ppos);
	sf::Vector2f GetPrevPosition();

	/*bool CollidesWith(Collider2D* pCollider2D) override;
	bool CollidesWith(BoxCollider2D* pBoxCollider2D) override;
	bool CollidesWith(CircleCollider2D* pCircleCollider2D) override;
	bool CollidesWith(TileMap* pTileMap) override;
	bool CollidesWith(Player* pPlayer) override;
	bool CollidesWith(TileCollisionBlock* pTileCollisionBlock) override;*/
	void OnCollision(Collider2D* pCollider2D) override;

private:
	AnimatedSprite m_AnimatedSprite;

	enum AnimationState {
		Idle,
		Sprint,
		Walk

	};

protected:
	bool isPressed;
	bool isLoop;

	int m_WeaponOffsetX;
	int m_WeaponOffsetY;
	AnimationState m_Curr;
	AnimationState m_Prev;
	
	WeaponBase* m_pWeapon;
	sf::Vector2f m_PrevPos;
};

