#include "Particle.h"

using namespace std;

//declare set frame time for particles
extern int FRAME_TIME;

Particle::Particle(string imagePath, double x, double y, int w, int h, double l) : GameObject(imagePath, x, y, w, h), lifetime(l) {

}

void Particle::Logic() {
    GameObject::Logic();
    LifetimeTick();
    position[1] += 5;
}

//compare lifetime with frame time (global var) until 0 and then delete
void Particle::LifetimeTick() {
    lifetime -= FRAME_TIME;
    if (lifetime <= 0) {
        MarkForDeletion();
    }
}
