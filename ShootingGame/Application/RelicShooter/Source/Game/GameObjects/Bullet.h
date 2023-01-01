#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"


class Bullet : public GameObject, public  BoxCollider2D
{

public:
	Bullet();
	~Bullet();
	virtual void Initialise() override;
	virtual void Update() override;
	virtual void GetPosition(float& x, float& y) override;
	virtual sf::Vector2f GetPosition() override;
	virtual void SetPosition(float px, float py) override;
	virtual void SetPosition(sf::Vector2f ppos) override;
	void setRotation(float angle);
	void setScale(float scaleX, float scaleY);

	void OnCollision(Collider2D* pCollider2D) override;
private:
	AnimatedSprite m_animatedSprite;
	float m_velocity;

public:

	/* Not actually neccessary, C++ will Generate this auto*/
	bool CollidesWith(BoxCollider2D* pBoxCollider2D) override
	{
		return BoxCollider2D::CollidesWith(pBoxCollider2D);
	}
private:
	float m_lifeTime;

	enum animation
	{
		bullet


	};

};

