#include "OpenGL/Shader.h"
#include <Core/Log.h>
#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

SOLAR_BEGIN
Shader::Shader(const std::string& vertFile, const std::string& fragFile)
	: mVertSource(std::string()), mFragSource(std::string()), mVertPath(std::string()), mFragPath(std::string()), 
	mVertexHandle(0), mFragHandle(0), mProgramHandle(0), mIsCompiled(false), mIsLinked(false)
{
	//vertPath = vertFile;
	//fragPath = fragFile;

	mVertSource = Read(vertFile);
	mFragSource = Read(fragFile);

	mVertexHandle = glCreateShader(GL_VERTEX_SHADER);
	mFragHandle = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vs = mVertSource.c_str();
	const char* fs = mFragSource.c_str();

	glShaderSource(mVertexHandle, 1, &vs, nullptr);
	glShaderSource(mFragHandle, 1, &fs, nullptr);

	mProgramHandle = glCreateProgram();
	glAttachShader(mProgramHandle, mVertexHandle);
	glAttachShader(mProgramHandle, mFragHandle);
}

Shader::Shader(const Shader& other)
{
	mVertSource = other.mVertSource;
	mFragSource = other.mFragSource;
	mVertPath = other.mVertPath;
	mFragPath = other.mFragPath;
	mVertexHandle = other.mVertexHandle;
	mFragHandle = other.mFragHandle;
	mProgramHandle = other.mProgramHandle;
	mIsCompiled = other.mIsCompiled;
	mIsLinked = other.mIsLinked;
}

Shader::Shader(Shader&& other) noexcept
{
	mVertSource	= other.mVertSource;
	mFragSource	= other.mFragSource;
	mVertPath	= other.mVertPath;
	mFragPath	= other.mFragPath;
	mVertexHandle		= other.mVertexHandle;
	mFragHandle		= other.mFragHandle;
	mProgramHandle	= other.mProgramHandle;
	mIsCompiled	= other.mIsCompiled;
	mIsLinked	= other.mIsLinked;
	
	other.mVertSource	= std::string();
	other.mFragSource	= std::string();
	other.mVertPath		= std::string();
	other.mFragPath		= std::string();
	other.mVertexHandle		= 0;
	other.mFragHandle		= 0;
	other.mProgramHandle		= 0;
	other.mIsCompiled	= false;
	other.mIsLinked		= false;
}

Shader::~Shader()
{
	Delete();
}

void Shader::Compile()
{
	if (mVertSource.empty() || mFragSource.empty())
	{
		mIsCompiled = false;
		return;
	}

	int compiled;

	// Compile Vertex
	glCompileShader(mVertexHandle);
	glGetShaderiv(mVertexHandle, GL_COMPILE_STATUS, &compiled);

	if (compiled == GL_TRUE)
	{
		SOLAR_LOG_INFO("[SHADER] Successfully compiled vertex shader!");
	}
	else
	{
		SOLAR_LOG_ERROR("[SHADER] Failed to compile vertex shader!");
		mIsCompiled = false;
		int length = 0;
		char message[1024];
		glGetShaderInfoLog(mVertexHandle, 1024, &length, message);
		SOLAR_LOG_ERROR(message);
	}

	// Compile Fragment
	glCompileShader(mFragHandle);
	glGetShaderiv(mFragHandle, GL_COMPILE_STATUS, &compiled);

	if (compiled == GL_TRUE)
	{
		SOLAR_LOG_INFO("[SHADER] Successfully compiled fragment shader!");
	}
	else
	{
		SOLAR_LOG_ERROR("[SHADER] Failed to compile fragment shader!");
		mIsCompiled = false;
		int length = 0;
		char message[1024];
		glGetShaderInfoLog(mFragHandle, 1024, &length, message);
		SOLAR_LOG_ERROR(message);
	}
	mIsCompiled = true;
}

void Shader::Link()
{
	if (!mIsCompiled) {
		SOLAR_LOG_ERROR("[SHADER] Cannot link shaders, compilation failed.");
		return;
	}

	glLinkProgram(mProgramHandle);
	int linked;
	glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &linked);

	if (linked == GL_TRUE)
	{
		SOLAR_LOG_INFO("[SHADER] Shader program successfully linked!");
		mIsLinked = true;
	}
	else
	{
		SOLAR_LOG_ERROR("[SHADER] Failed to link shader program!");
		mIsLinked = false;
		int length = 0;
		char message[1024];
		glGetProgramInfoLog(mProgramHandle, 1024, &length, message);
		SOLAR_LOG_ERROR(message);
	}
}

