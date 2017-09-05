// Defines the entry point for the console application.
//
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <cstdlib>

#include "Camera.h"
#include "Shader.h"
#include "LiveObj.h"
#include "Window.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <SOIL.h>


#define PI 3.14159f
#define CENTER_X 0.0f
#define CENTER_Z -65.0f
#define RADIUS 20.0f
#define AIMINV 0.063f
#define LIGHT_H 18.0f






void init();
void display();
void reshape(int, int);
void idle();
void keyboard(unsigned char, int, int);
void special(int, int, int);
bool Checkboolean(int flag);
GLint SortObjectDistance(void);
int CompareDistance(const void* a, const void* b);

GLuint		program, s_program, sp_program, g_program;

GLint			loc_a_vertex;
GLint       		loc_a_texcoord;
GLint 			loc_a_normal;

GLint			loc_modelview_matrix;
GLint 			loc_projection_matrix;
GLint 			loc_normal_matrix;
GLint 			loc_light_position;
GLint  			loc_a_product;
GLint  			loc_s_product;
GLint  			loc_shininess;
GLint  			loc_d_product;
GLint                         loc_u_texid;


GLint			loc_s_modelview_matrix;
GLint 			loc_s_projection_matrix;
GLint 			loc_s_light_position;
GLint 			loc_s_normal_matrix;
GLint 			loc_s_a_normal;

GLint			loc_s_a_vertex;
GLint  			loc_s_a_product;
GLint  			loc_s_s_product;
GLint  			loc_s_shininess;
GLint  			loc_s_d_product;


GLint       loc_sp_a_vertex;
GLint       loc_sp_a_texcoord;
GLint       loc_sp_u_texid;
GLint 	loc_sp_u_pvm_matrix;


GLint			loc_g_modelview_matrix;
GLint 			loc_g_projection_matrix;
GLint 			loc_g_normal_matrix;
GLint 			loc_g_light_position;
GLint  			loc_g_d_product;
GLint                         loc_g_u_texid;
GLint   			loc_g_a_vertex;
GLint			loc_g_a_texcoord ;
GLint 			loc_g_a_normal;



GLuint      tile_texid;
GLuint   	  aim_texid;
GLuint   	  pro_texid;



int windowPosX;
int windowPosY;


glm::mat4 mat_VM;
glm::vec4 l_position;

std::string g_filename;
LiveObj liveobj[17];


Fountain F;

Camera		  g_camera;			// viewer (you)






std::vector<glm::vec3> vertices, a_vertices, p_vertices;
std::vector<glm::vec2> texcoords, a_texcoords, p_texcoords;




void load_texture(GLuint *textureid,const char* filename);
void init_texcoord();





