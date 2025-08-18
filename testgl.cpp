#include <emscripten.h>
#ifdef __APPLE__
#include<GLUT/glut.h>
#include<openGL/openGL.h>

#else
#include<GL/glut.h>
#endif
#include <stdlib.h>
#include <string.h>
 #include <GL/gl.h>
#include <GL/glu.h>
#include<GL/glut.h>
#include "OutText.h"



#define  LIST_OBJECT  128


  //global                                                                                                              
GLfloat d = 0.1;
int refreshMillis = 30; 
//end global
    




struct kulka
{     
            
GLfloat x;
GLfloat y ;

} kulka={0.0, -0.5} , wall= {1.0 , 1.0} , speed= {0.03, 0.04}, quad;
            
struct point
{
GLfloat x;
GLfloat y;
}point;


namespace glut {


void CreateList(void)
{
int c=128;
do
{
 glNewList(LIST_OBJECT *c, GL_COMPILE);
{
c--;                                           
glColor3f(1.0,1.0,.0);

    glutSolidSphere(0.07,4,4);

glFlush ();
glEndList();

}
}while (c > 0);
}

void enemy()
{


int i=129;


point.x=-0.9;
point.y=0.0;

glBegin(GL_LINE);
glVertex2f(-quad.x, quad.y);
glVertex2f(quad.x, quad.y);
glVertex2f(quad.x, 0.0);
glVertex2f(-quad.x, 0.0);
glEnd();

do

{

i--;
if ( (point.x>wall.x-0.12)&& (wall.y>=point.y))
{
point.y=point.y+0.12;
point.x=-wall.x+0.07;

}
glPushMatrix();
glTranslatef(point.x ,point.y, 0.0);
  glCallList(LIST_OBJECT *i);
point.x=point.x+0.12;


 glPopMatrix();

 if (((point.y-0.12)<kulka.y+0.02) &&   (kulka.x<0.02 +(point.x-0.12) )&& ((point.x-0.12)<0.01+kulka.x) &&((kulka.y-0.12)<0.01+point.y)  )
{
glDeleteLists(LIST_OBJECT  *i , 1 );

}  
}

 while( i>0);

if(point.y--&& point.x--)
{
 OutText("win");   
}
  
 glFlush ();


}

};
namespace glut {

GLfloat x2 , y2=-0.7;

int menu = 0;

void drawBall2(GLfloat x2,  GLfloat y2)
{

    glColor3f(1.0,0.0,.0);

    glPushMatrix();

    glTranslatef(x2, y2,0.0);

    glutSolidSphere(d,20,20);
OutText("win");   
    glPopMatrix();


}
void keyboard (unsigned char key, int x, int y )  
{



switch (key) {
case 'd':
x2=x2+0.1;
glutPostRedisplay();
break;
case 'a':
x2=x2-0.1;
glutPostRedisplay();
break;
case 'w':
y2=y2+0.1;
glutPostRedisplay();
break;
case 's':
y2=y2-0.1;
glutPostRedisplay();
break;
 case 'q':  
menu =menu+ 1;
 break;
glutPostRedisplay();
break;
}
}

};
                                                        //p.

namespace glut {                //class


       



void drawBall1()
{

    glColor3f(0.0,1.0,.0);

    glPushMatrix();

    glTranslatef(kulka.x,kulka.y,0.0);

    glutSolidSphere(d,20,20);

    glPopMatrix();
}


void update()
{

kulka.x+=speed.x;
kulka.y+=speed.y;
quad.x+=speed.x;
quad.y+=speed.y;

if (kulka.x>wall.x)
{
speed.x=-speed.x;
}
if ( kulka.y>wall.y)
{
speed.y=-speed.y;
}
  if(kulka.x<-wall.x)
 {
speed.x=-speed.x;
}

if((  kulka.y<d + glut::y2) && (kulka.x <d +glut::x2  )&& (glut::x2-kulka.x<d) )
{

speed.y=-speed.y;
}


}

};
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


 glShadeModel(GL_SMOOTH);
glColor3f(1,0,0);

int w, h;
glut::drawBall2(glut::x2, glut::y2);   
glut:: drawBall1();
glut::update();
glut::enemy();

 glTranslatef(-0.5,0.2,0.0);


OutText("win");                    //TEKST in glut
glutSwapBuffers();
}



void initRendering()
{
    glEnable(GL_DEPTH_TEST);   
  
 
}

void reshape(int w,int h)
{
  
     glViewport(0, 0, w, h);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

glMatrixMode(GL_MODELVIEW);

   glLoadIdentity();


}             

void Timer(int value)          //kopjuj wklej p.
 {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("gra Q");

    initRendering();
    glut::CreateList();

    glutReshapeFunc(reshape);
    glutKeyboardFunc(glut::keyboard);

    // This is the correct Emscripten loop setup
    emscripten_set_main_loop(display, 0, 1);

    return 0;
}



