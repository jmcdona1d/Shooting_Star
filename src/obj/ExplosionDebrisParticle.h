#ifndef EXPLOSIONDEBRISPARTICLE_H_
#define EXPLOSIONDEBRISPARTICLE_H_

#include "Particle.h"
#include <random>

class ExplosionDebrisParticle : public Particle {
public:
    ExplosionDebrisParticle(double, double);
    virtual void Logic() override;
private:
    static std::default_random_engine randomNumbers;
    static std::uniform_real_distribution<double> distribution;
};

#endif /* EXPLOSIONDEBRISPARTICLE_H_ */