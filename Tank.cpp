#include "GL/freeglut.h"
#include "GL/gl.h"
#include <iostream>
#include "Tank.h"
using namespace std;

//I/O Methods
void keyPressed(unsigned char key, int x, int y);

//Tank AIs
void AI_1(Tank *myTank, Tank *enemyTank);

Tank::Tank()
{
   this->posX = 0.0;
   this->posY = 0.0;
   //Tank boundaries
   this->leftX = posX - 0.05;
   this->rightX = posX + 0.05;
   this->topY = posY + 0.075;
   this->bottomY = posY - 0.075;

   this->verticalMovement = true;
   this->horizontalSpeed = 0.005;
   this->verticalSpeed = 0.005;
   this->bulletSpeed = 0.0;
   this->bulletx = 0.0; 
   this->bullety = 0.0;
   this->bulletRotation = 0.0;
   this->bulletOrientation = UP;
   this->bulletPosition = 0.0;
}
Tank::~Tank()
{
}

float Tank::getRotation(int orientation)
{
   if(orientation == UP)
   {
       return 0.0;
   }
   if(orientation == RIGHT)
   {
       return -90.0;
   }
   if(orientation == DOWN)
   {
       return -180.0;
   }
   if(orientation == LEFT)
   {
       return -270.0;
   }
}

void Tank::draw()
{
   this->drawBody();
   this->drawTurret();
   this->drawBullets();
}

void Tank::drawBody()
{

    //Retrive user input
    glutKeyboardFunc(keyPressed);
    if(this->verticalMovement)
    {
       this->posY+= this->verticalSpeed;
       
    }
    else
    {
       this->posX+= this->horizontalSpeed;
    }


   //calculate new tank boundaries
   this->leftX = posX - 0.05;
   this->rightX = posX + 0.05;
   this->topY = posY + 0.075;
   this->bottomY = posY - 0.075;

    //Draw body
    glColor3f(0.1, 0.5, 0.0);
    glPushMatrix();

    
    
    glTranslatef(this->posX, this->posY, 0.0);  
    glRotatef(Tank::getRotation(this->orientation), 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
	glVertex2f(-0.05, -0.075);
	glVertex2f(-0.05, 0.075);
	glVertex2f(0.05, 0.075);
	glVertex2f(0.05, -0.075);
    glEnd();

    //Draw front bumper
    glColor3f(0.85, 0.0, 0.0);
    glBegin(GL_QUADS);
       glVertex2f(-0.05, 0.075);
       glVertex2f(0.05, 0.075);
       glVertex2f(0.05, 0.070);
       glVertex2f(-0.05, 0.070);
    glEnd();
    glColor3f(0.0, 0.3, 0.8);
}

void Tank::drawTurret()
{
    glRotatef(this->turretRotation, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
       glVertex2f(-0.01, 0.0);
       glVertex2f(-0.01, 0.09);
       glVertex2f(0.01, 0.09);
       glVertex2f(0.01, 0.0);
    glEnd();
    glPopMatrix(); 
}

void Tank::drawBullets()
{
    glPushMatrix(); 
    glColor3f(0.0, 0.0, 0.0);
 
    if(this->bulletSpeed == 0.0)
    { 
       glTranslatef(this->posX, posY, 0.0);
       glRotatef(this->turretRotation, 0.0, 0.0, 1.0);
       glRotatef(Tank::getRotation(this->orientation), 0.0, 0.0, 1.0);
       this->bulletx = posX;
       this->bullety = posY;
       this->bulletRotation = this->turretRotation + getRotation(this->orientation);
       //bulletOrientation = getRotation(orientation);
    }
    else
    {
        glTranslatef(this->bulletx, this->bullety, 0.0);
        glRotatef(this->bulletRotation, 0.0, 0.0, 1.0);
        //glRotatef(getRotation(bulletOrientation), 0.0, 0.0, 1.0);
        glTranslatef(0.0, this->bulletPosition, 0.0);
        this->bulletPosition+= this->bulletSpeed;  
    }

    //cout << bulletPosition << endl;
    if(this->bulletPosition > 2.0)
    {
       this->bulletSpeed = 0.0;
       this->bulletPosition = 0.0;
    }
       glBegin(GL_QUADS);
         glVertex2f(-0.01, 0.07);
         glVertex2f(-0.01, 0.09);
         glVertex2f(0.01, 0.09);
         glVertex2f(0.01, 0.07);
       glEnd();
    glPopMatrix();
}

//AI METHODS
void Tank::draw_AI(Tank *enemyTank)
{
   this->drawBody_AI(AI_1, enemyTank);
   this->drawTurret();
   this->drawBullets();
}

void Tank::drawBody_AI(void (*f)(Tank *myTank, Tank *enemyTank), Tank *enemyTank)
{
   f(this, enemyTank);
}

bool Tank::wasHit(float x, float y, Tank* enemyTank)
{
   x = x + enemyTank->bulletPosition;
   if(x > this->leftX && x < this->rightX /*&& y > bottomY && y < topY*/)
   {
      cout << "I was hit " << endl;
      return true;
   }
   else
   {
      //cout << x << " " << y << endl;
      //cout << this->leftX << "    " << this->rightX << endl;
      //cout << x + enemyTank->bulletPosition << endl;
      return false;  
   }
}

void AI_1(Tank *myTank, Tank *enemyTank)
{

    //myTank->posY = enemyTank->posY;
    //Draw body
    glColor3f(0.1, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(myTank->posX, myTank->posY, 0.0);  
    glRotatef(Tank::getRotation(myTank->orientation), 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
	glVertex2f(-0.05, -0.075);
	glVertex2f(-0.05, 0.075);
	glVertex2f(0.05, 0.075);
	glVertex2f(0.05, -0.075);
    glEnd();

    //Draw front bumper
    glColor3f(0.85, 0.0, 0.0);
    glBegin(GL_QUADS);
       glVertex2f(-0.05, 0.075);
       glVertex2f(0.05, 0.075);
       glVertex2f(0.05, 0.070);
       glVertex2f(-0.05, 0.070);
    glEnd();
    glColor3f(0.0, 0.3, 0.8);
}


//END OF CLASS
