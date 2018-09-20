#version 150

out vec4 outputColor;
uniform vec4 color;
uniform float headX;
uniform int currentColor;
uniform float amp[100];
uniform float time;

void main()
{
 	float windowWidth = 1520.0;
    float windowHeight = 980.0;
    float r,g,b,a;
    if(currentColor == 0){//purple
	    //r = gl_FragCoord.x / windowWidth +headX/8;
	    r = (sin(time*2+amp[1]*40)+1)/2.0;
	    g = gl_FragCoord.y / windowHeight -headX/8;
	    b = 0.8;
	    a = 1.0;
    }else if(currentColor == 1){//red
    	r = 0.8;
	    //g = gl_FragCoord.y / windowHeight;
	    g = (sin(time*2+amp[2]*50)+1)/2.0;
	    b = gl_FragCoord.x / windowWidth-headX/8;;
	    a = 1.0;
    }else if(currentColor == 2){//green
    	r = gl_FragCoord.x / windowWidth-headX/8;
	    g = 0.8;
	    //b = gl_FragCoord.y / windowHeight;
	    b = (sin(time*2+amp[3]*60)+1)/2.0;
	    a = 1.0;
    }

   	

    outputColor = vec4(r, g, b, a);
   
}