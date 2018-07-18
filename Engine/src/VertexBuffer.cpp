//
//  VertexBuffer.cpp
//  Engine
//
//  Created by Callum Cooper Work on 15/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#include <stdio.h>

#include "../headers/VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    /* Setup the buffer and bind the buffer */
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
