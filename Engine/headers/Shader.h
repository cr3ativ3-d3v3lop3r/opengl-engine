//
//  Shader.h
//  Engine
//
//  Created by Callum Cooper Work on 16/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "../headers/Renderer.h"

/* Struct allows us to return multiple types in ParseShader function */
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();
    
    void Bind() const;
    void Unbind() const;
    
    /* Set uniforms */
    void SetUniform1i(const std::string& name, int v0);
    
    void SetUniform1f(const std::string& name, float v0);
    void SetUniform2f(const std::string& name, float v0, float v1);
    void SetUniform3f(const std::string& name, float v0, float v1, float v2);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    int GetUniformLocation(const std::string& name);
    
    /* Caching for uniforms */
    std::unordered_map<std::string, int> m_UniformLocationCache;
};

#endif /* Shader_h */
