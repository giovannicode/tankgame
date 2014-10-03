#include "GL/freeglut.h"
#include "GL/gl.h"
#include <iostream>
using namespace std;



class Tank
{

public:
//variables-static
static float const UP = 1;
static float const RIGHT = 2;
static float const DOWN = 3;
static float const LEFT = 4;

//variables-positioning
float posX;
float posY;
int orientation;
float turretRotation;
float verticalMovement;

//variables tank boundaries
float leftX;
float rightX;
float topY;
float bottomY;

//variables-physics
float horizontalSpeed;
float verticalSpeed;

//variables-bullets
float bulletSpeed;
float bulletx;
float bullety;
float bulletRotation;
int bulletOrientation;
float bulletPosition;


//methods 
Tank();
~Tank();
void draw();
void draw_AI(Tank *enemyTank);
static float getRotation(int orientation);
bool wasHit(float x, float y, Tank* enemyTank);

private:
//varibles


//methods
void drawBody();
void drawBody_AI(void (*f)(Tank *myTank, Tank *enemyTank), Tank *enemyTank);
void drawTurret();
void drawBullets();

};
