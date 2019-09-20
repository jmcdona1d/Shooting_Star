#include "CheckpointParticle.h"
#include "CheckpointDebrisParticle.h"

using namespace std;

//specify initial particle dimensions
const int PARTICLE_WIDTH = 200;
const int PARTICLE_HEIGHT = 200;
const int PARTICLE_LIFETIME = 300;

CheckpointParticle::CheckpointParticle(double x, double y) : Particle("expparticle2.png", x, y, PARTICLE_WIDTH, PARTICLE_HEIGHT, PARTICLE_LIFETIME) {
    for (int i = 0; i < 15; i++) {
        // corresponding to explosion debris
        GameManager::AddObject(make_shared<CheckpointDebrisParticle>(x, y));
    }
}

void CheckpointParticle::Logic() {
    Particle::Logic();
    if (lifetime >= 0) {
        //increase with lifetime
        GetRect()->w = PARTICLE_WIDTH * (lifetime / PARTICLE_LIFETIME);
        GetRect()->h = PARTICLE_HEIGHT * (lifetime / PARTICLE_LIFETIME);
    }
}