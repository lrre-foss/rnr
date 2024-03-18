#pragma once
#include <vector>

namespace RNR::Rendering {
  class Shader {
    unsigned int program;
    std::vector<unsigned int> shaders;
  public:
    Shader();

    void addShader(const char* code, unsigned int type);
    void link();

    unsigned int getProgram() { return program; };
  };
}