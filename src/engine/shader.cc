#include "shader.h"
#include <GL/glext.h>
#include <iostream>
#include "auxil.h"
void shader::init(string filename)
{
	const char *title = aux::textFileRead(filename).c_str();
	glShaderSource(x, 1, &title, NULL);
	glCompileShader(x);
}

vertShader::vertShader(string filename)
{
	x = glCreateShader(GL_VERTEX_SHADER);
	init(filename);
}

geoShader::geoShader(string filename)
{
	x = glCreateShader(GL_GEOMETRY_SHADER);
	init(filename);
}

fragShader::fragShader(string filename)
{
	x = glCreateShader(GL_FRAGMENT_SHADER);
	init(filename);
	GLint compiled;
	while(!compiled) glGetShaderiv(x, GL_COMPILE_STATUS, &compiled);
}
