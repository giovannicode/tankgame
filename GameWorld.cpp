#include "GL/freeglut.h"
#include "GL/gl.h"
#include <iostream>
#include <cmath>
#include "Tank.cpp"
using namespace std;

//Graphics Methods
void draw();
void initialize();
void finalize();
void Timer(int iUnused);

//I/O Methods
void keyPressed(unsigned char key, int x, int y);

//Initialize a tank
Tank tank1;
Tank tank2;

//Get user Input
void keyPressed(unsigned char key, int x, int y)
{

    //Chage direction after key hit
    if(key == 'a' /*&& horizontalSpeed > 0*/)
    {
       if(tank1.horizontalSpeed > 0)
       {
          tank1.horizontalSpeed = -tank1.horizontalSpeed;
       }
       tank1.orientation = Tank::LEFT;
       tank1.verticalMovement = false;
    }
    if(key == 'd' /*&& horizontalSpeed < 0*/)
    {
        if(tank1.horizontalSpeed < 0)
        {
           tank1.horizontalSpeed = -tank1.horizontalSpeed; 
        }
        tank1.orientation = Tank::RIGHT;
        tank1.verticalMovement = false;
    }
    if(key == 'w' /*&& verticalSpeed < 0*/)
    {
       if(tank1.verticalSpeed < 0)
       {
          tank1.verticalSpeed = -tank1.verticalSpeed;         
       }
       tank1.orientation = Tank::UP;
       tank1.verticalMovement = true;
    }
    if(key == 's' /*&& verticalSpeed > 0*/)
    {
        if(tank1.verticalSpeed > 0)
        {
           tank1.verticalSpeed = -tank1.verticalSpeed;
        }
        tank1.orientation = Tank::DOWN;
        tank1.verticalMovement = true;
    }
    if(key == 'k')
    {
         tank1.turretRotation = tank1.turretRotation + 12.0;
    }
    if(key == 'l')
    {
        tank1.turretRotation = tank1.turretRotation - 12.0;
    }
    if(key == 'j')
    {
        tank1.bulletSpeed = 0.1;
    }     
}

//Draw the Game
void draw()
{
  initialize();
  tank1.draw();
  tank2.draw_AI(&tank1);
  //checkForCollistions(&tank1, &tank2);
  tank2.wasHit(tank1.bulletx, tank1.bullety, &tank1);
  finalize();
}

void initialize()
{
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void finalize()
{
   glFlush();
}

void Timer(int iUnused)
{
   glutPostRedisplay();
   glutTimerFunc(30, Timer, 0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    glutDisplayFunc(draw);
    Timer(0);
    glutMainLoop();    
    return 0;
}
