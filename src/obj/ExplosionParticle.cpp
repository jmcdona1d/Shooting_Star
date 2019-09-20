#include "ExplosionParticle.h"
#include "ExplosionDebrisParticle.h"

using namespace std;

//specify initial particle dimensions
const int PARTICLE_WIDTH = 400;
const int PARTICLE_HEIGHT = 400;
const int PARTICLE_LIFETIME = 300;

ExplosionParticle::ExplosionParticle(double x, double y) : Particle("expparticle.png", x, y, PARTICLE_WIDTH, PARTICLE_HEIGHT, PARTICLE_LIFETIME) {
    for (int i = 0; i < 20; i++) {
        // corresponding to explosion debris
        GameManager::AddObject(make_shared<ExplosionDebrisParticle>(x, y));
    }
}

void ExplosionParticle::Logic() {
    Particle::Logic();
    if (lifetime >= 0) {
        //increase with lifetime
        GetRect()->w = PARTICLE_WIDTH * (lifetime / PARTICLE_LIFETIME);
        GetRect()->h = PARTICLE_HEIGHT * (lifetime / PARTICLE_LIFETIME);
    }
}