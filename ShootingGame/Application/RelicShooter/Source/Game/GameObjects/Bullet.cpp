#include "Bullet.h"

#include "Player.h"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Game/GameData/GameDataManager.h"
#include "../GameData/SpritesheetDef.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialise()
{
	

	//Initializing sprite and adding animations
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheeetDef;

	const int fps = 24;

	pSpritesheeetDef = pGameDataManager->GetSpritesheetDef("sprites/bullets/spr_bullet.xml");

	m_animatedSprite.AddAnimationFromSpriteSheetDef(bullet, pSpritesheeetDef, "spr_bullet", fps, false);
	m_animatedSprite.SetCurrentAnimation(bullet);
	//m_animatedSprite.Pause();

	//Initializing bullet variables
	m_velocity = 50.0f;
	m_lifeTime = 1.0f;
	m_CollisionRect = m_animatedSprite.getGlobalBounds();

}

void Bullet::Update()
{
	m_animatedSprite.Animate();

	//Dont move until we are passed the muzzle flash
	if(m_animatedSprite.GetCurrentFrame() == 0)
	{
		return;

	}

	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	//Create a foward moving vector
	sf::Vector2f movement(10.0f, 0.0f);

	//Modify magnitude based on velocity
	movement *= (m_velocity * pFrameTimer->DeltaTime());

	//Rotate and scale it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_animatedSprite.getRotation());
	transform.scale(m_animatedSprite.getScale());
	movement = transform.transformPoint(movement);

	//Transform the bullet position
	m_animatedSprite.move(movement);

	//Deleting the bullet overtime so it doesnt keep flying
	m_lifeTime -= pFrameTimer->DeltaTime();
	if(m_lifeTime <= 0.0f)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();
		//remove from the current game state
		if(pGameState)
		{
			pGameState->RemoveGameObject(this);

		}

	}
	m_CollisionRect = m_animatedSprite.getGlobalBounds();


}





void Bullet::GetPosition(float& x, float& y)
{
	m_animatedSprite.getPosition().x;
	m_animatedSprite.getPosition().y;

}

sf::Vector2f Bullet::GetPosition()
{
	return m_animatedSprite.getPosition();

}

void Bullet::SetPosition(float px, float py)
{
	m_animatedSprite.setPosition(px, py);

}

void Bullet::SetPosition(sf::Vector2f ppos)
{
	m_animatedSprite.setPosition(ppos);

}

void Bullet::setRotation(float angle)
{
	m_animatedSprite.setRotation(angle);

}

void Bullet::setScale(float scaleX, float scaleY)
{
	m_animatedSprite.setScale(scaleX, scaleY);

}

void Bullet::OnCollision(Collider2D* pCollider2D)
{
	//TODO:  Collide with other objects
	//m_animatedSprite.SetVisible(false);
	if(dynamic_cast<Bullet*>(pCollider2D))
	{
		m_animatedSprite.SetVisible(true);

	}else
	{
		m_animatedSprite.SetVisible(false);

	}

}




