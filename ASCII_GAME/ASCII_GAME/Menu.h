#pragma once
#ifndef _MENU_H_
#define _MENU_H_
#include "Core/Renderer/Sprite.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class MenuIcon : public Sprite
{
public:
	MenuIcon();
	~MenuIcon();

	void Initialise(Vector2& position);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

	void SetPosition(Vector2 position);
	Vector2 GetPosition();

	void SetSpriteID(int ID) { spriteID = ID; };
	int GetSpriteID() { return spriteID; };

private:
	bool m_bInitialised;
	bool m_Active;

	int  spriteID;
	Vector2 m_position;


};


class Pointer : public Sprite
{
public:
	Pointer();
	~Pointer();

	void Initialise(Vector2& position, int leftKey, int rightKey);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

private:
	int m_upKey;
	int m_downKey;
	bool m_bInitialised;
	void MoveUp();
	void MoveDown();
};
#endif
