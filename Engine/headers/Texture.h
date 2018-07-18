//
//  Texture.h
//  Engine
//
//  Created by Callum Cooper Work on 18/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include "vendor/stb_image.h"

#include "Renderer.h"

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();
    
    void Bind(unsigned int slot = 0) const;
    void Unbind();
    
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP; /* <- Bits per pixel of the texture */
    
};

#endif /* Texture_h */
