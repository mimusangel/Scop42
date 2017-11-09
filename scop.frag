#version 330 core

out vec3 color;

uniform float tMode;

in vec3 vColor;

void main(){
  color = vColor * (1.0 - tMode) + vec3(1.0, 0.0, 0.0) * tMode;
}
