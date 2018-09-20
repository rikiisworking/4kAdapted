#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
uniform vec4 colorL;
uniform vec4 colorR;

void main(){
	gl_Position = modelViewProjectionMatrix * position;
}
