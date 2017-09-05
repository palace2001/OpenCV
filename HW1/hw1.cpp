/*
*
*   Kookmin Univ.  CS .  20113253   Kim Keun Peel
*   Computer Graphics.    Homework 1
*
*/



#include <GL/freeglut.h>
#include <iostream>
#include "Painter.cpp"

using namespace std;

void init();
void myDisplay();
void myReshape(int w, int h);
void myKeyboard(unsigned char key, int x,  int y);
void mySpecial(int key, int x, int y);
void myTimer(int value);
void myMenu(int item);
void drawBottom();


static float g_aspect = 1.0f;
static float g_delta_x = 0.0f ;
static float g_delta_y = 5.0f ;
static float g_fovy = 100.0f ;


static Painter painter;


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);  // deal -> main function parameter
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Hello FreeGLUT");


	GLint SubMenu_N = glutCreateMenu(myMenu);
	glutAddMenuEntry("10",0);
	glutAddMenuEntry("50",1);
	glutAddMenuEntry("100",2);
	glutAddMenuEntry("500",3);
	glutAddMenuEntry("1000",4);
	glutAddMenuEntry("5000",41);

	GLint SubMenu_C = glutCreateMenu(myMenu);
	glutAddMenuEntry("Red",5);
	glutAddMenuEntry("Green",6);
	glutAddMenuEntry("Blue",7);
	glutAddMenuEntry("Random",8);

	GLint SubMenu_F = glutCreateMenu(myMenu);
	glutAddMenuEntry("Circle",9);
	glutAddMenuEntry("Star",10);
	glutAddMenuEntry("Square",11);
	glutAddMenuEntry("Triangle",12);
	glutAddMenuEntry("Random",13);


	// Create a menu
        glutCreateMenu(myMenu);
        glutAddSubMenu("Numbers",SubMenu_N);
        glutAddSubMenu("Colors", SubMenu_C);
        glutAddSubMenu("Figures", SubMenu_F);


	init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutTimerFunc(1,myTimer,1);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecial);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 

	gluPerspective(g_fovy, g_aspect, 0.01f, 1000.0f);  
	
	gluLookAt(g_delta_x, g_delta_y, 8.0f,
		g_delta_x, g_delta_y, 0.0f,
		0.0f, 10.0f, 0.0f);

	glPushMatrix();
	drawBottom(); // bottom
	glPopMatrix();


	 painter.DrawFountain();  // draw fountain

	glutSwapBuffers();  // glFlush
}

void myReshape(int w, int h)
{
	g_aspect = (float)w / (float)h; 
	glViewport(0, 0, w, h); 
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x,  int y)
{
	switch(key){
		case '+':
			g_fovy -= 10.0f;
			break;
		case '-':
			g_fovy += 10.0f;
			break;
	}
	glutPostRedisplay();  
}

void mySpecial(int key, int x, int y)
{
	switch(key) {
		case GLUT_KEY_LEFT: // 0.02만큼 x증가
			g_delta_x += -0.2f;
			break;
     		case GLUT_KEY_RIGHT:  // 0.02만큼 y증가
     			g_delta_x += 0.2f;
     			break;
     		case GLUT_KEY_UP:  // 0.02만큼 y감소
     			g_delta_y += 0.2f;
     			break;
     		case GLUT_KEY_DOWN:  // 0.02만큼 y감소
     			g_delta_y += -0.2f;
    			 break;
    		case GLUT_KEY_HOME:   // Reset
     			g_delta_x = 0.0f ;
			g_delta_y = 5.0f ;
			g_fovy = 100.0f ;
    			 break;
    		default :
    			break;
    	 }
    	 glutPostRedisplay();
 }

void myTimer(int value)
{
	glutPostRedisplay( );
	glutTimerFunc(1,myTimer,1);
}

