#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <cmath>

#include "LiveObj.h"

void LiveObj::draw_live(int loc_a_vertex, int loc_a_normal,
  int loc_u_material_ambient, int loc_u_material_diffuse,
  int loc_u_material_specular, int loc_u_material_shininess, int loc_a_texcoord)
{  

  if(life_flag){
    draw(loc_a_vertex, loc_a_normal,
      loc_u_material_ambient, loc_u_material_diffuse,
      loc_u_material_specular, loc_u_material_shininess, loc_a_texcoord);
  }
}

void LiveObj::load_texture( const char* filename)
{
  int width, height, channels;
  GLubyte* image_data;

  // 1. load image data with SOIL library, in which the followings are automatically called
   glGenTextures(1, &textureid);
   // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    textureid = SOIL_load_OGL_texture
    (
      filename,
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y
      );

    
  if (textureid== 0)
  {
    std::cerr << "Fail to load an image file with SOIL_load_OGL_texture() function." << std::endl;
    return;
  }

  // 2. create a texture object
  // glGenTextures(1, textureid);
  // 3. bind the texture object, so texture operations work for the binded texture object
  glBindTexture(GL_TEXTURE_2D, textureid);
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


void LiveObj::simple_draw(int loc_a_vertex, int loc_a_normal,
  int loc_u_material_ambient, int loc_u_material_diffuse,
  int loc_u_material_specular, int loc_u_material_shininess)
{  
  for (size_t i=0; i<m_groups.size(); ++i)
  {
    Group& group = m_groups[i];



    Material& mtl = m_materials[group.m_mtl_name];
    glm::vec4& ambient  = mtl.m_ambient;
    glm::vec4& diffuse  = mtl.m_diffuse;
    glm::vec4& specular = mtl.m_specular;
    float& shininess    = mtl.m_shininess;

    glm::vec3 a_normal = glm::vec3(0,0,0);

    // TODO: extend the code in below for Phong shading model



    glUniform4fv(loc_u_material_ambient, 1, glm::value_ptr(ambient));

    

    glUniform4fv(loc_u_material_diffuse, 1, glm::value_ptr(diffuse));

    glUniform4fv(loc_u_material_specular, 1, glm::value_ptr(specular));

    glUniform1f(loc_u_material_shininess, shininess);

    glVertexAttribPointer(loc_a_vertex, 3, GL_FLOAT, false, 0, group.m_vertices.data());
    glVertexAttribPointer(loc_a_normal, 3, GL_FLOAT, false, 0, group.m_normals.data());


    glEnableVertexAttribArray(loc_a_vertex);
    glEnableVertexAttribArray(loc_a_normal);
     
    glDrawArrays(GL_TRIANGLES, 0, group.m_vertices.size());

    glDisableVertexAttribArray(loc_a_vertex);
    glDisableVertexAttribArray(loc_a_normal);
  }
}

void LiveObj::gun_draw(int loc_a_vertex, int loc_a_normal, int loc_u_material_diffuse,int loc_a_texcoord)
{  
  for (size_t i=0; i<m_groups.size(); ++i)
  {
    Group& group = m_groups[i];


    Material& mtl = m_materials[group.m_mtl_name];
    glm::vec4& ambient  = mtl.m_ambient;
    glm::vec4& diffuse  = mtl.m_diffuse;
    glm::vec4& specular = mtl.m_specular;
    float& shininess    = mtl.m_shininess;

    glm::vec3 a_normal = glm::vec3(0,0,0);

    // TODO: extend the code in below for Phong shading model




    // glUniform4fv(loc_u_material_ambient, 1, glm::value_ptr(ambient));
    glUniform4fv(loc_u_material_diffuse, 1, glm::value_ptr(diffuse));
    // glUniform1f(loc_u_material_shininess, shininess);

    glVertexAttribPointer(loc_a_vertex, 3, GL_FLOAT, false, 0, group.m_vertices.data());
    glVertexAttribPointer(loc_a_normal, 3, GL_FLOAT, false, 0, group.m_normals.data());
    glVertexAttribPointer(loc_a_texcoord, 2, GL_FLOAT, false, 0, group.m_texcoords.data());




    glEnableVertexAttribArray(loc_a_vertex);
    glEnableVertexAttribArray(loc_a_normal);
    glEnableVertexAttribArray(loc_a_texcoord);
     
    glDrawArrays( GL_TRIANGLES, 0, group.m_vertices.size());


    glDisableVertexAttribArray(loc_a_vertex);
    glDisableVertexAttribArray(loc_a_normal);
    glDisableVertexAttribArray(loc_a_texcoord);



  }
}




void LiveObj::SetLifeFlag()
{
  if(life_flag == true)
  {
    life_flag = false;
    return;
  }
  life_flag = true;
}

bool LiveObj::GetLifeFlag()
{
  return life_flag;
}

bool LiveObj::IsBoundBoxClick(Camera& camera)
{
  //model pos -> world pos
  glm::vec4 min = modelMatrix * glm::vec4(min_x, min_y, min_z, 1.0);
  glm::vec4 max = modelMatrix * glm::vec4(max_x, max_y, max_z, 1.0);
  SwapValue(min, max);

  //Camera front_dir
  float dir_x = camera.front_direction().x ;
  float dir_y = camera.front_direction().y ;
  float dir_z = camera.front_direction().z ;

  //Camera pos  
  float pos_x = camera.position().x;
  float pos_y = camera.position().y;
  float pos_z = camera.position().z;

  for(int i=1;i<60;i++)
  {
    if(min.x-1.5 <= pos_x + dir_x*i && pos_x + dir_x*i <= max.x+1.5)
      if(min.y-1.5 <= pos_y + dir_y*i && pos_y + dir_y*i <= max.y+1.5)
       if(min.z -1.5<= pos_z + dir_z*i && pos_z + dir_z*i <= max.z+1.5)
         return true;
  }
  return false;
}

void LiveObj::SetModelMatrix(glm::mat4 matrix)
{
  modelMatrix =  matrix;
}

glm::mat4 LiveObj::GetModelMatrix(void)
{
  return modelMatrix;
}

float LiveObj::ModifyValue(float num)
{
  while(!(0<=abs(num) && abs(num)<=1))
    num = num/10;

  return num;
}

glm::vec4 LiveObj::GetMaxRange(void)
{
  return glm::vec4(max_x, max_y, max_z, 1.0);
}

glm::vec4 LiveObj::GetMinRange(void)
{
  return glm::vec4(min_x, min_y, min_z, 1.0);
}

void LiveObj::SwapValue(glm::vec4& min, glm::vec4& max)  //Swap value
{
  float temp;
  if(min.x >= max.x)
  {
    temp = min.x;
    min.x = max.x;
    max.x = temp;
  }
  if(min.y >= max.y)
  {
    temp = min.y;
    min.y = max.y;
    max.y = temp;
  }
  if(min.z >= max.z)
  {
    temp = min.z;
    min.z = max.z;
    max.z = temp;
  }
}

bool LiveObj::IsBoundBoxMove(Camera& camera, int flag) // forward : 1 , backward : 2 , left : 3, right : 4
{
  //model pos -> world pos
  glm::vec4 min = modelMatrix * glm::vec4(min_x, min_y, min_z, 1.0);
  glm::vec4 max = modelMatrix * glm::vec4(max_x, max_y, max_z, 1.0);
  SwapValue(min, max);

  glm::vec3 pos = camera.position();
  glm::vec3 front = camera.front_direction();
  glm::vec3 right = camera.right_direction();
  glm::vec3 center = camera.center_position();

  if(flag == 1) //forward
  {
    if(min.x -0.5<= pos.x + front.x && pos.x + front.x <= max.x +0.5)
    {
      if(min.y -0.5<= pos.y + front.y && pos.y + front.y <= max.y +0.5)
      {
        if(min.z -0.5<= pos.z + front.z && pos.z + front.z <= max.z +0.5)
        {
          return true;
        }
      }
    }
  }

  else if(flag ==2)  //backward
  {
    if(min.x -0.5<= pos.x - front.x && pos.x - front.x <= max.x+0.5)
    {
      if(min.y -0.5<= pos.y - front.y && pos.y - front.y <= max.y+0.5)
      {
        if(min.z -0.5<= pos.z - front.z && pos.z - front.z <= max.z+0.5)
          return true;
      }
    }
  }
  else if(flag == 3)  //left
  {
    if(min.x -0.5<= pos.x - right.x && pos.x - right.x <= max.x+0.5)
    {
      if(min.y -0.5<= pos.y - right.y && pos.y - right.y <= max.y+0.5)
      {
        if(min.z -0.5<= pos.z - right.z && pos.z - right.z <= max.z+0.5)
          return true;
      }
    }
  } 
  else  //right
  {
    if(min.x -0.5<= pos.x + right.x && pos.x + right.x <= max.x+0.5)
    {
      if(min.y -0.5<= pos.y + right.y && pos.y + right.y <= max.y+0.5)
      {
        if(min.z -0.5<= pos.z + right.z && pos.z + right.z <= max.z+0.5)
          return true;
      }
    }
  }
  return false;
}

  void LiveObj::SetCenterPos(void)
  {
    centerPos_X = (min_x + max_x)/2;
    centerPos_Y = (min_y + max_y)/2;
    centerPos_Z = (min_z + max_z)/2;
  }

  float LiveObj::ReturnDistance(Camera& camera)
  {
    float distance = sqrt(pow(centerPos_X - camera.position().x, 2) + pow(centerPos_Y - camera.position().y, 2)
      +pow(centerPos_Z - camera.position().z, 2));

    return distance;
  }

GLint LiveObj::GetTextureID(void)
{
  return textureid;
}



 void Fountain::set_velocity()
{
      srand((unsigned int)time(NULL));

      for(int i =0; i<WATER_COUNT; i++){
        float random = ((float)rand()) / (float)RAND_MAX;
        float diff = VX_MAX - VX_MIN;
        float r = random * diff;
        w[i].vx = VX_MIN + r ;

        random = ((float)rand()) / (float)RAND_MAX;
        diff = VY_MAX - VY_MIN;
        r = random * diff;
        w[i].vy =  VY_MIN + r;

        random = ((float)rand()) / (float)RAND_MAX;
        diff = VZ_MAX - VZ_MIN;
        r = random * diff;
        w[i].vz =  VZ_MIN + r;
      }

}


void Fountain::set_location(int loc_a_vertex, int loc_a_normal,
  int loc_u_material_ambient, int loc_u_material_diffuse,
  int loc_u_material_specular, int loc_u_material_shininess)
 {
  loc_s_a_normal = loc_a_normal;
  loc_s_a_vertex = loc_a_vertex;
  loc_s_a_product = loc_u_material_ambient;
  loc_s_s_product = loc_u_material_specular;
  loc_s_shininess = loc_u_material_shininess;
  loc_s_d_product = loc_u_material_diffuse;
 }


float Fountain::x_calculate(int i)
{
  return  ( X_ZERO + (w[i].vx)*(w[i].timer) );
}
float Fountain::y_calculate(int i)
{
  return ( Y_ZERO + (w[i].vy)*(w[i].timer) - (0.5f*GRAVITY*(w[i].timer)*(w[i].timer)) );
}
float Fountain::z_calculate(int i)
{
  return  ( Z_ZERO + (w[i].vz)*(w[i].timer) );
}


void Fountain::DrawFountain(glm::mat4 mat_View, int loc_vm, int loc_nm)
{
  glm::mat4   mat_Model, mat_VM;
  glm::mat3   mat_Normal;

  for(int i=0;i<WATER_COUNT;i++)
  {
    mat_Model = glm::mat4(1.0);
    mat_Model*= glm::translate( glm::vec3(w[i].x_aspect, w[i].y_aspect, w[i].z_aspect) );
    mat_Model *= glm::scale( glm::vec3(0.068,0.068, 0.068) );
    mat_VM   = mat_View*mat_Model;
    mat_Normal = glm::transpose(glm::inverse(glm::mat3(mat_VM)));
    glUniformMatrix4fv(loc_vm, 1, false, glm::value_ptr(mat_VM));
    glUniformMatrix3fv(loc_nm, 1, false, glm::value_ptr(mat_Normal));

     w[i].particle.simple_draw(loc_s_a_vertex, loc_s_a_normal,loc_s_a_product, loc_s_d_product,
    loc_s_s_product, loc_s_shininess);
  }


  for(int i=0;i<WATER_COUNT;i++){
    w[i].x_aspect = x_calculate(i);
    w[i].y_aspect = y_calculate(i);
    w[i].z_aspect = z_calculate(i);
    w[i].timer += INTERVAL;

    if( w[i].y_aspect < Y_ZERO - 3.8) 
      w[i].timer = 0.0f;
  }
}

Fountain::~Fountain()
{
  delete[] w;
}

