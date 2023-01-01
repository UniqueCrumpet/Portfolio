#pragma once

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine/Physics/Collider2D.h"

class TileCollisionBlock : public GameObject, public Collider2D
{
public:
	TileCollisionBlock();
	~TileCollisionBlock() override;

	void Initialise() override;
	void Update() override;
	void UpdatePos(int x, int y);
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
	void GetPosition(float& x, float& y) override;

	bool CollidesWith(Collider2D* pCollider2D) override;
	bool CollidesWith(BoxCollider2D* pBoxCollider2D) override;
	bool CollidesWith(CircleCollider2D* pCircleCollider2D) override;
	bool CollidesWith(TileMap* pTileMap) override;
	bool CollidesWith(TileCollisionBlock* pTileCollisionBlock) override;
	void OnCollision(Collider2D* pCollider2D) override;

private:
	Sprite m_collisionBlock;
};



