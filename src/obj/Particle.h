#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "GameObject.h"
#include "../base/GameManager.h"
#include <chrono>

class Particle : public GameObject {
public:
    Particle(std::string, double, double, int, int, double);
    virtual void Logic() override;
    void Destroy();
private:
    double hspd;
    double vspd;

protected:
    void LifetimeTick();
    double lifetime;
};

#endif /* PARTICLE_H_ */
