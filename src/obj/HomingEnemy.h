#ifndef HOMINGENEMY_H
#define HOMINGENEMY_H

#include "GameObject.h"
#include "PlayerObject.h"
#include "Enemy.h"

class HomingEnemy : public Enemy {
public:
    HomingEnemy(double, double, int, int, double);
    void DamagePlayer(PlayerObject&);
    virtual void Logic() override;
    
private:
    double lifetime;
    void LifetimeTick();
};

#endif // HOMINGNEMY_H