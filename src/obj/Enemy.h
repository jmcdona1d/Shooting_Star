#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "PlayerObject.h"
#include <string>

class Enemy : public GameObject {
public:
    Enemy(std::string, std::string);
    Enemy(std::string, std::string , double, double, int, int);
    virtual void Logic() override;
    void DamagePlayer(PlayerObject&);
private:
    

};

#endif // ENEMY_Hs