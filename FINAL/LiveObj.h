#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ctime>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"
#include "Object.h"
#include "SOIL.h"

#define NUM_OF_OBJECT 17
#define FOUNTAIN 0
#define IRON_MAN 1
#define HULK 2
#define THOR 3
#define VENOM 4
#define SILVER 5
#define ANT_MAN 6
#define ROBOCOP 7
#define CYCLOPS 8
#define FLASH 9
#define STANE 10
#define DEADPOOL 11
#define  SPIDER 12
#define HORUS 13
#define GUN  14
#define STAR 15
#define ROAD 16



#define WATER_COUNT 2500
#define GRAVITY 9.8f

#define X_ZERO 0.0f
#define X_MIN -5.0f
#define X_MAX 5.0f
#define Y_ZERO 3.8f
#define Y_MAX 20.0f
#define Z_ZERO -65.0f
#define Z_MIN -70.0f
#define Z_MAX -60.0f

#define VX_MAX 2.3f
#define VX_MIN  -2.3f
#define VY_MAX 10.0f
#define VY_MIN  6.0f
#define VZ_MAX 2.3f
#define VZ_MIN  -2.3f

#define INTERVAL 0.04f

class LiveObj : public Object
{
public:
  LiveObj() { life_flag = true;} 
  GLuint textureid;


  void load_texture( const char* filename);
  void draw_live(int loc_a_vertex, int loc_a_normal,
  int loc_u_material_ambient, int loc_u_material_diffuse,
  int loc_u_material_specular, int loc_u_material_shininess, int loc_a_texcoord);
  void simple_draw(int loc_a_vertex, int loc_a_normal,
  int loc_u_material_ambient, int loc_u_material_diffuse,
  int loc_u_material_specular, int loc_u_material_shininess);
  void gun_draw(int loc_a_vertex, int loc_a_normal, int loc_u_material_diffuse, int loc_a_texcoord);
  void SetLifeFlag(void);
  bool GetLifeFlag(void);
  void SetModelMatrix(glm::mat4 matrix);
  glm::mat4 GetModelMatrix(void);
  bool IsBoundBoxClick(Camera& camera);
  float ModifyValue(float num); //Make 0<=num<=1
  glm::vec4 GetMaxRange(void);
  glm::vec4 GetMinRange(void);
  void SwapValue(glm::vec4& min, glm::vec4& max);  //Swap value
  bool IsBoundBoxMove(Camera& camera, int flag); // forward : 1 , backward : 2 , left : 3, right : 4
  void SetCenterPos(void);
  float ReturnDistance(Camera& camera);
  GLint GetTextureID(void);
  
private:
  bool life_flag;
  float centerPos_X;
  float centerPos_Y;
  float centerPos_Z;
};


class Water {

public :
	LiveObj particle;
	float timer;
	float vx, vy, vz ;
	float x_aspect, y_aspect, z_aspect;

	Water()
	{
		particle.load_simple_obj("./data/water/water.obj");
		timer = 0.0;
		x_aspect = X_ZERO;
		y_aspect = Y_ZERO;
		z_aspect = Z_ZERO;
	}
	
};


class Fountain {

private :
	GLint 			loc_s_a_normal;
	GLint			loc_s_a_vertex;
	GLint  			loc_s_a_product;
	GLint  			loc_s_s_product;
	GLint  			loc_s_shininess;
	GLint  			loc_s_d_product;
	

public :
	Water *w;
	
	Fountain()
	{
		w = new Water[WATER_COUNT];
	}

	void set_location(int loc_a_vertex, int loc_a_normal,
  					int loc_u_material_ambient, int loc_u_material_diffuse,
  					int loc_u_material_specular, int loc_u_material_shininess);
	float x_calculate(int i);
	float y_calculate(int i);
	float z_calculate(int i);
	void DrawFountain(glm::mat4 mat_View,int loc_vm, int loc_nm);
	void set_velocity();
	~Fountain();
};

