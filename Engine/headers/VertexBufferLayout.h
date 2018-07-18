//
//  VertexBufferLayout.h
//  Engine
//
//  Created by Callum Cooper Work on 15/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#ifndef VertexBufferLayout_h
#define VertexBufferLayout_h

#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "../headers/Renderer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    
    static unsigned int getSizeOfType(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
        }
        ASSERT(false);
        return 0;
    }
};

enum class VALUETYPE
{
    FLOAT = 0,
    UNSIGNED_INT = 1,
    UNSIGNED_CHAR = 2
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
    : m_Stride(0) {};
    
    void push(unsigned int count, VALUETYPE value)
    { 
        switch(value)
        {
            case VALUETYPE::FLOAT:
                m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
                m_Stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
                break;
            case VALUETYPE::UNSIGNED_INT:
                m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
                m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
                break;
            case VALUETYPE::UNSIGNED_CHAR:
                m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
                m_Stride +=VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
                break;
        }
    }
    
    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
    
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride = 0;
};

#endif /* VertexBufferLayout_h */
