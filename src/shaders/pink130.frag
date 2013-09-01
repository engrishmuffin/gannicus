#version 130

uniform sampler2D colorIn;

void main()
{
	vec4 colorOut = vec4(1.0, 0.5, 0.5, 0.4) + texture2D(colorIn, gl_TexCoord[0].st);
	gl_FragColor = colorOut;
}
