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

void init();
void display();
void reshape(int, int);
void idle();
void keyboard(unsigned char, int, int);
void special(int, int, int);

GLuint		program;

GLint			loc_a_vertex;
GLint 			loc_a_normal;

GLint			loc_modelview_matrix;
GLint 			loc_projection_matrix;
GLint 			loc_normal_matrix;
GLint 			loc_light_position;
GLint  			loc_shininess;
GLint  			loc_a_product;
GLint  			loc_d_product;
GLint  			loc_s_product; 


glm::mat4 mat_VM;
glm::vec4 l_position;

std::string g_filename;
Object		  g_model;      // object
Camera		  g_camera;			// viewer (you)

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		g_filename = argv[2];
	}
	else
	{
		g_filename = "./data/cube.obj";
	}    

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
	g_model.load_simple_obj(g_filename);
	// g_model.print();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    // for filled polygon rendering  

  // TODO: 1. Implement vertex/fragment shader codes for Phong shading model
	program = Shader::create_program("./shader/simple.vert", "./shader/simple.frag");

  // TODO: 2. Get locations of shader variables in shader program
	loc_modelview_matrix	= glGetUniformLocation(program, "modelview_matrix");

	loc_projection_matrix	= glGetUniformLocation(program, "projection_matrix");

	loc_normal_matrix	= glGetUniformLocation(program, "normal_matrix");

	loc_light_position	= glGetUniformLocation(program, "l_position");

	loc_shininess	= glGetUniformLocation(program, "shininess");

	loc_a_product	= glGetUniformLocation(program, "a_product");
	loc_d_product	= glGetUniformLocation(program, "d_product");
	loc_s_product	= glGetUniformLocation(program, "s_product");

	loc_a_normal			= glGetAttribLocation(program, "a_normal");

	loc_a_vertex			= glGetAttribLocation(program, "a_vertex");

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);


	glUseProgram(program);

	// Camera setting
	glm::mat4   mat_Proj, mat_View, mat_Model;
	glm::mat3   mat_Normal;

	l_position = glm::vec4(1.3,0.0,1.3,1) ;

	// camera extrinsic param
	mat_View = glm::lookAt(
		g_camera.position(),				// eye position
		g_camera.center_position(), // center position
		g_camera.up_direction()			// up direction 
		);

	// camera intrinsic param
	mat_Proj  = glm::perspective(g_camera.fovy(), 1.0f, 0.001f, 10000.0f);  	
	
	mat_Model = glm::mat4(1.0);
	
	mat_VM   = mat_View*mat_Model;

	l_position = mat_VM * l_position;

	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));

	
	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));
	
  // TODO: 3. Extend Object::draw function to pass variables to the shader program
	g_model.draw(loc_a_vertex, loc_a_normal, loc_a_product, loc_d_product
		, loc_s_product, loc_shininess);
	
	glUseProgram(0);

	Shader::check_gl_error("draw");

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y)
{  
	if ('a' == key || 'A' == key)
	{
		g_camera.rotate_left(0.1);
	}
	else if ('d' == key || 'D' == key)
	{
		g_camera.rotate_right(0.1);
	}

  glutPostRedisplay();
}

void special(int key, int x, int y)
{	
	switch (key)
	{
	case GLUT_KEY_UP:
		g_camera.move_forward(1.0);
		break;
	case GLUT_KEY_DOWN:
		g_camera.move_backward(1.0);
		break;
	case GLUT_KEY_LEFT:
		g_camera.move_left(1.0);
		break;
	case GLUT_KEY_RIGHT:
		g_camera.move_right(1.0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void idle()
{
	glutPostRedisplay();
}
