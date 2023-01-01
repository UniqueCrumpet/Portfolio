 #pragma once

#include "WeaponBase.h"


class BlitzWeapon : public WeaponBase
{
public:
	BlitzWeapon();
	~BlitzWeapon() override;

	//functions
	 void Initialise() override;
	virtual void Update() override;
	 void Reload() override;
	virtual void Fire() override;

protected:
	int m_barrelOffsetX;
	int m_barrelOffsetY;
	

	enum animationState
	{
		fire

	};

};

