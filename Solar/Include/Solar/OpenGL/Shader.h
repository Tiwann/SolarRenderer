#pragma once
#include <Solar/Config.h>
#include <glm/glm.hpp>

#include <string>

SOLAR_BEGIN
class Shader
{
private:
	std::string mVertSource;
	std::string mFragSource;

	std::string mVertPath;
	std::string mFragPath;

	Handle mVertexHandle;
	Handle mFragHandle;
	Handle mProgramHandle;

	bool mIsCompiled;
	bool mIsLinked;
public:
	Shader(const std::string& vertFile, const std::string& fragFile);
	Shader(const Shader& other);
	Shader(Shader&& other) noexcept;
	~Shader();
	NODISCARD unsigned int GetProgram() const { return mProgramHandle; }
	void PrintSource();
	void Compile();
	void Link();
	void UseProgram() const;
	void Delete() const;

	void SetUniformData1f(const std::string& name, const float& data) const;
	void SetUniformData2f(const std::string& name, const glm::vec2& data) const;
	void SetUniformData3f(const std::string& name, const glm::vec3& data) const;
	void SetUniformData4f(const std::string& name, const glm::vec4& data) const;
				   
	void SetUniformData1i(const std::string& name, const int& data) const;
	void SetUniformData2i(const std::string& name, const glm::ivec2& data) const;
	void SetUniformData3i(const std::string& name, const glm::ivec3& data) const;
	void SetUniformData4i(const std::string& name, const glm::ivec4& data) const;
	void SetUniformDataMat4f(const std::string& name, const glm::mat4& data) const;
	
	NODISCARD unsigned int operator*() const;
	Shader& operator=(const Shader& other) = default;
	Shader& operator=(Shader&& other) noexcept;
	
private:
	static std::string Read(const std::string& file);
};
SOLAR_END

