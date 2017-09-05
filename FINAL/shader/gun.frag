uniform vec4 l_position;
// uniform vec4 a_product;
uniform vec4 d_product;
// uniform vec4 s_product;
// uniform float shininess;


uniform sampler2D u_texid;

varying vec3 pos;
varying vec3 v_normal;
varying vec2 v_texcoord;



void main() {


	vec3 lightPos = (l_position).xyz;

	vec3 N = normalize(v_normal);
  	vec3 L = normalize(lightPos - pos);


  	float Kd = max( dot(L, N), 0.0 );
  	vec4 diffuse = Kd * d_product;
  	diffuse.a = 1.0;

	
	
	gl_FragColor =  texture2D(u_texid, v_texcoord) + diffuse;
}