#include "shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace rendering;

Shader::Shader(const char* vertFilePath, const char* fragFilePath)
{
    //read shader files
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        
        vShaderFile.open(vertFilePath);
        fShaderFile.open(fragFilePath);
        
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
        printf("%s\n", e.what());
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    uint32_t vertexID, fragmentID;
    int32_t success;
    char infoLog[512];

    //vertex shader
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vShaderCode, NULL);
    glCompileShader(vertexID);

    //check for errors
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    //fragment shader
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fShaderCode, NULL);
    glCompileShader(fragmentID);

    //check for errors
    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    //create shader program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertexID);
    glAttachShader(m_id, fragmentID);
    glLinkProgram(m_id);
    
    //check for linking errors
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

}

void Shader::Bind()
{
    // Bind the shader program
    glUseProgram(m_id);
}

void Shader::Unbind() {
    //unbind the shader program
    glUseProgram(0);
}

template<>
void Shader::setUniform(const char* name, float value) const
{
    int location = glGetUniformLocation(m_id, name);
    glProgramUniform1f(m_id, location, value);
}

template<>
void Shader::setUniform(const char* name, int value) const {
    int location = glGetUniformLocation(m_id, name);
    glProgramUniform1i(m_id, location, value);
}

template<>
void Shader::setUniform(const char* name, glm::vec3 value) const {
    int location = glGetUniformLocation(m_id, name);
    glProgramUniform3fv(m_id, location, 1, glm::value_ptr(value));
}

template<>
void Shader::setUniform(const char* name, glm::mat3 value) const {
    int location = glGetUniformLocation(m_id, name);
    glProgramUniformMatrix3fv(m_id, location, 1, GL_FALSE, glm::value_ptr(value));
}

template<>
void Shader::setUniform(const char* name, glm::mat4 value) const{
    int location = glGetUniformLocation(m_id, name);
    glProgramUniformMatrix4fv(m_id, location, 1, GL_FALSE, glm::value_ptr(value));
}
