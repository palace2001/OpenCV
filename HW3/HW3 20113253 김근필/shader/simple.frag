uniform vec4 l_position;
uniform float shininess;
uniform vec4 a_product;
uniform vec4 d_product;
uniform vec4 s_product; 



varying vec3 pos;
varying vec3 v_normal;

void main() {



	vec3 lightPos = (l_position).xyz;

	vec3 N = normalize(v_normal);
  	vec3 L = normalize(lightPos - pos);
  	vec3 V = normalize( - pos );
  	vec3 R = reflect(-L, N);
  	

  	vec4 ambient = a_product;

  	float Kd = max( dot(L, N), 0.0 );
  	vec4 diffuse = Kd * d_product;

  	float Ks = pow( max(dot(R, V),0.0), shininess );
  	vec4 specular = Ks * s_product;


  
  	// if(dot(L,	N) <	0.0)	
  	// 	specular = vec4(0.0,0.0,0.0,1.0);

	vec4 v_color =  ambient + diffuse + specular ;   
	v_color.a = 1.0;
	
	gl_FragColor =  v_color;
}