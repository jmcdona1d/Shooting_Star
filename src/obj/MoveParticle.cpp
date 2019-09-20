#include "MoveParticle.h"

using namespace std;

//set initial variables for particle
const int PARTICLE_WIDTH = 17*2;
const int PARTICLE_HEIGHT = 18*2;
const int PARTICLE_LIFETIME = 500;

MoveParticle::MoveParticle(double x, double y) : Particle("sprParticle.png", x, y, PARTICLE_WIDTH, PARTICLE_HEIGHT, PARTICLE_LIFETIME) {}

void MoveParticle::Logic() {
    Particle::Logic();
    //gradually increase width with time
    if (lifetime >= 0) {
        GetRect()->w = PARTICLE_WIDTH * (lifetime / PARTICLE_LIFETIME);
        GetRect()->h = PARTICLE_HEIGHT * (lifetime / PARTICLE_LIFETIME);
    }
}
