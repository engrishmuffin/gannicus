out vec4 colorOut;
in vec4 gl_FragCoord;
 
void main()
{
	gl_FragCoord = vec4(1.0, 1.0, 1.0, 1.0);
	colorOut = vec4(1.0, 0.5, 0.5, 1.0);
}
