#version 150

out vec4 outputColor;
uniform float time;
uniform float fft[100];
void main()
{
 	float windowWidth = 1920.0;
    float windowHeight = 1080.0;
    
    float r = (sin(time*4+fft[0]*2)+1)/2.0;
    //float g = (cos(gl_FragCoord.x +fft[1]*8)+1 )/ 2.0;
    float g=gl_FragCoord.x +fft[1]*8/windowWidth;
    float b = gl_FragCoord.y / windowHeight +fft[2]*2;
    float a = 1.0;
    outputColor = vec4(r, g, b, a);
}