int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	Window* mainWindow = new Window(800, 800, 100, 100, "Image Texture Mapping");
	
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

	init_texcoord();

  	load_texture(&tile_texid,"./data/pattern1.jpg");

  	load_texture(&aim_texid,"./data/green.png");

  	load_texture(&pro_texid,"./data/professor.JPG");



	liveobj[FOUNTAIN].load_simple_obj("./data/Fountain/11686_Fountain.obj");

	liveobj[STAR].load_simple_obj("./data/star/3d-model.obj");

	liveobj[GUN].load_simple_obj("./data/m4a1/obj/m4a1_s.obj");
	liveobj[GUN].load_texture("./data/m4a1/obj/M4A1-s.tga");

	liveobj[IRON_MAN].load_simple_obj("./data/IronMan/Iron_Man_mark_7.obj");
	liveobj[IRON_MAN].load_texture("./data/IronMan/Iron_Man_mark_7_D.tga");

	liveobj[HULK].load_simple_obj("./data/Hulk/Hulk_Avengers.obj");
	liveobj[HULK].load_texture("./data/Hulk/Hulk_D.tga");

	liveobj[SPIDER].load_simple_obj("./data/SpiderMan/Spider-Man.obj");
	liveobj[SPIDER].load_texture("./data/SpiderMan/Spider-Man_D.tga");

	liveobj[VENOM].load_simple_obj("./data/Venom/Venom.obj");
	liveobj[VENOM].load_texture("./data/Venom/Venom_D.tga");

	liveobj[THOR].load_simple_obj("./data/Thor/Thor_Avengers.obj");
	liveobj[THOR].load_texture("./data/Thor/Thor_D.tga");

	liveobj[HORUS].load_simple_obj("./data/Horus/Horus.obj");
	liveobj[HORUS].load_texture("./data/Horus/Horus_D.tga");

	liveobj[STANE].load_simple_obj("./data/Stane/Ezekiel_Stane.obj");
	liveobj[STANE].load_texture("./data/Stane/Ezekiel_Stane_S.tga");

	liveobj[DEADPOOL].load_simple_obj("./data/Deadpool/deadpool.obj");
	liveobj[DEADPOOL].load_texture("./data/Deadpool/CHR_Deadpool_Body_TEXTSET_Color_NormX.jpg");

	liveobj[SILVER].load_simple_obj("./data/Silver_Surfer/Silver_Surfer.obj");
	liveobj[SILVER].load_texture("./data/Silver_Surfer/SilverSurfer_D.tga");

	liveobj[ROBOCOP].load_simple_obj("./data/Robocop/Robocop_Black.obj");
	liveobj[ROBOCOP].load_texture("./data/Robocop/Robocop_Black_D.tga");

	liveobj[CYCLOPS].load_simple_obj("./data/Cyclops/cyclops.obj");
	liveobj[CYCLOPS].load_texture("./data/Cyclops/Tex_14994.tga");

	liveobj[FLASH].load_simple_obj("./data/Flash/Flash.obj");
	liveobj[FLASH].load_texture("./data/Flash/Flash_D.tga");

	liveobj[ANT_MAN].load_simple_obj("./data/AntMan/Ant-Man.obj");
	liveobj[ANT_MAN].load_texture("./data/AntMan/Ant-Man_D.tga");






	glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_EQUAL);
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
  	glFrontFace(GL_CCW);

	glClearColor(0.1f, 0.1f, 0.240f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    // for filled polygon rendering  

  // TODO: 1. Implement vertex/fragment shader codes for Phong shading model
	program = Shader::create_program("./shader/texture.vert", "./shader/texture.frag");
	s_program = Shader::create_program("./shader/simple.vert", "./shader/simple.frag");
	sp_program = Shader::create_program("./shader/spark.vert", "./shader/spark.frag");
	g_program = Shader::create_program("./shader/gun.vert", "./shader/gun.frag");

  // TODO: 2. Get locations of shader variables in shader program
	loc_modelview_matrix	= glGetUniformLocation(program, "modelview_matrix");
	loc_projection_matrix	= glGetUniformLocation(program, "projection_matrix");
	loc_normal_matrix	= glGetUniformLocation(program, "normal_matrix");
	loc_light_position	= glGetUniformLocation(program, "l_position");
	loc_a_product	= glGetUniformLocation(program, "a_product");
	loc_d_product	= glGetUniformLocation(program, "d_product");
	loc_s_product	= glGetUniformLocation(program, "s_product");
	loc_shininess	= glGetUniformLocation(program, "shininess");
	loc_a_vertex			= glGetAttribLocation(program, "a_vertex");
	loc_a_texcoord               = glGetAttribLocation(program, "a_texcoord");
	loc_a_normal			= glGetAttribLocation(program, "a_normal");
	loc_u_texid 			= glGetUniformLocation(program, "u_texid");


	loc_s_modelview_matrix	= glGetUniformLocation(s_program, "modelview_matrix");
	loc_s_projection_matrix	= glGetUniformLocation(s_program, "projection_matrix");
	loc_s_normal_matrix	= glGetUniformLocation(s_program, "normal_matrix");
	loc_s_light_position	= glGetUniformLocation(s_program, "l_position");
	loc_s_shininess	= glGetUniformLocation(s_program, "shininess");
	loc_s_a_product	= glGetUniformLocation(s_program, "a_product");
	loc_s_d_product	= glGetUniformLocation(s_program, "d_product");
	loc_s_s_product	= glGetUniformLocation(s_program, "s_product");
	loc_s_a_normal			= glGetAttribLocation(s_program, "a_normal");
	loc_s_a_vertex			= glGetAttribLocation(s_program, "a_vertex");


	loc_sp_u_pvm_matrix = glGetUniformLocation(sp_program, "u_pvm_matrix");
	loc_sp_a_vertex = glGetAttribLocation(sp_program, "a_vertex");
	loc_sp_a_texcoord  = glGetAttribLocation(sp_program, "a_texcoord");
	loc_sp_u_texid = glGetUniformLocation(sp_program, "u_texid");


	loc_g_modelview_matrix = glGetUniformLocation(g_program, "modelview_matrix");
	loc_g_projection_matrix = glGetUniformLocation(g_program, "projection_matrix");
	loc_g_normal_matrix = glGetUniformLocation(g_program, "normal_matrix");
	loc_g_light_position = glGetUniformLocation(g_program, "l_position");
	loc_g_d_product = glGetUniformLocation(g_program, "d_product");
	loc_g_a_normal = glGetAttribLocation(g_program, "a_normal");
 	loc_g_u_texid = glGetUniformLocation(g_program, "u_texid");
 	loc_g_a_vertex = glGetAttribLocation(g_program, "a_vertex");
	loc_g_a_texcoord  = glGetAttribLocation(g_program, "a_texcoord");



	F.set_location(loc_s_a_vertex, loc_s_a_normal,
  					loc_s_a_product, loc_s_d_product,
  					loc_s_s_product, loc_s_shininess);
	F.set_velocity();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera setting
	glm::mat4   mat_Proj, mat_View, mat_Model, mat_PVM;
	glm::mat3   mat_Normal;

	l_position = glm::vec4(CENTER_X,LIGHT_H,CENTER_Z,1.0) ;

	// camera extrinsic param
	mat_View = glm::lookAt(
		g_camera.position(),				// eye position
		g_camera.center_position(), // center position
		g_camera.up_direction()			// up direction 
		);
	// camera intrinsic param
	mat_Proj  = glm::perspective(glm::radians(g_camera.fovy()), 1.0f, 0.001f, 10000.0f);

	l_position = mat_View * l_position;

	mat_PVM = mat_Proj*mat_View*mat_Model;



	// Draw Tile
	glUseProgram(sp_program);
	
	mat_Model = glm::mat4(1.0);
	//mat_Model*= glm::translate( glm::vec3(CENTER_X, -1.5, CENTER_Z) );
	//mat_Model *= glm::scale( glm::vec3(0.45,0.45, 0.45) );
	glUniform1i(loc_sp_u_texid, 0);
  	glActiveTexture(GL_TEXTURE0);
  	glBindTexture(GL_TEXTURE_2D, tile_texid);

  	 glUniformMatrix4fv(loc_sp_u_pvm_matrix, 1, false, glm::value_ptr(mat_PVM));

  	glVertexAttribPointer(loc_sp_a_vertex, 3, GL_FLOAT, false, 0, vertices.data());
  	glVertexAttribPointer(loc_sp_a_texcoord, 2, GL_FLOAT, false, 0, texcoords.data());

  	glEnableVertexAttribArray(loc_sp_a_vertex);
  	glEnableVertexAttribArray(loc_sp_a_texcoord);

  	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  	glDisableVertexAttribArray(loc_sp_a_vertex);
  	glDisableVertexAttribArray(loc_sp_a_texcoord);



  	// Draw Aim
  	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(0.0,AIMINV,0.0) );


  	glUniform1i(loc_sp_u_texid, 1);
  	glActiveTexture(GL_TEXTURE1);
  	glBindTexture(GL_TEXTURE_2D, aim_texid);

  	 glUniformMatrix4fv(loc_sp_u_pvm_matrix, 1, false, glm::value_ptr(mat_Model));

  	glVertexAttribPointer(loc_sp_a_vertex, 3, GL_FLOAT, false, 0, a_vertices.data());
  	glVertexAttribPointer(loc_sp_a_texcoord, 2, GL_FLOAT, false, 0, a_texcoords.data());

  	glEnableVertexAttribArray(loc_sp_a_vertex);
  	glEnableVertexAttribArray(loc_sp_a_texcoord);

  	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  	glDisableVertexAttribArray(loc_sp_a_vertex);
  	glDisableVertexAttribArray(loc_sp_a_texcoord);



  	mat_Model = glm::mat4(1.0);
  	mat_Model *= glm::rotate( 90*(PI/180.0f), glm::vec3(0.0, 0.0, 1.0) );
	mat_Model*= glm::translate( glm::vec3(0.0,AIMINV,0.0) );
	

  	glUniform1i(loc_sp_u_texid, 1);
  	glActiveTexture(GL_TEXTURE1);
  	glBindTexture(GL_TEXTURE_2D, aim_texid);

  	 glUniformMatrix4fv(loc_sp_u_pvm_matrix, 1, false, glm::value_ptr(mat_Model));

  	glVertexAttribPointer(loc_sp_a_vertex, 3, GL_FLOAT, false, 0, a_vertices.data());
  	glVertexAttribPointer(loc_sp_a_texcoord, 2, GL_FLOAT, false, 0, a_texcoords.data());

  	glEnableVertexAttribArray(loc_sp_a_vertex);
  	glEnableVertexAttribArray(loc_sp_a_texcoord);

  	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  	glDisableVertexAttribArray(loc_sp_a_vertex);
  	glDisableVertexAttribArray(loc_sp_a_texcoord);



  	mat_Model = glm::mat4(1.0);
  	mat_Model *= glm::rotate( 180*(PI/180.0f), glm::vec3(0.0, 0.0, 1.0) );
	mat_Model*= glm::translate( glm::vec3(0.0,AIMINV,0.0) );

  	glUniform1i(loc_sp_u_texid, 1);
  	glActiveTexture(GL_TEXTURE1);
  	glBindTexture(GL_TEXTURE_2D, aim_texid);

  	 glUniformMatrix4fv(loc_sp_u_pvm_matrix, 1, false, glm::value_ptr(mat_Model));

  	glVertexAttribPointer(loc_sp_a_vertex, 3, GL_FLOAT, false, 0, a_vertices.data());
  	glVertexAttribPointer(loc_sp_a_texcoord, 2, GL_FLOAT, false, 0, a_texcoords.data());

  	glEnableVertexAttribArray(loc_sp_a_vertex);
  	glEnableVertexAttribArray(loc_sp_a_texcoord);

  	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  	glDisableVertexAttribArray(loc_sp_a_vertex);
  	glDisableVertexAttribArray(loc_sp_a_texcoord);



  	mat_Model = glm::mat4(1.0);
	mat_Model *= glm::rotate( -90*(PI/180.0f), glm::vec3(0.0, 0.0, 1.0) );
	mat_Model*= glm::translate( glm::vec3(0.0,AIMINV,0.0) );

  	glUniform1i(loc_sp_u_texid, 1);
  	glActiveTexture(GL_TEXTURE1);
  	glBindTexture(GL_TEXTURE_2D, aim_texid);

  	 glUniformMatrix4fv(loc_sp_u_pvm_matrix, 1, false, glm::value_ptr(mat_Model));

  	glVertexAttribPointer(loc_sp_a_vertex, 3, GL_FLOAT, false, 0, a_vertices.data());
  	glVertexAttribPointer(loc_sp_a_texcoord, 2, GL_FLOAT, false, 0, a_texcoords.data());

  	glEnableVertexAttribArray(loc_sp_a_vertex);
  	glEnableVertexAttribArray(loc_sp_a_texcoord);

  	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  	glDisableVertexAttribArray(loc_sp_a_vertex);
  	glDisableVertexAttribArray(loc_sp_a_texcoord);




  	//Draw Professor
  	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(0.0,0.0,7.0) );
	mat_Model *= glm::rotate( 180*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	mat_Model *= glm::scale( glm::vec3(3.0f,3.0f, 3.0f) );
	glUniform1i(loc_sp_u_texid, 2);
  	glActiveTexture(GL_TEXTURE2);
  	glBindTexture(GL_TEXTURE_2D, pro_texid);

  	mat_PVM = mat_Proj * mat_View * mat_Model;
  	 glUniformMatrix4fv(loc_sp_u_pvm_matrix, 1, false, glm::value_ptr(mat_PVM));

  	glVertexAttribPointer(loc_sp_a_vertex, 3, GL_FLOAT, false, 0, p_vertices.data());
  	glVertexAttribPointer(loc_sp_a_texcoord, 2, GL_FLOAT, false, 0, p_texcoords.data());

  	glEnableVertexAttribArray(loc_sp_a_vertex);
  	glEnableVertexAttribArray(loc_sp_a_texcoord);

  	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  	glDisableVertexAttribArray(loc_sp_a_vertex);
  	glDisableVertexAttribArray(loc_sp_a_texcoord);


  	glUseProgram(0);

	  	
	
/*
*   Simple Shader
*
*/



	glUseProgram(s_program);



	//Draw Star (Center)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(CENTER_X, LIGHT_H, CENTER_Z) );
	//mat_Model *= glm::rotate( 90*(PI/180.0f), glm::vec3(1.0, 0.0, 0.0) );
	mat_Model *= glm::scale( glm::vec3(0.40,0.40, 0.40) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));

	liveobj[STAR].SetModelMatrix(mat_Model);
	glUniformMatrix4fv(loc_s_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_s_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_s_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_s_light_position,  1, glm::value_ptr(l_position));
	liveobj[STAR].simple_draw(loc_s_a_vertex, loc_s_a_normal,
		loc_s_a_product, loc_s_d_product,
		loc_s_s_product, loc_s_shininess);





	// Draw Fountaion (Center)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(CENTER_X, -1.5, CENTER_Z) );
	mat_Model *= glm::scale( glm::vec3(0.45,0.45, 0.45) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));

	liveobj[FOUNTAIN].SetModelMatrix(mat_Model);
	glUniformMatrix4fv(loc_s_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_s_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_s_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_s_light_position,  1, glm::value_ptr(l_position));
	liveobj[FOUNTAIN].simple_draw(loc_s_a_vertex, loc_s_a_normal,
		loc_s_a_product, loc_s_d_product,
		loc_s_s_product, loc_s_shininess);



	// Draw Water (center)
	glUniform4fv(loc_s_light_position,  1, glm::value_ptr(l_position));
	glUniformMatrix4fv(loc_s_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	F.DrawFountain(mat_View, loc_s_modelview_matrix, loc_s_normal_matrix);

	glUseProgram(0);




/*
*   Gun Shader
*
*/


	glUseProgram(g_program);

	// Draw Gun 
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(0.0,-0.02,0.07) );
	mat_Model *= glm::rotate( 180*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	mat_Model *= glm::scale( glm::vec3(0.01,0.01, 0.01) );
	mat_VM   = mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));

	//printf("%f %f %f\n",l_position.x, l_position.y, l_position.z);

	glUniformMatrix4fv(loc_g_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_g_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_g_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_g_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_g_u_texid, 13);
  	glActiveTexture(GL_TEXTURE13);
  	glBindTexture(GL_TEXTURE_2D, liveobj[GUN].textureid);
	liveobj[GUN].gun_draw(loc_g_a_vertex, loc_g_a_normal, loc_g_d_product,loc_g_a_texcoord);

	glUseProgram(0);


