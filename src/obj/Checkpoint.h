#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "GameObject.h"
#include "PlayerObject.h"

class Checkpoint : public GameObject {
public:
    Checkpoint();
    Checkpoint(double, double, int, int);
    void CollidePlayer(PlayerObject&, int, int);
private:
    int level = 0;
};

#endif // ENEMY_H
