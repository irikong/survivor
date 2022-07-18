#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();

	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	void SetActive();

private:
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShaderID);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram();

	GLuint mShaderProgramID;
	GLuint mVertShaderID;
	GLuint mFragShaderID;
};

