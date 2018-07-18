//
//  VertexBuffer.h
//  Engine
//
//  Created by Callum Cooper Work on 15/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#ifndef VertexBuffer_h
#define VertexBuffer_h

#include "Renderer.h"

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    
    void Bind() const;
    void Unbind() const;
    
private:
    unsigned int m_RendererID;
};

#endif /* VertexBuffer_h */
