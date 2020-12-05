#include<windows.h>
#include <GL/glut.h>
#include<iostream>
#include "imageloader.h"
#include "Brick.h"

using namespace std;


float x=-1.0, y=0.8;
GLint points= 0;
GLfloat color[3] ={1.0, 1.0, 1.0};
GLfloat posX = -0.125, sizeX=0.25, incX=0.0;
GLfloat ballSize = 0.025, bx = 0.0, by =0.0, ballSpeed = -0.06;
bool ballGoUp=false, ballDown=true, ballSide=false, isCatched=false, isColideToTop=false, isColideToBottom=false, isColideToRight=false, isColideToLeft=false;
char msg1[] = "GAME OVER!";
float ballOnCatcher;
Brick *brick = (Brick*)malloc(sizeof(Brick)*30);


float giveMeRandom(){
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

static void resize(int width, int height)
{

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   // glOrtho(0, 100, 0, 100, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}


static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    /*glColor3f(1,1,0);
    glRasterPos3f(-0.1, 0.5, 0);
    for (int i = 0; i < strlen(msg1); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
    }*/



    glColor3f(0, 1, 0);
    glRasterPos3f(-0.98, 0.95, 0);
    char ss[3];
    sprintf( ss, "%d", points );
    for (int i = 0; i < 9; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ss[i]);
    }



    float ff = x, gg = y;
    int xxi=0;

    for(int i=0; i<3;i++){
        for (int j=0 ; j<10 ; j++)
        {
            brick[xxi] = Brick(ff, gg);
            ff+=0.202;
            xxi++;
        }
            ff = x;
           gg-=0.095;
    }


  brick[0].isDead = true;  brick[5].isDead = true;  brick[8].isDead = true;  brick[15].isDead = true;


    for(int i=0; i<30;i++){
        brick[i].CreateBrick();
    }




  // Creating Brick
    /*float ff = x, gg = y;

    for(int i=0; i<5;i++){
        for (int j=0 ; j<10 ; j++)
        {
           // cout<<x;
            CreateBrick(ff,gg);
            ff+=0.202;
        }
            ff = x;
           gg-=0.095;
    }
*/


//Ball
    glPushMatrix();
    glTranslated(bx, by, 0.0);
    glColor3f(color[1], color[2], color[3]);
    glutSolidSphere(ballSize,90,2);
    glPopMatrix();


//Catcher
    glPushMatrix();
    glTranslated(posX, -0.9, 0.0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glColor3f(1.0, 0.3, 0.2);    glVertex2f(0.0, 0.06);
    glVertex2f(sizeX, 0.06);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(sizeX, 0.0);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}




void Update(int v){


// Collide Condition for the boundaries


        by+=ballSpeed;
        bx+=incX;



     if(by<= -0.9+0.06+ballSize && (bx>=posX && bx<=posX+sizeX)){
            //ballDown=false;
            isCatched = true;
           // ballGoUp=true;
        }
     if(isCatched){
            float ballOnCatcher = (sizeX+(bx-posX))/sizeX;

            if(ballOnCatcher>=1 && 1.1>ballOnCatcher)
                incX=-0.025;
            else if(ballOnCatcher>=1.1 && 1.2>ballOnCatcher)
                incX=-0.01875;
            else if(ballOnCatcher>=1.2 && 1.3>ballOnCatcher)
                incX=-0.0125;
            else if(ballOnCatcher>=1.3 && 1.4>ballOnCatcher)
                incX=-0.00625;
            else if(ballOnCatcher>=1.4 && 1.6>ballOnCatcher)
                incX=-0.0;
            else if(ballOnCatcher>=1.6 && 1.7>ballOnCatcher)
                incX=0.00625;
            else if(ballOnCatcher>=1.7 && 1.8>ballOnCatcher)
                incX=0.0125;
            else if(ballOnCatcher>=1.8 && 1.9>ballOnCatcher)
                incX=0.01875;
            else if(ballOnCatcher>=1.9 && 2.0>=ballOnCatcher)
                incX=0.025;


                PlaySound("F:\\Project\\C++\\GLUT\\DX-Ball\\Sounds\\Boing.wav",NULL,SND_ASYNC);
                color[0]=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color[1]=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color[2]=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                ballSpeed*=-1;
                isCatched=false;
                points++;
               // isColideToTop=false;
                //ballGoUp=true;
        }



    if(bx<=-1 + ballSize ){
        isColideToLeft = true;
    }
     if(bx>=1 - ballSize ){
        isColideToRight = true;
    }
     if(by<=-1 + ballSize){
        isColideToBottom = true;
    }
     if(by>=1 - ballSize ){
        isColideToTop = true;
    }

    if(isColideToBottom || isColideToTop){
        PlaySound("F:\\Project\\C++\\GLUT\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
        ballSpeed*=-1;
        isColideToBottom=false;
        isColideToTop=false;
        points++;

    }
    if(isColideToLeft || isColideToRight){
        PlaySound("F:\\Project\\C++\\GLUT\\DX-Ball\\Sounds\\Swordswi.wav",NULL,SND_ASYNC);
        incX*=-1;
        isColideToRight=false;
         isColideToLeft=false;
         points++;
    }


    glutTimerFunc(100, Update, v);

}

void mySpecialFunc(int key, int x, int y){
    switch(key){
    case GLUT_KEY_RIGHT:
        if(posX<1.0-sizeX)
            posX += 0.0625;
		break;
    case GLUT_KEY_LEFT:
        if(posX>-1.0)
            posX -= 0.0625;
	    break;
    case GLUT_KEY_UP:
            sizeX += 0.125;
		break;
    case GLUT_KEY_DOWN:
            sizeX -= 0.125;
	    break;

	}

    glutPostRedisplay();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
            ballSize+=0.006;
            break;

        case 's':
           ballSize-=0.006;
           break;
        case ' ':
             //brick[0].isDead = true;
            break;
    }

    glutPostRedisplay();
}



static void idle(void)
{
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(300,180);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("DX-Ball");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutSpecialFunc(mySpecialFunc);
    glutKeyboardFunc(key);
    glutTimerFunc(100, Update, 0);

    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}