/*
*   Texture Shader
*
*/


	glUseProgram(program);


	// Draw IronMan (12'o)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(CENTER_X, 0.0, CENTER_Z - RADIUS) );
	// mat_Model *= glm::rotate( 0*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	// mat_Model *= glm::scale( glm::vec3(0.5,0.5, 0.5) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[IRON_MAN].SetModelMatrix(mat_Model);

	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 0);
  	glActiveTexture(GL_TEXTURE0);
  	glBindTexture(GL_TEXTURE_2D, liveobj[IRON_MAN].textureid);
	liveobj[IRON_MAN].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);


	// Draw Hulk (Right 60)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(60.0f*(PI/180.0f)), 0.0,
										 CENTER_Z + RADIUS * sin(-60.0f*(PI/180.0f))) );
	mat_Model *= glm::rotate( -30.0f*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	//mat_Model *= glm::scale( glm::vec3(0.024,0.024, 0.024) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[HULK].SetModelMatrix(mat_Model);
	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

  	glUniform1i(loc_u_texid, 1);
  	glActiveTexture(GL_TEXTURE1);
  	glBindTexture(GL_TEXTURE_2D, liveobj[HULK].textureid);
	liveobj[HULK].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);


	// Draw Thor(Right 30)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(30.0f*(PI/180.0f)), 0.0, 
										CENTER_Z + RADIUS * sin(-30.0f*(PI/180.0f))) );
	mat_Model *= glm::rotate( -60.0f*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	//mat_Model *= glm::scale( glm::vec3(0.024,0.024, 0.024) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[THOR].SetModelMatrix(mat_Model);
	
	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 2);
  	glActiveTexture(GL_TEXTURE2);
  	glBindTexture(GL_TEXTURE_2D, liveobj[THOR].textureid);
	liveobj[THOR].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);




	// Draw Venom (Right)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(CENTER_X + RADIUS, 0.0, CENTER_Z) );
	mat_Model *= glm::rotate( -90.0f*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	//mat_Model *= glm::scale( glm::vec3(0.024,0.024, 0.024) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[VENOM].SetModelMatrix(mat_Model);
	
	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 3);
  	glActiveTexture(GL_TEXTURE3);
  	glBindTexture(GL_TEXTURE_2D, liveobj[VENOM].textureid);
	liveobj[VENOM].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);


	// Draw SilverSufer(Right -30)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(-30.0f*(PI/180.0f)), 0.0, 
										CENTER_Z + RADIUS * sin(30.0f*(PI/180.0f))) );
	mat_Model *= glm::rotate( -120.0f*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	//mat_Model *= glm::scale( glm::vec3(0.024,0.024, 0.024) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[SILVER].SetModelMatrix(mat_Model);

	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 4);
  	glActiveTexture(GL_TEXTURE4);
  	glBindTexture(GL_TEXTURE_2D, liveobj[SILVER].textureid);
	liveobj[SILVER].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);






	// Draw AntMan(Right -60)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(-60.0f*(PI/180.0f)), 0.0, 
										CENTER_Z + RADIUS * sin(60.0f*(PI/180.0f))) );
	mat_Model *= glm::rotate( -150.0f*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	//mat_Model *= glm::scale( glm::vec3(0.024,0.024, 0.024) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[ANT_MAN].SetModelMatrix(mat_Model);
	
	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 5);
  	glActiveTexture(GL_TEXTURE5);
  	glBindTexture(GL_TEXTURE_2D, liveobj[ANT_MAN].textureid);
	liveobj[ANT_MAN].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);


	// Draw Robocop(Right Road)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(-60.0f*(PI/180.0f)), 0.0, 
										CENTER_Z + RADIUS * sin(60.0f*(PI/180.0f))) );
	mat_Model*= glm::translate( glm::vec3( 0.0f, 0.0f, 15.0f));
	mat_Model *= glm::rotate( -90.0f*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	mat_Model *= glm::scale( glm::vec3(1.2f,1.2f, 1.2f) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[ROBOCOP].SetModelMatrix(mat_Model);
	
	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 6);
  	glActiveTexture(GL_TEXTURE6);
  	glBindTexture(GL_TEXTURE_2D, liveobj[ROBOCOP].textureid);
	liveobj[ROBOCOP].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);



	// Draw Cyclops(Left Road)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(-120.0f*(PI/180.0f)), 0.0, 
										CENTER_Z + RADIUS * sin(120.0f*(PI/180.0f))) );
	mat_Model*= glm::translate( glm::vec3( 0.0f, 0.0f, 15.0f));
	// mat_Model *= glm::rotate( 90*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	mat_Model *= glm::scale( glm::vec3(0.048,0.048, 0.048) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[CYCLOPS].SetModelMatrix(mat_Model);

	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 7);
  	glActiveTexture(GL_TEXTURE7);
  	glBindTexture(GL_TEXTURE_2D, liveobj[CYCLOPS].textureid);
	liveobj[CYCLOPS].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);




	// Draw Flash(Left -60)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(-120.0f*(PI/180.0f)), 0.0, 
										CENTER_Z + RADIUS * sin(120.0f*(PI/180.0f))) );
	mat_Model *= glm::rotate( 150*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	mat_Model *= glm::scale( glm::vec3(1.2f,1.2f, 1.2f) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[FLASH].SetModelMatrix(mat_Model);

	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 8);
  	glActiveTexture(GL_TEXTURE8);
  	glBindTexture(GL_TEXTURE_2D, liveobj[FLASH].textureid);
	liveobj[FLASH].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);




	// Draw Stane(Left -30)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(-150.0f*(PI/180.0f)), 0.0f, 
										CENTER_Z + RADIUS * sin(150.0f*(PI/180.0f))) );
	mat_Model *= glm::rotate( 120*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	mat_Model *= glm::scale( glm::vec3(1.2f,1.2f, 1.2f) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[STANE].SetModelMatrix(mat_Model);

	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 9);
  	glActiveTexture(GL_TEXTURE9);
  	glBindTexture(GL_TEXTURE_2D, liveobj[STANE].textureid);
	liveobj[STANE].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);




	//Draw Deadpool (Left)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3(CENTER_X - RADIUS, 0.0, CENTER_Z) );
	mat_Model *= glm::scale( glm::vec3(0.024,0.024, 0.024) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[DEADPOOL].SetModelMatrix(mat_Model);

	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));

	glUniform1i(loc_u_texid, 10);
  	glActiveTexture(GL_TEXTURE10);
  	glBindTexture(GL_TEXTURE_2D, liveobj[DEADPOOL].textureid);
	liveobj[DEADPOOL].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);





	// Draw SpiderMan(Left 30)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(150.0f*(PI/180.0f)), 0.0, 
										CENTER_Z + RADIUS * sin(-150.0f*(PI/180.0f))) );
	mat_Model *= glm::rotate( 30*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	//mat_Model *= glm::scale( glm::vec3(0.024,0.024, 0.024) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[SPIDER].SetModelMatrix(mat_Model);

	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));


	glUniform1i(loc_u_texid, 11);
  	glActiveTexture(GL_TEXTURE11);
  	glBindTexture(GL_TEXTURE_2D, liveobj[SPIDER].textureid);
	liveobj[SPIDER].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
							loc_d_product, loc_s_product,
							loc_shininess, loc_a_texcoord);
	




	// Draw Horus(Left 30)
	mat_Model = glm::mat4(1.0);
	mat_Model*= glm::translate( glm::vec3( CENTER_X + RADIUS * cos(120.0f*(PI/180.0f)), 0.0, 
										CENTER_Z + RADIUS * sin(-120.0f*(PI/180.0f))) );
	mat_Model *= glm::rotate( 30*(PI/180.0f), glm::vec3(0.0, 1.0, 0.0) );
	//mat_Model *= glm::scale( glm::vec3(0.024,0.024, 0.024) );
	mat_VM   = mat_View*mat_Model;
	mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
	liveobj[HORUS].SetModelMatrix(mat_Model);

	glUniformMatrix4fv(loc_modelview_matrix, 1, false, glm::value_ptr(mat_VM));
	glUniformMatrix4fv(loc_projection_matrix, 1, false, glm::value_ptr(mat_Proj));
	glUniformMatrix3fv(loc_normal_matrix, 1, false, glm::value_ptr(mat_Normal));
	glUniform4fv(loc_light_position,  1, glm::value_ptr(l_position));


	glUniform1i(loc_u_texid, 12);
  	glActiveTexture(GL_TEXTURE12);
  	glBindTexture(GL_TEXTURE_2D, liveobj[HORUS].textureid);
	liveobj[HORUS].draw_live(loc_a_vertex, loc_a_normal,loc_a_product,
						 loc_d_product, loc_s_product,
						 loc_shininess, loc_a_texcoord);

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
		g_camera.rotate_right(0.1);
		// g_ant_man.print();
	}
	else if ('d' == key || 'D' == key)
	{
		g_camera.rotate_left(0.1);
	}
	else if('z' == key || 'Z' == key)
	{
		if(!g_camera.IsZoom())
		{
			g_camera.set_fovy(20);
	  		g_camera.SetZoom();
		}
		 
		else
		{
			g_camera.set_fovy(100);
			g_camera.SetZoom();
		}
	}
	else if(' ' == key || key == 32)
	{
		GLint index= SortObjectDistance();
		for(int i=0;i<NUM_OF_OBJECT-3;i++)
		{
			if(liveobj[i].GetTextureID()== index)
			{
				liveobj[i].SetLifeFlag();
				break;
			}
		}
	}
	else if('r' == key || 'R' == key)
	{
		for(int i =1;i<NUM_OF_OBJECT-3;i++)
		{
			if(liveobj[i].GetLifeFlag() == false)
				liveobj[i].SetLifeFlag();
		}
	}

  glutPostRedisplay();
}

