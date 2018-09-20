#version 150

const int number_of_targets = 400;

out vec4 outputColor;
uniform float time;
uniform vec2 resolution;
uniform vec4 targets[number_of_targets];
uniform vec4 colors[number_of_targets];
uniform vec3 color2;
void main() {

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
  vec3 color = vec3(gl_FragCoord.y/resolution.y*0.17,gl_FragCoord.y/resolution.y*0.17,gl_FragCoord.y/resolution.y*0.17);

  float mixValue = distance(p,vec2(0.0,0.5))/1.75;
  for(int i = 0; i < number_of_targets; i++){
    vec2 t = vec2(targets[i].x, -targets[i].y) / min(resolution.x, resolution.y) * 2.0;
    t.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);
    vec3 color1 = colors[i].xyz; 
    vec3 final = mix(color1,color2,mixValue);
    if(length(p-t)<0.025){
   		vec4 myColor=vec4(final.xyz,1.0);
   		color=myColor.xyz;
    }
    
  }

  outputColor = vec4(color, 1.0);
}

    /*
	float r = 0.0195 / length(p - t) * colors[i].x;
    float g = 0.0195 / length(p - t) * colors[i].y;
    float b = 0.0195 / length(p - t) * colors[i].z;
   
    vec3 c = vec3(smoothstep(0.19, 1.0, r), smoothstep(0.19, 1.0, g), smoothstep(0.19, 1.0, b));
    
    color +=c;
    if(color.r==1.0&&color.g==1.0&&color.b==1.0){
    color = colors[i].xyz;
    }
    */