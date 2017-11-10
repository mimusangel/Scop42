#version 330 core

out vec4 color;

uniform float tMode;
uniform sampler2D uTexture;
uniform int disableTexture;

in vec3 vColor;
in vec2 vTex;

void main(){
	if (disableTexture == 1)
	{
		color = vec4(vColor * (1.0 - tMode) + vec3(1.0, 0.0, 0.0) * tMode, 1.0);
	}
	else
	{
		vec4 texColor = texture(uTexture, vTex);
  		color = vec4(vColor * (1.0 - tMode) + texColor.rgb * tMode, 1.0);
	}
}
