#pragma once

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "Bullet.h"

class WeaponBase : public GameObject
{
public:
	WeaponBase();
	virtual ~WeaponBase() override;
	
	//functions
	virtual void Initialise();
	virtual void Reload();
	virtual void Update();
	virtual void Fire();
	bool CanFire();
	void SetScale(float scaleX, float scaleY);
	void SetRotation(float angle);
	void SetPosition(float posx, float posy) override;
	void SetPosition(sf::Vector2f ppos) override;
	sf::Vector2f GetPosition() override;
	void GetPosition(float& x, float& y) override;

public:
	int m_ammo{};
	float m_fireRate{};
	float m_fireTimer{};
	AnimatedSprite m_animatedSprite;
	


};

