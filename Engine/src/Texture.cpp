//
//  Texture.cpp
//  Engine
//
//  Created by Callum Cooper Work on 18/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#include "../headers/Texture.h"

Texture::Texture(const std::string &path)
    : m_RendererID(0), m_FilePath(path),
      m_LocalBuffer(nullptr), m_Width(0),
      m_Height(0), m_BPP(0)
{
    /* Call vendor stb_image code - ensure that the texture is flipped vertically,
     * so that it adheres to OpenGL bottom left texture coords scanning standard.
     */
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    
    /* Note to self - in C++ when function is declared as pointer (you should pass by reference like this.) */
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0,
                        GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    
    /* Unbind our textures */
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    
    /* And free our texture date from the GPU */
    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
