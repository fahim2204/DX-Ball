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

        if(!isDead){
            glColor3f(0.8,0.5, 1.0);
        }
        else
            glColor3f(1.0,0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 80);
        glVertex2f(100, 80);
        glVertex2f(100, 0);
        glEnd();
        glPopMatrix();
    }


Brick::~Brick()
{
    //dtor
}
