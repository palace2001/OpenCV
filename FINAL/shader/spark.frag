#version 120

uniform sampler2D u_texid;

varying vec2 v_texcoord;

void main() {
  gl_FragColor = texture2D(u_texid, v_texcoord);  
}