void Shader::UseProgram() const
{
	if (!mIsLinked)
	{
		SOLAR_LOG_ERROR("[SHADER] An error occured, cannot use this shader.");
		SOLAR_ASSERT(Shader::mIsLinked, "[SHADER] An error occured, cannot use this shader.");
	}
	glUseProgram(mProgramHandle);
}

void Shader::PrintSource()
{
	std::cout << mVertSource;
	std::cout << mFragSource;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	mVertSource	= other.mVertSource;
	mFragSource	= other.mFragSource;
	mVertPath	= other.mVertPath;
	mFragPath	= other.mFragPath;
	mVertexHandle		= other.mVertexHandle;
	mFragHandle		= other.mFragHandle;
	mProgramHandle	= other.mProgramHandle;
	mIsCompiled	= other.mIsCompiled;
	mIsLinked	= other.mIsLinked;
	
	other.mVertSource	= std::string();
	other.mFragSource	= std::string();
	other.mVertPath		= std::string();
	other.mFragPath		= std::string();
	other.mVertexHandle		= 0;
	other.mFragHandle		= 0;
	other.mProgramHandle		= 0;
	other.mIsCompiled	= false;
	other.mIsLinked		= false;
	return *this;
}

std::string Shader::Read(const std::string& file)
{
	std::ifstream stream(file.c_str(), std::ios::in);

	if (!stream.is_open()) {
		SOLAR_LOG_ERROR("[SHADER] Fail to read shader file {}", file);
		stream.close();
		return "";
	}

	SOLAR_LOG_TRACE("[SHADER] Reading file {}", file);
	std::stringstream ss;
	ss << stream.rdbuf();
	stream.close();
	return ss.str();
}

void Shader::Delete() const
{
	glDeleteShader(mVertexHandle);
	glDeleteShader(mFragHandle);
}

void Shader::SetUniformData1f(const std::string& name, const float& data) const
{
	const int location = glGetUniformLocation(mProgramHandle, name.c_str());
	glUniform1fv(location, 1, &data);
}

void Shader::SetUniformData2f(const std::string& name, const glm::vec2& data) const
{
	const int location = glGetUniformLocation(mProgramHandle, name.c_str());
	glUniform2fv(location, 1, glm::value_ptr(data));
}

void Shader::SetUniformData3f(const std::string& name, const glm::vec3& data) const
{
	const int location = glGetUniformLocation(mProgramHandle, name.c_str());
	glUniform3fv(location, 1, glm::value_ptr(data));
}

void Shader::SetUniformData4f(const std::string& name, const glm::vec4& data) const
{
	const int location = glGetUniformLocation(mProgramHandle, name.c_str());
	glUniform4fv(location, 1, glm::value_ptr(data));
}

void Shader::SetUniformData1i(const std::string& name, const int& data) const
{
	const int location = glGetUniformLocation(mProgramHandle, name.c_str());
	glUniform1iv(location, 1, &data);
}
void Shader::SetUniformData2i(const std::string& name, const glm::ivec2& data) const
{
	const int location = glGetUniformLocation(mProgramHandle, name.c_str());
	glUniform2iv(location, 1, glm::value_ptr(data));
}
void Shader::SetUniformData3i(const std::string& name, const glm::ivec3& data) const
{
	const int location = glGetUniformLocation(mProgramHandle, name.c_str());
	glUniform3iv(location, 1, glm::value_ptr(data));
}
void Shader::SetUniformData4i(const std::string& name, const glm::ivec4& data) const
{
	const int location = glGetUniformLocation(mProgramHandle, name.c_str());
	glUniform4iv(location, 1, glm::value_ptr(data));
}

void Shader::SetUniformDataMat4f(const std::string& name, const glm::mat4& data) const
{
	const int location = glGetUniformLocation(mProgramHandle, name.c_str());
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(data));
}

unsigned int Shader::operator*() const
{
	return mProgramHandle;
}
SOLAR_END
