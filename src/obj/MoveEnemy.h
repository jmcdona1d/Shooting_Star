#ifndef MOVEENEMY_H
#define MOVEENEMY_H

#include "GameObject.h"
#include "PlayerObject.h"
#include "Enemy.h"

class MoveEnemy : public Enemy {
public:
    MoveEnemy(double, double, int, int);
    void DamagePlayer(PlayerObject&);
    virtual void Logic() override;
private:
    int direction;
    float hspd;
    float vspd;
};

#endif // MOVEENEMY_H
