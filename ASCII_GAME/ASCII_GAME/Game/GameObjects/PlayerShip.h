#ifndef _PLAYER_SHIP_H
#define _PLAYER_SHIP_H_

#include "../../Core/Renderer/Sprite.h"

class ASCIIRenderer;

extern const int SCREEN_WIDTH;

class PlayerShip : public Sprite
{
public:

    PlayerShip();
    ~PlayerShip();

    void Update();
    void Initialise(Vector2& position, int upKey, int downKey);
    void Render(ASCIIRenderer* pRenderer);

private:

    int m_UpKey;
    int m_DownKey;
    bool m_bInitialised;


    bool UpKeyPressed();
    bool DownKeyPressed();

    void MoveUp();
    void MoveDown();
};



#endif

