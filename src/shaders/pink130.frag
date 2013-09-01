#version 130

uniform sampler2D colorIn;

void main()
{
	vec4 colorOut = texture2D(colorIn, gl_TexCoord[0].st);
	colorOut.x = 1.0;
	gl_FragColor = colorOut;
}
