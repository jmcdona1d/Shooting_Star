#ifndef MOVEPARTICLE_H_
#define MOVEPARTICLE_H_

#include "Particle.h"

class MoveParticle : public Particle {
public:
    MoveParticle(double, double);
    virtual void Logic() override;
private:

};

#endif /* MOVEPARTICLE_H_ */