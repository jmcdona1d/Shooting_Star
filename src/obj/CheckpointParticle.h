#ifndef CHECKPOINTPARTICLE_H_
#define CHECKPOINTPARTICLE_H_

#include "Particle.h"

class CheckpointParticle : public Particle {
public:
    CheckpointParticle(double, double);
    virtual void Logic() override;
private:

};

#endif /* CHECKPOINTPARTICLE_H_ */