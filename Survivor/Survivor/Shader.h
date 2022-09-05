#pragma once
#include <GL/glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();

	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
	void SetVector3Uniform(const char* name, const Vector3& vector);
	void SetIntUniform(const char* name, const int integer);
	void SetFloatUniform(const char* name, const float f);

private:
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShaderID);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram();

	GLuint mShaderProgramID;
	GLuint mVertShaderID;
	GLuint mFragShaderID;
};

