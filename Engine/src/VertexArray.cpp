//
//  VertexArray.cpp
//  Engine
//
//  Created by Callum Cooper Work on 15/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#include "../headers/VertexArray.h"
#include "../headers/VertexBufferLayout.h"
#include "../headers/VertexBuffer.h"
#include "../headers/Renderer.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RenderID));
    GLCall(glBindVertexArray(m_RenderID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RenderID));
}

/* Define the buffer attribute layout so the GPU understands the data it is passed
 * && link the buffer to the vao, index zero VV is a reference to OpenGLs currently
 * bound buffer above ^^.
 */
void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count , element.type,
                                     element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RenderID));
}
    
void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

