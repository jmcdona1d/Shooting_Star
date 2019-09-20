#ifndef WALLENEMY_H
#define WALLENEMY_H

#include "Enemy.h"

class WallEnemy : public Enemy {
public:
    WallEnemy(double, double, int, int);
    virtual void Logic() override;
private:
    

};

#endif // WALLENEMY_H