void special(int key, int x, int y)
{	
	switch (key)
	{
		case GLUT_KEY_UP:
			if(Checkboolean(1))
				g_camera.move_forward(1.0);
			break;
		
		case GLUT_KEY_DOWN:
			if(Checkboolean(2))
				g_camera.move_backward(1.0);
			break;
			
		case GLUT_KEY_LEFT:
			if(Checkboolean(3))
				g_camera.move_left(1.0);
			break;

		case GLUT_KEY_RIGHT:
			if(Checkboolean(4))
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

void load_texture(GLuint *textureid,const char* filename)
{
  int width, height, channels;
  GLubyte* image_data;

  // 1. load image data with SOIL library, in which the followings are automatically called
   glGenTextures(1, textureid);
   // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    *textureid = SOIL_load_OGL_texture
    (
      filename,
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

    
  if (*textureid== 0)
  {
    std::cerr << "Fail to load an image file with SOIL_load_OGL_texture() function." << std::endl;
    return;
  }

  // 2. create a texture object
  // glGenTextures(1, textureid);
  // 3. bind the texture object, so texture operations work for the binded texture object
  glBindTexture(GL_TEXTURE_2D, *textureid);
  // 4. upload texture data to the GPU
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

  // 5. set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // 6. destroy image data
  //delete[] image_data;
}


void init_texcoord()
{
	vertices.push_back(glm::vec3(-100.0f, 0.0f, 100.0f));
  	vertices.push_back(glm::vec3(100.0f, 0.0f, 100.0f));
  	vertices.push_back(glm::vec3(100.0f, 0.0f, -100.0f));
  	vertices.push_back(glm::vec3(-100.0f, 0.0f, -100.0f));

  	// texture coordinates
  	texcoords.push_back(glm::vec2(0.0f, 0.0f));
  	texcoords.push_back(glm::vec2(100.0f, 0.0f));
  	texcoords.push_back(glm::vec2(100.0f, 100.0f));
  	texcoords.push_back(glm::vec2(0.0f, 100.0f));



  	a_vertices.push_back(glm::vec3(-0.003f, 0.0f, 0.0f));
  	a_vertices.push_back(glm::vec3(0.003f, 0.0f, 0.0f));
  	a_vertices.push_back(glm::vec3(0.003f, 0.06f, 0.0f));
  	a_vertices.push_back(glm::vec3(-0.003f, 0.06f, 0.0f));

  	// texture coordinates
  	a_texcoords.push_back(glm::vec2(0.0f, 0.0f));
  	a_texcoords.push_back(glm::vec2(1.0f, 0.0f));
  	a_texcoords.push_back(glm::vec2(1.0f, 1.0f));
  	a_texcoords.push_back(glm::vec2(0.0f, 1.0f));


  	p_vertices.push_back(glm::vec3(-1.0f, 2.0f, 0.0f));
  	p_vertices.push_back(glm::vec3(1.0f, 2.0f, 0.0f));
  	p_vertices.push_back(glm::vec3(1.0f, 4.0f, 0.0f));
  	p_vertices.push_back(glm::vec3(-1.0f, 4.0f, 0.0f));


  	// texture coordinates
  	p_texcoords.push_back(glm::vec2(0.0f, 0.0f));
  	p_texcoords.push_back(glm::vec2(1.0f, 0.0f));
  	p_texcoords.push_back(glm::vec2(1.0f, 1.0f));
  	p_texcoords.push_back(glm::vec2(0.0f, 1.0f));


}

bool Checkboolean(int flag)
{
	for(int i=0; i<NUM_OF_OBJECT-3; i++)
		if(liveobj[i].IsBoundBoxMove(g_camera, flag))
			return false;
	return true;
}

GLint SortObjectDistance(void)
{
	GLint index;
	LiveObj* list = (LiveObj*)malloc(sizeof(LiveObj) * (NUM_OF_OBJECT-3));
	memset(list, 0, sizeof(LiveObj)*(NUM_OF_OBJECT-3));
	memcpy(list, liveobj, sizeof(LiveObj)*(NUM_OF_OBJECT-3));

	for(int i=0 ; i<NUM_OF_OBJECT-3 ; i++)
		list[i].SetCenterPos();

	qsort(list,NUM_OF_OBJECT-3, sizeof(LiveObj), CompareDistance);

	for(int i=0;i<NUM_OF_OBJECT-3;i++)
	{
		if(list[i].IsBoundBoxClick(g_camera))
		{
			index = list[i].GetTextureID();
			free(list);
			return index;
		}
	}
	free(list);
	return -1;
	
}

int CompareDistance(const void* a, const void* b)
{
	if(((LiveObj*)a)->ReturnDistance(g_camera) > ((LiveObj*)b)->ReturnDistance(g_camera))
		return 1;
	if(((LiveObj*)a)->ReturnDistance(g_camera) < ((LiveObj*)b)->ReturnDistance(g_camera))
		return -1;
	else
		return 0;
}