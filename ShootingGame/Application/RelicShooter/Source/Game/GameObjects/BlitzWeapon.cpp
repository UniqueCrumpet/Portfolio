#include "BlitzWeapon.h"

#include "Bullet.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Game/GameData/GameDataManager.h"
class blitz_weapon;


BlitzWeapon::BlitzWeapon(): WeaponBase()
{
}

BlitzWeapon::~BlitzWeapon()
{
}

void BlitzWeapon::Initialise()
{
	WeaponBase::Initialise();

	//Initalising member variables
	m_barrelOffsetX = 55;
	m_barrelOffsetY = -5;
	m_ammo = 1000;
	m_fireRate = 10;
	m_fireTimer = 1;



	//Intializing the sprite and adding animations
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSPriteSheetDef;

	const int fps = 10;

	pSPriteSheetDef = pGameDataManager->GetSpritesheetDef("sprites/weapons/spr_blitz.xml");

	m_animatedSprite.AddAnimationFromSpriteSheetDef(fire, pSPriteSheetDef, "spr_blitz", fps, false);
	m_animatedSprite.SetCurrentAnimation(fire);
	m_animatedSprite.Pause();

}

void BlitzWeapon::Update()
{
	WeaponBase::Update();
}

void BlitzWeapon::Reload()
{
	WeaponBase::Reload();
}

void BlitzWeapon::Fire()
{
	if(!CanFire())
	{
		return;

	}

	//Generate bullet
	Bullet* bullet = new Bullet();

	bullet->Initialise();

	//Create a bullet spawn offset
	sf::Vector2f bulletSpawnOffset(sf::Vector2i(m_barrelOffsetX, m_barrelOffsetY));

	//Rotate it to face toe correct direction
	sf::Transform transform;
	transform.rotate(m_animatedSprite.getRotation());
	transform.scale(m_animatedSprite.getScale());
	bulletSpawnOffset = transform.transformPoint(bulletSpawnOffset);

	bullet->SetPosition(m_animatedSprite.getPosition().x + bulletSpawnOffset.x, m_animatedSprite.getPosition().y + bulletSpawnOffset.y);
	bullet->setRotation(m_animatedSprite.getRotation());
	bullet->setScale(m_animatedSprite.getScale().x, m_animatedSprite.getScale().y);

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	//add it to the current game state
	if(pGameState)
	{
		pGameState->AddGameObject(bullet);
	}


	WeaponBase::Fire();
	m_animatedSprite.Play();
}
