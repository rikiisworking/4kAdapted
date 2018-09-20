#version 150
 
const int number_of_targets = 120;
 
out vec4 outputColor;
uniform float time;
uniform float amps[number_of_targets];
uniform vec2 resolution;
uniform vec4 targets[number_of_targets];
uniform vec4 colors[number_of_targets];
uniform float lives[number_of_targets];
uniform float sizes[number_of_targets];
uniform vec3 color2;
void main() {

	
	vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
	vec4 color = vec4(gl_FragCoord.y/resolution.y*0.17,gl_FragCoord.y/resolution.y*0.17,gl_FragCoord.y/resolution.y*0.17,1.0);
	float mixValue = distance(p,vec2(0.0,0.75))/1.75;
	for(int i = 0; i < number_of_targets; i++){
		vec2 t = vec2(targets[i].x, -targets[i].y) / min(resolution.x, resolution.y) * 2.0;
	    t.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);
	    vec3 color1 = colors[i].xyz;    
	    vec3 final = mix(color1,color2,mixValue);
			if(length(p-t)<sizes[i]/500+amps[i%3]/75){
				vec4 myColor=vec4(final.xyz,1.0);
				color = color * (1.0-lives[i]/400.0f) + myColor * lives[i]/400.0f;
			}
			
 	}
 
  outputColor = color;
}