#include "Shader.hpp"
#include <glad/glad.h>
#include <Logger.hpp>

namespace RNR::Rendering {
  Shader::Shader() {
    program = glCreateProgram();
  }

  void Shader::link() {
    for(auto shader : shaders)
      glAttachShader(program, shader);
    glLinkProgram(program);

    DEV_LOGMSGF("linked program with %i shaders", shaders.size());
    for(auto shader : shaders)
      glDeleteShader(shader);
    shaders.clear();
  }

  void Shader::addShader(const char* code, unsigned int type) {

  }
}