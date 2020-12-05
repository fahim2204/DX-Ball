#include "Brick.h"
#include<windows.h>
#include <GL/glut.h>
#include <iostream>


float brickPosX, brickPosY;
bool isDead = false;

Brick::Brick(float x, float y){
        brickPosX = x;
        brickPosY = y;
        //std::cout<<x<<y;
    }



Brick::CreateBrick(){
        glPushMatrix();
        glTranslated(brickPosX, brickPosY, 0.0);
        glBegin(GL_QUADS);

        if(!isDead)
            glColor3f(0.1,0.6, 0.2);
        else
            glColor3f(0.0,0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 0.08);
        glVertex2f(0.18, 0.08);
        glVertex2f(0.18, 0.0);
        glEnd();
        glPopMatrix();
    }


Brick::~Brick()
{
    //dtor
}
