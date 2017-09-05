uniform mat4 modelview_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix;


attribute vec2 a_texcoord;
attribute vec3 a_normal;
attribute vec4 a_vertex;


varying vec3 pos;
varying vec3 v_normal;
varying vec2 v_texcoord;



void main() {
	
  	
  	pos =(modelview_matrix * a_vertex).xyz;	
  	v_normal= normalize( normal_matrix * a_normal );

  	v_texcoord = a_texcoord;

	gl_Position = projection_matrix * modelview_matrix * a_vertex;
}