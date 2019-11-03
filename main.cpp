#define GLUT_DISABLE_ATEXIT_HACK

//compile with g++ -std=c++11 main.cpp -o main -lGL -lGLU -lglut
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <unistd.h>
#include <ctime>
#include <stdlib.h>
#include <random>
#include "boid.h"
#include "boid.cpp"


using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define Z_KEY 122
#define X_KEY 120




void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

void dibujaRectangulo(int ancho, int largo);
void dibujaGrua(int angulo1, int angulo2, int largo);
void pescera(double);

//function called on each frame
GLvoid window_idle();

float w = 800,h=800;
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 2 : Boids");

	initGL();
	init_scene();

	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 0;
}

//vector boidssssssssssssssssssssssssssssssssssssssssssssssssss

vector<Boid *> flock;

GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);



}

float a= 0.0;
float b=0.0,m=0.1;
float l=5;


void init_scene()
{
	//srand(time(NULL));
	/*vector<double> pos = {0,0,1};
	vector<double> dir = {1,0,0};
	Boid uno(pos, dir);*/

	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(-30.0, 30.0);
	for(int i = 0;i<100;i++)
	{
		double rx,ry;
		rx = dist(mt);
		ry = dist(mt);
		cout<< rx << " " << ry << endl;
		flock.push_back(new Boid(rx,ry,20,20));
	}

}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-w/32.0f, w/32.0f, -h/32.0f, h/32.0f, -25.0f, 25.0f);

	gluPerspective(65.0f, 1.0f, 1.0f, 200.0f);
	glTranslated(0,0,-70);

	pescera(20);
	//dibujaGrua(90,90,5);
	for(int i=0;i<flock.size();i++)
	{
		flock[i]->edges();
		flock[i]->behaviour(flock);
		flock[i]->update();
		flock[i]->draw();
		//sleep(1);
	}


	glutSwapBuffers();
	glFlush();

}




GLvoid window_reshape(GLsizei width, GLsizei height)
{
    w = width;
    h = height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
}




GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
        case ECHAP:
            exit(1);
            break;

        case W_KEY:
            a -= 0.5;
            break;

        case S_KEY:
            a += 0.5;
            break;

        case A_KEY:
            b -= 0.5;
            break;

        case D_KEY:
            b += 0.5;
            break;

        case Z_KEY:
            l -= 1;
            break;

        case X_KEY:
            l += 1;
            break;

        default:
            printf("La touche %d non active.\n", key);
            break;
	}
}


//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}

void dibujaRectangulo(int ancho, int largo)
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glVertex3f(0,0,1);
        glVertex3f(ancho,0,1);
        glVertex3f(ancho,largo,1);
        glVertex3f(0,largo,1);
    glEnd();
}

void dibujaGrua(int angulo1, int angulo2, int largo)
{
    glColor3d(255,128,0);
    dibujaRectangulo(5,2);

    glColor3d(237,255,033);
    glTranslated(2.5,1,0);
    glRotated(angulo1,0,0,1);
    dibujaRectangulo(2,15);

    glColor3d(237,255,033);
    glTranslated(0,15,0);
    glRotated(angulo2,0,0,1);
    dibujaRectangulo(2,10);

    glTranslated(0,10,0);
    dibujaRectangulo(largo,1);
    glTranslated(largo,0,0);
    glutSolidSphere(1,8,8);
}


void pescera(double tam)
{
	double negative_tam = (-1)*tam;




	glBegin(GL_LINES);
	glColor3f(   1.0,  1.0, 1.0 );

	//frontal arriba abajo izquierda dereca
	glVertex3f(  negative_tam, tam, tam );
	glVertex3f(  tam,  tam, tam );

	glVertex3f(  negative_tam, negative_tam, tam );
	glVertex3f(  tam,  negative_tam, tam );

	glVertex3f(  negative_tam, tam, tam );
	glVertex3f(  negative_tam, negative_tam, tam );

	glVertex3f(  tam,  tam, tam );
	glVertex3f(  tam,  negative_tam, tam );



	//trasero
	glVertex3f(  negative_tam, tam, negative_tam );
	glVertex3f(  tam,  tam, negative_tam );

	glVertex3f(  negative_tam, negative_tam, negative_tam );
	glVertex3f(  tam,  negative_tam, negative_tam );

	glVertex3f(  negative_tam, tam, negative_tam );
	glVertex3f(  negative_tam, negative_tam, negative_tam );

	glVertex3f(  tam,  tam, negative_tam );
	glVertex3f(  tam,  negative_tam, negative_tam );

	//laterales
	glVertex3f(  negative_tam, tam, tam );
	glVertex3f(  negative_tam, tam, negative_tam );

	glVertex3f(  tam,  tam, tam );
	glVertex3f(  tam,  tam, negative_tam );

	glVertex3f(  negative_tam, negative_tam, tam );
	glVertex3f(  negative_tam, negative_tam, negative_tam );

	glVertex3f(  tam,  negative_tam, tam );
	glVertex3f(  tam,  negative_tam, negative_tam );

	glEnd();




}
