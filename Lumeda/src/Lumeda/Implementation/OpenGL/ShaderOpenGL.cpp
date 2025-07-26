#include <Lumeda/Implementation/OpenGL/ShaderOpenGL.h>

#include <Lumeda/Utils/FileReader.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Lumeda;

const int InfoLogSize = 512;

ShaderOpenGL::ShaderOpenGL(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) : m_Name(name)
{
	LUMEDA_PROFILE;
	m_Handle = glCreateProgram();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	try
	{
		// Used for all compilation/linking status checks
		int success;

		// Compile the vertex shader
		std::string vertexCode = FileReader::ReadFile(vertexPath);
		const char* vertexSource = vertexCode.c_str();
		glShaderSource(vertexShader, 1, &vertexSource, nullptr);
		glCompileShader(vertexShader);
		// Check compilation
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) 
		{
			char infoLog[InfoLogSize];
			glGetShaderInfoLog(vertexShader, InfoLogSize, nullptr, infoLog);
			LUMEDA_CORE_ERROR("Vertex shader compilation, failed: {0}", infoLog);
			throw std::runtime_error("Vertex shader compilation failed");
		}

		// Compile the fragment shader
		std::string fragmentCode = FileReader::ReadFile(fragmentPath);
		const char* fragmentSource = fragmentCode.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShader);
		// Check compilation
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[InfoLogSize];
			glGetShaderInfoLog(fragmentShader, InfoLogSize, nullptr, infoLog);
			LUMEDA_CORE_ERROR("Fragment shader compilation, failed: {0}", infoLog);
			throw std::runtime_error("Fragment shader compilation failed");
		}

		// Attach the shaders then link the program
		glAttachShader(m_Handle, vertexShader);
		glAttachShader(m_Handle, fragmentShader);
		glLinkProgram(m_Handle);

		// Check the linking status
		success;
		glGetProgramiv(m_Handle, GL_LINK_STATUS, &success);
		if (success != GL_TRUE)
		{
			char infoLog[InfoLogSize];
			glGetProgramInfoLog(m_Handle, InfoLogSize, nullptr, infoLog);
			LUMEDA_CORE_ERROR("Failed to link program ", infoLog);
			throw std::runtime_error("Failed to link program");
		}

		// The shaders are linked to the program, they can now be deleted
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	catch (std::exception& e)
	{
		LUMEDA_CORE_ERROR("Failed to create shader", e.what());

		// If an exception is thrown, then the shaders are not cleaned up
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		throw e;
	}
}

ShaderOpenGL::~ShaderOpenGL()
{
	LUMEDA_PROFILE;
	glDeleteShader(m_Handle);
}

void ShaderOpenGL::Bind()
{
	LUMEDA_PROFILE;
	glUseProgram(m_Handle);
}

void ShaderOpenGL::UnBind()
{
	LUMEDA_PROFILE;
	glUseProgram(0);
}

void ShaderOpenGL::Prepare(float time, const glm::vec3& cameraPosition, const glm::vec3& cameraForward, const glm::mat4 cameraMatrix)
{
	LUMEDA_PROFILE;
	SetUniform("u_Time", time);
	SetUniform("u_CameraPosition", cameraPosition);
	SetUniform("u_CameraForward", cameraForward);
	SetUniform("u_CameraMatrix", cameraMatrix);
}

void ShaderOpenGL::SetUniform(const std::string& uniform, int value)
{
	LUMEDA_PROFILE;
	glUniform1i(glGetUniformLocation(m_Handle, uniform.c_str()), value);
}

void ShaderOpenGL::SetUniform(const std::string& uniform, float value)
{
	LUMEDA_PROFILE;
	glUniform1f(glGetUniformLocation(m_Handle, uniform.c_str()), value);
}

void ShaderOpenGL::SetUniform(const std::string& uniform, const glm::vec2& value)
{
	LUMEDA_PROFILE;
	glUniform2fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, glm::value_ptr(value));
}

void ShaderOpenGL::SetUniform(const std::string& uniform, const glm::vec3& value)
{
	LUMEDA_PROFILE;
	glUniform3fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, glm::value_ptr(value));
}

void ShaderOpenGL::SetUniform(const std::string& uniform, const glm::vec4& value)
{
	LUMEDA_PROFILE;
	glUniform4fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, glm::value_ptr(value));
}

void ShaderOpenGL::SetUniform(const std::string& uniform, const glm::mat2& value)
{
	LUMEDA_PROFILE;
	glUniformMatrix2fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, false, glm::value_ptr(value));
}

void ShaderOpenGL::SetUniform(const std::string& uniform, const glm::mat3& value)
{
	LUMEDA_PROFILE;
	glUniformMatrix3fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, false, glm::value_ptr(value));
}

void ShaderOpenGL::SetUniform(const std::string& uniform, const glm::mat4& value)
{
	LUMEDA_PROFILE;
	glUniformMatrix4fv(glGetUniformLocation(m_Handle, uniform.c_str()), 1, false, glm::value_ptr(value));
}
