#include "ExplosionDebrisParticle.h"

using namespace std;

//global variables for explosion dimensions, timimg, and force
const int PARTICLE_WIDTH = 18;
const int PARTICLE_HEIGHT = 18;
const int PARTICLE_LIFETIME = 800;

const double PARTICLE_LAUNCHFORCE = 20.0;

//create explosion to have particles go in random direction with the given force
default_random_engine ExplosionDebrisParticle::randomNumbers;
uniform_real_distribution<double> ExplosionDebrisParticle::distribution(-PARTICLE_LAUNCHFORCE, PARTICLE_LAUNCHFORCE);

//constructor for explosion particle with added force in the random direction with given force
ExplosionDebrisParticle::ExplosionDebrisParticle(double x, double y) : Particle("expparticle.png", x, y, PARTICLE_WIDTH, PARTICLE_HEIGHT, PARTICLE_LIFETIME) {
    AddForce(ExplosionDebrisParticle::distribution(ExplosionDebrisParticle::randomNumbers), ExplosionDebrisParticle::distribution(ExplosionDebrisParticle::randomNumbers));
}

//make sure particle only lasts for the given lifetime with explosion increasing over lifetime
void ExplosionDebrisParticle::Logic() {
    Particle::Logic();
    if (lifetime >= 0) {
        GetRect()->w = PARTICLE_WIDTH * (lifetime / PARTICLE_LIFETIME);
        GetRect()->h = PARTICLE_HEIGHT * (lifetime / PARTICLE_LIFETIME);
    }
}