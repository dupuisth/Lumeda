#include <Lumeda/Implementation/OpenGL/ShaderOpenGL.h>

#include <Lumeda/Utils/FileReader.h>

#include <glad/glad.h>

using namespace Lumeda;

const int InfoLogSize = 512;

ShaderOpenGL::ShaderOpenGL(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) : m_Name(name)
{
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
			LUMEDA_CORE_ERROR("Vertex shader compilatop, failed: {0}", infoLog);
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
			LUMEDA_CORE_ERROR("Fragment shader compilatop, failed: {0}", infoLog);
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
	glDeleteShader(m_Handle);
}

void ShaderOpenGL::Bind()
{
	glUseProgram(m_Handle);
}

void ShaderOpenGL::UnBind()
{
	glUseProgram(0);
}

void ShaderOpenGL::SetFloat(const std::string& uniform, float value)
{
	glUniform1f(glGetUniformLocation(m_Handle, uniform.c_str()), value);
}

void ShaderOpenGL::SetInt(const std::string& uniform, int value)
{
	glUniform1i(glGetUniformLocation(m_Handle, uniform.c_str()), value);

}
