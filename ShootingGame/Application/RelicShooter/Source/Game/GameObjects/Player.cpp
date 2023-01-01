#include "Player.h"
#include "../../Game/GameData/GameDataManager.h"
#include "KeyboardAndMouseInputDevices.h"
#include "TileCollisionBlock.h"
#include "TileMap.h"
#include "../../Engine/Core/MathHelpers.h"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Utils/Utils.h"

Player::Player():BoxCollider2D()
{
}

Player::~Player()
{
	SAFE_DELETE_PTR(m_pWeapon);

}

//bool Player::CollidesWith(TileCollisionBlock* pTileCollisionBlock)
//{
//	return true;
//}
//
//
//bool Player::CollidesWith(Collider2D* pCollider2D)
//{
//	return false;
//}
//
//bool Player::CollidesWith(Player* pPlayer)
//{
//	return false;
//}
//
//bool Player::CollidesWith(BoxCollider2D* pBoxCollider2D)
//{
//	m_AnimatedSprite.setPosition(m_PrevPos);
//	return true;
//}
//
//bool Player::CollidesWith(CircleCollider2D* pCircleCollider2D)
//{
//	return false;
//}
//
//bool Player::CollidesWith(TileMap* pTileMap)
//{
//	return false;
//}

void Player::OnCollision(Collider2D* pCollider2D)
{
	if (dynamic_cast<TileMap*>(pCollider2D))
	{
		m_AnimatedSprite.setPosition(m_PrevPos);
	}
	//TODO: Handle other types of collision
	else
	{
		
	}

}

void Player::Initialise()
{
	//Setting the player
	m_AnimatedSprite.setPosition(300, 250);

	//Getting the sprite sheet
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSPriteSheetDef;

	const int frameRate = 10;

	pSPriteSheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_pinky.xml");

	//Adding the animations
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(Idle, pSPriteSheetDef,
		"spr_pinky_idle", frameRate);

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(Walk, pSPriteSheetDef,
		"spr_pinky_walk", frameRate);

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(Sprint, pSPriteSheetDef,
		"spr_pinky_sprint", frameRate);
	

	m_Curr = Idle;
	m_Prev = Idle;
	//Setting default animation state
	m_AnimatedSprite.SetCurrentAnimation(m_Curr);
	//m_AnimatedSprite.scale(3, 3);
	m_AnimatedSprite.Play();

	//Intializing the BlitzWeapon class
	m_pWeapon = new BlitzWeapon();
	m_pWeapon->Initialise();
	

}

void Player::SetPrevPosition(sf::Vector2f ppos)
{
	m_PrevPos = ppos;
}


sf::Vector2f Player::GetPrevPosition()
{
	return m_PrevPos;
}

void Player::Update()
{


	this->SetPrevPosition(this->GetPosition());

	m_AnimatedSprite.Animate();

	//Inputting the controls
	InputManager* p_InputManager = C_SysContext::Get<InputManager>();
	InputDevice* p_InputDevice = p_InputManager->GetInputDevice();

	auto ttpf = C_SysContext::Get<FrameTimer>();
	float ttpff = ttpf->DeltaTime();

	float speed = 100.0f;

	//Movement variable values
	sf::Vector2f m_Up = sf::Vector2f(0.0f, -1.0f);
	sf::Vector2f m_Down = sf::Vector2f(0.0f, 1.0f);
	sf::Vector2f m_Left = sf::Vector2f(-1.0f, 0.0f);
	sf::Vector2f m_Right = sf::Vector2f(1.0f, 0.0f);

	int temp = 0;

	sf::Vector2f tmovement(0.0f, 0.0f);

	static float tscalex = 1.0f;

	//Movement
	if (p_InputDevice->GetButtonInput(E_DigitalInput_LeftThumb).IsDown())
	{
		speed = 500.0f;

	}
	if (p_InputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
	{
		tmovement += m_Left;
	}
	if (p_InputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
	{
		tmovement += m_Right;
	}
	if (p_InputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
	{
		tmovement += m_Up;
	}
	if (p_InputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
	{
		tmovement += m_Down;
	}

	tmovement *= speed * ttpff;

	
	m_AnimatedSprite.move(tmovement);
	

	float tlength = MathHelpers::Length(tmovement);

	if(tlength > 0)
	{
		
		m_Curr = Walk;
		if (tmovement.x > 0.0f)
			m_AnimatedSprite.setScale(1.0f, 1.0f);
		else if (tmovement.x < 0.0f)
			m_AnimatedSprite.setScale(-1.0f, 1.0f);
		tmovement = MathHelpers::Normalise(tmovement);
		//Setting the sprint
		if(speed > 100.0f)
		{
			m_Curr = Sprint;

		}

	}
	else if(tlength == 0)
	{
		m_Curr = Idle;
	}

	//Animation State Machine
	if (m_Curr == Walk && m_Prev != Walk)
	{
		m_AnimatedSprite.SetCurrentAnimation(Walk);
		m_AnimatedSprite.Play();

		
	}
	else if(m_Curr == Idle && m_Prev == Walk)
	{
		m_AnimatedSprite.SetCurrentAnimation(Idle);
		m_AnimatedSprite.Play();
	}else if(m_Curr == Sprint && m_Prev != Sprint && speed > 100.0f)
	{
		m_AnimatedSprite.SetCurrentAnimation(Sprint);
		m_AnimatedSprite.Play();

	}

	m_Prev = m_Curr;

	m_WeaponOffsetY = 20;
	m_WeaponOffsetX = 20;



	//Updating the weapon class
	//Get the player position and add the weapon offset to it (accounting for scale)
	sf::Vector2f tweaponPos = m_AnimatedSprite.getPosition();
	tweaponPos.x += m_WeaponOffsetX * m_AnimatedSprite.getScale().x;
	tweaponPos.y += m_WeaponOffsetY * m_AnimatedSprite.getScale().y;
	m_pWeapon->SetPosition(tweaponPos.x, tweaponPos.y);
	//Set the weapon scale relative to the player
	m_pWeapon->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);

	m_pWeapon->Update();

	//Weapon controls/mechanics
	if(p_InputDevice->GetButtonInput(E_DigitalInput_A).IsDown())
	{
		m_pWeapon->Fire();


	}

	if(p_InputDevice->GetButtonInput(E_DigitalInput_X).IsDown())
	{
		m_pWeapon->Reload();


	}

	this->m_CollisionRect = this->m_AnimatedSprite.getGlobalBounds();
}

void Player::GetPosition(float& px, float& py)
{
	m_AnimatedSprite.getPosition().x;
	m_AnimatedSprite.getPosition().y;

}

sf::Vector2f Player::GetPosition()
{
	return m_AnimatedSprite.getPosition();

}

void Player::SetPosition(float px, float py)
{
	m_AnimatedSprite.setPosition(px, py);


}

void Player::SetPosition(sf::Vector2f ppos)
{
	m_AnimatedSprite.setPosition(ppos);

}