void myMenu(int item)
{
	switch (item){
		case 0:	// n = 10
			if(painter.get_numfigure() != 10)
				painter.set_numfigure(10);
			break;
		case 1:	// n = 50
			if(painter.get_numfigure() != 50)
				painter.set_numfigure(50);
			break;
		case 2:	// n = 100
			if(painter.get_numfigure() != 100)
				painter.set_numfigure(100);
			break;
		case 3:	// n = 500
			if(painter.get_numfigure() != 500)
				painter.set_numfigure(500);
			break;
		case 4:	// n = 1000
			if(painter.get_numfigure() != 1000)
				painter.set_numfigure(1000);
			break;
		case 41:	// n = 5000
			if(painter.get_numfigure() != 5000)
				painter.set_numfigure(5000);
			break;
		case 5:	// c = red
			painter.set_colors(RED);
			break;
		case 6:	// c = green	
			painter.set_colors(GREEN);
			break;
		case 7:	// c = blue
			painter.set_colors(BLUE);
			break;
		case 8:	// c = random
			painter.set_colors(RANDOM);
			break;
		case 9:	// f = circle
			painter.set_polygon(CIRCLE);
			break;
		case 10:	// f = star
			painter.set_polygon(STAR);
			break;
		case 11:	// f = square
			painter.set_polygon(SQUARE);
			break;
		case 12:	// f = triangle
			painter.set_polygon(TRIANGLE);
			break;
		case 13:	// f = random
			painter.set_polygon(RANDOM);
			break;
		default :
			break;
	}
	glutPostRedisplay();

	return;
}

void drawBottom()
{
	glColor3f(0.7f, 0.9f, 0.7f);
	glBegin(GL_POLYGON);
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f(-5.0f, -0.5f, 0.0f);
	glVertex3f(5.0f, -0.5f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(-5.0f, -0.5f, 0.0f);
	glVertex3f(-5.0f, -1.0f, 0.0f);
	glVertex3f(-4.8f, -1.0f, 0.0f);
	glVertex3f(-4.8f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-3.85f, -0.5f, 0.0f);
	glVertex3f(-3.85f, -1.0f, 0.0f);
	glVertex3f(-3.65f, -1.0f, 0.0f);
	glVertex3f(-3.65f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-2.6f, -0.5f, 0.0f);
	glVertex3f(-2.6f, -1.0f, 0.0f);
	glVertex3f(-2.4f, -1.0f, 0.0f);
	glVertex3f(-2.4f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.35f, -0.5f, 0.0f);
	glVertex3f(-1.35f, -1.0f, 0.0f);
	glVertex3f(-1.15f, -1.0f, 0.0f);
	glVertex3f(-1.15f, -0.5f, 0.0f);
	glEnd();

	
	glBegin(GL_POLYGON);
	glVertex3f(-0.1f, -0.5f, 0.0f);
	glVertex3f(-0.1f, -1.0f, 0.0f);
	glVertex3f(0.1f, -1.0f, 0.0f);
	glVertex3f(0.1f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.35f, -0.5f, 0.0f);
	glVertex3f(1.35f, -1.0f, 0.0f);
	glVertex3f(1.15f, -1.0f, 0.0f);
	glVertex3f(1.15f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.4f, -0.5f, 0.0f);
	glVertex3f(2.4f, -1.0f, 0.0f);
	glVertex3f(2.6f, -1.0f, 0.0f);
	glVertex3f(2.6f, -0.5f, 0.0f);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(3.85f, -0.5f, 0.0f);
	glVertex3f(3.85f, -1.0f, 0.0f);
	glVertex3f(3.65f, -1.0f, 0.0f);
	glVertex3f(3.65f, -0.5f, 0.0f);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(4.8f, -0.5f, 0.0f);
	glVertex3f(4.8f, -1.0f, 0.0f);
	glVertex3f(5.0f, -1.0f, 0.0f);
	glVertex3f(5.0f, -0.5f, 0.0f);
	glEnd();
}


