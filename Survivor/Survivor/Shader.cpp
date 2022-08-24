#include "Shader.h"
#include <fstream>
#include <sstream>
#include <SDL/SDL_log.h>

Shader::Shader() :
	mShaderProgramID(0),
	mVertShaderID(0),
	mFragShaderID(0)
{

}

Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertShaderID) ||
		!CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShaderID)) {
		return false;
	}

	mShaderProgramID = glCreateProgram();
	glAttachShader(mShaderProgramID, mVertShaderID);
	glAttachShader(mShaderProgramID, mFragShaderID);
	glLinkProgram(mShaderProgramID);

	return IsValidProgram();
}

void Shader::Unload()
{
	glDeleteProgram(mShaderProgramID);
	glDeleteShader(mVertShaderID);
	glDeleteShader(mFragShaderID);
}

void Shader::SetActive()
{
	glUseProgram(mShaderProgramID);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	GLuint location = glGetUniformLocation(mShaderProgramID, name); // TODO: location 캐싱
	glUniformMatrix4fv(location, 1, GL_TRUE, matrix.GetAsFloatPtr()); // location, count, transpose(행 벡터이면 true), *value
}

void Shader::SetVector3Uniform(const char* name, const float vector[3])
{
	GLuint location = glGetUniformLocation(mShaderProgramID, name);
	glUniform3fv(location, 1, vector);
}

void Shader::SetIntUniform(const char* name, const int integer)
{
	GLuint location = glGetUniformLocation(mShaderProgramID, name);
	glUniform1i(location, integer);
}

void Shader::SetFloatUniform(const char* name, const float f)
{
	GLuint location = glGetUniformLocation(mShaderProgramID, name);
	glUniform1f(location, f);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShaderID)
{
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open()) {
		std::stringstream SS;
		SS << shaderFile.rdbuf();
		std::string source = SS.str();
		const char* sourceChar = source.c_str();

		outShaderID = glCreateShader(shaderType);
		glShaderSource(outShaderID, 1, &(sourceChar), nullptr); // shader, count, string, length
		glCompileShader(outShaderID);

		if (!IsCompiled(outShaderID)) {
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else {
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shaderID)
{
	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shaderID, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}

	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;
	glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgramID, 511, nullptr, buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}

	return true;
}
