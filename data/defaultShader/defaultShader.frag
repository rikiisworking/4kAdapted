#version 150

out vec4 outputColor;
uniform float time;
uniform float sound;
uniform vec4 inputColor1;
uniform vec4 inputColor2;

void main()
{
	vec3 color1 = inputColor1.xyz;
	vec3 color2 = inputColor2.xyz;

	vec2 resolution = vec2(1920.0,1080.0);
	vec2 st = gl_FragCoord.xy/resolution.xy;

 	float mixValue = distance(st,vec2(1.0,1.0));

   	vec3 color = mix(color1,color2,mixValue);
   // outputColor = vec4(color,mixValue+0.02);
   outputColor = vec4(color,1.0);
}

