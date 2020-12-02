#include<windows.h>
#include <GL/glut.h>
#include<iostream>
using namespace std;

GLfloat red[] ={1.0, 0.0, 0.0};
GLfloat posX = -0.125, sizeX=0.25, incX=0;
GLfloat ballSize = 0.025, bx = 0.0, by =0.0, ballSpeed = 0.06;
bool ballUp=false, ballDown=true, ballSide=false, isCatched=false;
char msg1[] = "GAME OVER!";


int random_number_in_range(int start, int end)
{
    //srand((unsigned) time(0));
    int randomNumber;

    randomNumber = (rand() % end) + start;
    return (randomNumber);
}

static void resize(int width, int height)
{
   // const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   //lFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glColor3f(1,1,0);
    glRasterPos3f(-0.1, 0.5, 0);
    for (int i = 0; i < strlen(msg1); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
    }

    glColor3f(0, 1, 0);
    glRasterPos3f(-0.3, 0, 0);
    char s[3];
    sprintf( s, "%d", by );
    for (int i = 0; i < 3; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }


//Ball
    glPushMatrix();
    glTranslated(bx, by, 0.0);
    glColor3f(1.0, 1.0, 1.0);
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

    if(ballDown){

        if(bx<0){
            //bx-= incX;
            by-= ballSpeed;

            if(bx>=1 || bx<=-1){
                ballSide=true;
                ballDown=false;
                if(bx>=1 )
                    bx-= incX;
                if(bx<=1 )
                    bx+= incX;
            }
        }
         else if(bx>0){
            bx+= incX;
            by-= ballSpeed;
            if(bx>=1 || bx<=-1){
                ballSide=true;
                ballDown=false;
            }
        }
        else
            by-= ballSpeed;



      //  by-=ballSpeed;
      //  bx+= incX;
    }

    if(!ballDown && ballSide){
        if(bx<0){
            bx-= incX;
            by+= ballSpeed;

            if(by>1-ballSize){
                ballSide=false;
                ballDown=true;

            }
        }
        else{
            bx-= incX;
            by+= ballSpeed;

             if(by>1-ballSize){
                ballSide=false;
                ballDown=true;
            }
        }
    }

    if(!ballDown && !ballSide){

        float ballOnCatcher = (sizeX+(bx-posX))/sizeX;

         by+= ballSpeed;
         bx+= incX;
         //bx+=0.0025;
         if(by>1-ballSize)
            ballDown=true;

        if(bx>=1 || bx<=-1)
           ballSide=true;

//Catcher & ball after collision
        if(isCatched){
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

        }

         isCatched=false;

    //  cout<< ballOnCatcher<<endl;
    }


    if(by<= -0.9+0.06+ballSize && (bx>=posX && bx<=posX+sizeX)){
            ballDown=false;
            isCatched = true;
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
