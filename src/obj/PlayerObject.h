#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "GameObject.h"

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 32;

class PlayerObject : public GameObject
{
public:
    PlayerObject();
    PlayerObject(double, double);
    void TakeLife();
    bool IsInvincible();
    double GetHitCircleSize();
    virtual void Logic() override;
    int GetLives();
private:
    void DestroyPlayer();
    void TurnInvincible();
    void CreateMoveParticle();
    int lives;
    bool invincible;
    double invincibilityTimer;
    double hitCircleSize;
};

#endif // PLAYEROBJECT_H
