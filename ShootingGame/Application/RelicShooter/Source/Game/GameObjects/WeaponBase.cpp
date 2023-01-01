#include "WeaponBase.h"

#include "../GameData/GameDataManager.h"

class GameDataManager;

WeaponBase::WeaponBase()
{
	
}

WeaponBase::~WeaponBase()
{
	
}


void WeaponBase::Initialise()
{
	
}

void WeaponBase::Update()
{
	m_animatedSprite.Animate();
	//Stopping the fire animation when no longer firing 
	if(m_animatedSprite.AnimationFinished())
	{
		m_animatedSprite.SetCurrentAnimation(0);
		m_animatedSprite.Pause();

	}

	//Counting down the cooldown
	if(m_fireTimer >= 0.0f)
	{
		FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();
		m_fireTimer -= pFrameTimer->DeltaTime();

	}

}

void WeaponBase::Reload()
{
	m_ammo = 10;

}

void WeaponBase::Fire()
{
	if(m_fireRate > 0.0f)
	{
		m_fireTimer = 1.0f / m_fireRate;

		--m_ammo;

	}

}

bool WeaponBase::CanFire()
{
	if(m_ammo > 0)
	{
		return m_fireTimer <= 0.0f;

	}

	return false;

}


void WeaponBase::SetScale(float scaleX, float scaleY)
{
	m_animatedSprite.setScale(scaleX, scaleY);

}


void WeaponBase::SetRotation(float angle)
{
	m_animatedSprite.setRotation(angle);

}

void WeaponBase::SetPosition(sf::Vector2f ppos)
{
	m_animatedSprite.setPosition(ppos);

}

void WeaponBase::SetPosition(float posx, float posy)
{
	m_animatedSprite.setPosition(posx, posy);

}


void WeaponBase::GetPosition(float& x, float& y)
{
	m_animatedSprite.getPosition().x;
	m_animatedSprite.getPosition().y;

}

sf::Vector2f WeaponBase::GetPosition()
{
	return m_animatedSprite.getPosition();
}

