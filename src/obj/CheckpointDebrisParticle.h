#ifndef CHECKPOINTDEBRISPARTICLE_H_
#define CHECKPOINTDEBRISPARTICLE_H_

#include "Particle.h"
#include <random>

class CheckpointDebrisParticle : public Particle {
public:
    CheckpointDebrisParticle(double, double);
    virtual void Logic() override;
private:
    static std::default_random_engine randomNumbers;
    static std::uniform_real_distribution<double> distribution;
};

#endif /* CHECKPOINTDEBRISPARTICLE_H_ */