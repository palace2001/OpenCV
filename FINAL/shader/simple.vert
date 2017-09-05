uniform mat4 modelview_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix;


attribute vec3 a_normal;
attribute vec4 a_vertex;


varying vec3 pos;
varying vec3 v_normal;


void main() {
	
  	
  	pos =(modelview_matrix * a_vertex).xyz;	
    	v_normal= normalize( normal_matrix * a_normal );


  	
	gl_Position = projection_matrix * modelview_matrix * a_vertex;
}