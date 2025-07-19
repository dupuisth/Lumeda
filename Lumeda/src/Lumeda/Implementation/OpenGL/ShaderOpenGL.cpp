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
		std::string vertexCode = FileReader::ReadFile(vertexPath);
		const char* vertexSource = vertexCode.c_str();
		glShaderSource(vertexShader, 1, &vertexSource, nullptr);
		glCompileShader(vertexShader);

		std::string fragmentCode = FileReader::ReadFile(fragmentPath);
		const char* fragmentSource = fragmentCode.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShader);

		glAttachShader(m_Handle, vertexShader);
		glAttachShader(m_Handle, fragmentShader);
		glLinkProgram(m_Handle);

		// Check the linking status
		int success;
		glGetProgramiv(m_Handle, GL_LINK_STATUS, &success);
		if (success != GL_TRUE)
		{
			char infoLog[InfoLogSize];
			glGetProgramInfoLog(m_Handle, InfoLogSize, nullptr, infoLog);
			LUMEDA_CORE_ERROR("Failed to link program ", infoLog);
			throw std::runtime_error("Failed to link program");
		}
	}
	catch (std::exception& e)
	{
		LUMEDA_CORE_ERROR("Failed to create shader", e.what());
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
