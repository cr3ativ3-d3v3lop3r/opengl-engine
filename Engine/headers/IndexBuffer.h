//
//  IndexBuffer.h
//  Engine
//
//  Created by Callum Cooper Work on 15/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#ifndef IndexBuffer_h
#define IndexBuffer_h

#include "Renderer.h"

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();
    
    void Bind() const;
    void Unbind() const;
    
    inline unsigned int GetCount() const { return m_count; }
    
private:
    unsigned int m_RendererID;
    unsigned int m_count;
};

#endif /* IndexBuffer_h */
