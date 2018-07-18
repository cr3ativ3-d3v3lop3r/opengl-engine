//
//  VertexArray.h
//  Engine
//
//  Created by Callum Cooper Work on 15/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#ifndef VertexArray_h
#define VertexArray_h

/* Forward declare reference to classes to prevent multiple .h ambiguity */
class VertexBufferLayout;
class VertexBuffer;

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();
    
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    
    void Bind() const;
    void Unbind() const;
private:
    unsigned int m_RenderID;
};

#endif /* VertexArray_h */
