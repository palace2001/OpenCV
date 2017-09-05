// main.cpp : Defines the entry point for the console application.
//

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <SOIL.h>

void init();
void load_texture(GLuint *textureid, const char* filename);

void display();
void reshape(int, int);
void idle();
void keyboard(unsigned char, int, int);
void special(int, int, int);

GLuint      program;

GLint       loc_a_vertex;
GLint       loc_a_texcoord;

GLint       loc_u_pvm_matrix;
GLint       loc_u_texid;

glm::mat4   mat_PVM;

glm::vec3   vec_eye = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3   vec_center = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3   vec_up = glm::vec3(0.0f, 1.0f, 0.0f);

float       aspect_ratio = 1.0f;

GLuint      textures[2];

std::vector<glm::vec3> vertices, vertices2;
std::vector<glm::vec2> texcoords, texcoords2;

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640, 640);
  glutCreateWindow("Image Texture Mapping");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
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
  vertices.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
  vertices.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
  vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
  vertices.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));


  // vertices.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
  // vertices.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
  // vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
  // vertices.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));

  // texture coordinates
  texcoords.push_back(glm::vec2(0.0f, 0.0f));
  texcoords.push_back(glm::vec2(1.0f, 0.0f));
  texcoords.push_back(glm::vec2(1.0f, 1.0f));
  texcoords.push_back(glm::vec2(0.0f, 1.0f));


  vertices2.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
  vertices2.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
  vertices2.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
  vertices2.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));

  texcoords2.push_back(glm::vec2(0.0f, 0.0f));
  texcoords2.push_back(glm::vec2(1.0f, 0.0f));
  texcoords2.push_back(glm::vec2(1.0f, 1.0f));
  texcoords2.push_back(glm::vec2(0.0f, 1.0f));

  glGenTextures(2, textures);

  load_texture(&textures[0],"./data/capture.bmp");
  load_texture(&textures[1],"./data/Indian_Cat_pic.jpg");

  glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  program = Shader::create_program("./shader/texture.vert", "./shader/texture.frag");

  loc_a_vertex = glGetAttribLocation(program, "a_vertex");
  loc_a_texcoord = glGetAttribLocation(program, "a_texcoord");

  loc_u_pvm_matrix = glGetUniformLocation(program, "u_pvm_matrix");
  loc_u_texid = glGetUniformLocation(program, "u_texid");
}

void load_texture(GLuint *textureid, const char* filename)
{
  int width, height, channels;
  //GLubyte* image_data;

  // 1. load image data with SOIL library, in which the followings are automatically called
  //  glGenTextures(1, &textureid);
  //  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

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
  //glGenTextures(1, &textureid);
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

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(program);

  glm::mat4   mat_Proj, mat_View, mat_Model;

  mat_View = glm::lookAt(
    vec_eye,			// eye position
    vec_center,		// center position
    vec_up				// up direction 
    );

  mat_Proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.01f, 1000.0f);

  mat_Model = glm::mat4(1.0);

  mat_PVM = mat_Proj*mat_View*mat_Model;

  // 9. let shader know that we will use the texture unit 0

  glUniform1i(loc_u_texid, 0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures[0]);



  

  glUniformMatrix4fv(loc_u_pvm_matrix, 1, false, glm::value_ptr(mat_PVM));

  glVertexAttribPointer(loc_a_vertex, 3, GL_FLOAT, false, 0, vertices.data());
  glVertexAttribPointer(loc_a_texcoord, 2, GL_FLOAT, false, 0, texcoords.data());

  glEnableVertexAttribArray(loc_a_vertex);
  glEnableVertexAttribArray(loc_a_texcoord);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  glDisableVertexAttribArray(loc_a_vertex);
  glDisableVertexAttribArray(loc_a_texcoord);


  //loc_u_texid = glGetUniformLocation(program, "u_texid");
  glUniform1i(loc_u_texid, 1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, textures[1]);


  glVertexAttribPointer(loc_a_vertex, 3, GL_FLOAT, false, 0, vertices2.data());
  glVertexAttribPointer(loc_a_texcoord, 2, GL_FLOAT, false, 0, texcoords2.data());

  glEnableVertexAttribArray(loc_a_vertex);
  glEnableVertexAttribArray(loc_a_texcoord);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  glDisableVertexAttribArray(loc_a_vertex);
  glDisableVertexAttribArray(loc_a_texcoord);





  glUseProgram(0);

  Shader::check_gl_error("draw");

  glutSwapBuffers();
}

void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  aspect_ratio = width / (float)height;
}

void idle()
{
  glutPostRedisplay();
}
