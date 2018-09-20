#version 150

out vec4 outputColor;
uniform int currentColor;
uniform float lifeTime=255;
void main()
{
	vec2 resolution = vec2(1920.0,1080.0);
	vec2 st = gl_FragCoord.xy/resolution.xy;
	vec3 color1,color2;

    if(currentColor == 0){
    	color1=vec3(0,0.921,0.705);
    	color2=vec3(0,0.313,1.0);
    }else{
    	color1=vec3(0.901,0.058,0.058);
    	color2=vec3(1.0,1.0,0.0);
    }

    float mixValue = distance(st,vec2(0,1));
   	vec3 color = mix(color1,color2,mixValue);


    outputColor = vec4(color,lifeTime);
   
}