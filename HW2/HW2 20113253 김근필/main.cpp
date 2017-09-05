// Defines the entry point for the console application.
//
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <fstream>

#include "Object.h"
#include "Camera.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>


#define PI 3.14159f
#define MOVE_DELTA 0.3f
#define ROTATE_DELTA 0.1f



void init();
void display();
void reshape(int, int);
void idle();
void keyboard(unsigned char, int, int);
void special(int, int, int);

GLuint		program;

GLint			loc_a_vertex;
GLint			loc_u_pvm_matrix;

glm::mat4 mat_PVM;

Object		g_desk, g_fan, g_sofa, g_tv;  // furniture
Camera		g_camera;											// viewer (you)

float g_aspect = 1.0f;
float fan_angle = 0.0f;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);  
	glutCreateWindow("Modeling & Navigating Your Studio");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(idle);

	if (glewInit() != GLEW_OK) 
	{
		std::cerr << "failed to initialize glew" << std::endl;
		return -1;
	}

	init();

	glutMainLoop();

	return 0;
}

void init()
{
	g_desk.load_simple_obj("./data/desk.obj");
	g_fan.load_simple_obj("./data/fan.obj");
	g_sofa.load_simple_obj("./data/sofa.obj");
	g_tv.load_simple_obj("./data/tv.obj");
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    // for wireframe rendering  

	program = Shader::create_program("./shader/simple.vert", "./shader/simple.frag");

	loc_u_pvm_matrix	= glGetUniformLocation(program, "u_pvm_matrix");

	loc_a_vertex			= glGetAttribLocation(program, "a_vertex");
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	// Camera setting
	glm::mat4   mat_Proj, mat_View, mat_Model;

	// camera extrinsic param
	mat_View = glm::lookAt(
		g_camera.position(),				// eye position
		g_camera.center_position(), // center position
		g_camera.up_direction()			// up direction 
		);
	// camera intrinsic param
	mat_Proj = glm::perspective(g_camera.fovy(), 1.0f, 0.001f, 10000.0f);



	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(-5.0, 0.0, 0.0) ); //= glTranslate()
	mat_Model *= glm::scale( glm::vec3(1.5, 1.5, 1.5) ); //=same as glScale()

	mat_PVM = mat_Proj*mat_View*mat_Model;
	glUniformMatrix4fv(loc_u_pvm_matrix, 1, false, glm::value_ptr(mat_PVM));
	g_desk.draw(loc_a_vertex);



	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(0.0, 5.0, 0.0) ); 
	mat_Model *= glm::rotate(fan_angle, glm::vec3(0.0, 1.0, 0.0) );
	mat_Model *= glm::scale( glm::vec3(1.5, 1.5, 1.5) );

	mat_PVM = mat_Proj*mat_View*mat_Model;
	glUniformMatrix4fv(loc_u_pvm_matrix, 1, false, glm::value_ptr(mat_PVM));
	g_fan.draw(loc_a_vertex);




	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(0.0, 0.0, 5.0) ); 
	mat_Model *= glm::rotate( 180.0f*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	mat_Model *= glm::scale( glm::vec3(1.5, 1.5, 1.5) );

	mat_PVM = mat_Proj*mat_View*mat_Model;
	glUniformMatrix4fv(loc_u_pvm_matrix, 1, false, glm::value_ptr(mat_PVM));
	g_sofa.draw(loc_a_vertex);




	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(0.0, 0.0, -5.0) ); 
	mat_Model *= glm::scale( glm::vec3(2.0, 2.0, 2.0) );

	mat_PVM = mat_Proj*mat_View*mat_Model;
	glUniformMatrix4fv(loc_u_pvm_matrix, 1, false, glm::value_ptr(mat_PVM));
	g_tv.draw(loc_a_vertex);

	glUseProgram(0);
	Shader::check_gl_error("draw");

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	g_aspect = width/height;
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key){
		case 'A':
		case 'a':
			g_camera.rotate_left(ROTATE_DELTA);
			break;
		case 'D':
		case 'd':
			g_camera.rotate_right(ROTATE_DELTA);
			break;
	}

	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch(key) {
		case GLUT_KEY_LEFT: 
			g_camera.move_left(MOVE_DELTA);
			break;
     		case GLUT_KEY_RIGHT:  
     			g_camera.move_right(MOVE_DELTA);
     			break;
     		case GLUT_KEY_UP:  
     			g_camera.move_forward(MOVE_DELTA);
     			break;
     		case GLUT_KEY_DOWN:  
     			g_camera.move_backward(MOVE_DELTA);
    			 break;
    		default :
    			break;
    	 }

    	 glutPostRedisplay();
}

void idle()
{
	fan_angle += 0.12f;
	glutPostRedisplay();
}
