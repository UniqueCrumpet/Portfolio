#include "TileCollisionBlock.h"

#include "../../Engine/Physics/BoxCollider2D.h"

bool TileCollisionBlock::CollidesWith(Collider2D* pCollider2D)
{
	return pCollider2D->CollidesWith(this);
}

bool TileCollisionBlock::CollidesWith(BoxCollider2D* pBoxCollider2D)
{
	//TODO:  Implement Block Collision
	bool tresult = this->m_collisionBlock.getGlobalBounds().intersects(pBoxCollider2D->m_CollisionRect);
	if(tresult)
	{
		return true;
	}
	return false;
}

bool TileCollisionBlock::CollidesWith(CircleCollider2D* pCircleCollider2D)
{
	return false;
}

bool TileCollisionBlock::CollidesWith(TileMap* pTileMap)
{
	return false;
}


bool TileCollisionBlock::CollidesWith(TileCollisionBlock* pTileCollisionBlock)
{
	return false;
}

void TileCollisionBlock::OnCollision(Collider2D* pCollider2D)
{
}

TileCollisionBlock::TileCollisionBlock()
{
}

TileCollisionBlock::~TileCollisionBlock()
{
}

void TileCollisionBlock::Initialise()
{
	m_collisionBlock.Initialise("sprites/spr_hud_face_raff_0.png");
}

void TileCollisionBlock::Update()
{
	//THIS IS STATIC SO NOTHING TO UPDATE.
}

void TileCollisionBlock::UpdatePos(int x, int y)
{
	this->SetPosition(x, y);
}

sf::Vector2f TileCollisionBlock::GetPosition()
{
	return this->m_collisionBlock.getPosition();
}

void TileCollisionBlock::GetPosition(float& x, float& y)
{
	auto tpos = this->GetPosition();
	x = tpos.x;
	y = tpos.y;
}

void TileCollisionBlock::SetPosition(float px, float py)
{
	this->m_collisionBlock.setPosition(px, py);
}

void TileCollisionBlock::SetPosition(sf::Vector2f ppos)
{
	this->m_collisionBlock.setPosition(ppos);
}

