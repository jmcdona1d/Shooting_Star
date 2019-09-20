#include "CheckpointDebrisParticle.h"

using namespace std;

//global variables for explosion dimensions, timimg, and force
const int PARTICLE_WIDTH = 25;
const int PARTICLE_HEIGHT = 25;
const int PARTICLE_LIFETIME = 800;

const double PARTICLE_LAUNCHFORCE = 25.0;

//create explosion to have particles go in random direction with the given force
default_random_engine CheckpointDebrisParticle::randomNumbers;
uniform_real_distribution<double> CheckpointDebrisParticle::distribution(-PARTICLE_LAUNCHFORCE, PARTICLE_LAUNCHFORCE);

//constructor for explosion particle with added force in the random direction with given force
CheckpointDebrisParticle::CheckpointDebrisParticle(double x, double y) : Particle("expparticle2.png", x, y, PARTICLE_WIDTH, PARTICLE_HEIGHT, PARTICLE_LIFETIME) {
    AddForce(CheckpointDebrisParticle::distribution(CheckpointDebrisParticle::randomNumbers), CheckpointDebrisParticle::distribution(CheckpointDebrisParticle::randomNumbers));
}

//make sure particle only lasts for the given lifetime with explosion increasing over lifetime
void CheckpointDebrisParticle::Logic() {
    Particle::Logic();
    if (lifetime >= 0) {
        GetRect()->w = PARTICLE_WIDTH * (lifetime / PARTICLE_LIFETIME);
        GetRect()->h = PARTICLE_HEIGHT * (lifetime / PARTICLE_LIFETIME);
    }
    AddForce(0, 0.5);
}