#include "shader.h"
#include <GL/glext.h>
#include <iostream>
#include "auxil.h"
void shader::init(string filename)
{
	string shader (aux::textFileRead(filename));
	const char *title = shader.c_str();
	std::cout << shader;
	
	char log[1024];
	int len, compiled;
	glShaderSource(x, 1, &title, NULL);
	glCompileShader(x);
	glGetShaderiv(x, GL_COMPILE_STATUS, &compiled);
	if(!compiled){
		glGetShaderInfoLog(x, sizeof(log), &len, log);
		std::cout << log << '\n';
	}
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
}
