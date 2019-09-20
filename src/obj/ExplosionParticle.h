#ifndef EXPLOSIONPARTICLE_H_
#define EXPLOSIONPARTICLE_H_

#include "Particle.h"

class ExplosionParticle : public Particle {
public:
    ExplosionParticle(double, double);
    virtual void Logic() override;
private:

};

#endif /* EXPLOSIONPARTICLE_H_ */