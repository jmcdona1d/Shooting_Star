CC = g++
CFLAGS = -Wall -g -std=c++11
INCLUDE = -I /usr/local/include/SDL2
LIBS = -L/usr/local/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
OBJS =  src/base/GameManager.o         \
       src/base/GameRenderer.o     \
       src/base/GameInput.o        \
        src/base/EnemyManager.o     \
       src/obj/GameObject.o        \
       src/obj/PlayerObject.o        \
       src/obj/Enemy.o                \
       src/obj/Checkpoint.o            \
       src/obj/ExplosionDebrisParticle.o        \
       src/obj/ExplosionParticle.o        \
       src/obj/MoveEnemy.o     \
        src/obj/HomingEnemy.o     \
        src/obj/WallEnemy.o     \
       src/obj/MoveParticle.o     \
       src/obj/Particle.o    \
       src/ui/UIButton.o         \
       src/ui/UIElement.o    \
       src/ui/UIImage.o            \
       src/ui/UIManager.o            \
       src/ui/UIMenu.o\
       src/ui/UIText.o\
       src/obj/CheckpointDebrisParticle.o\
        src/obj/CheckpointParticle.o     \


%.o: %.cpp
	g++ -c -std=c++11 $(CFLAGS) $< -o $@ $(INCLUDE)

DriversEd: $(OBJS)
	g++ -o Debug/DriversEd $(OBJS) $(LIBS) $(CFLAGS) $(INCLUDE)