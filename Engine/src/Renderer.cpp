//
//  Renderer.cpp
//  Engine
//
//  Created by Callum Cooper Work on 15/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#include "../headers/Renderer.h"
#include "../headers/IndexBuffer.h"
#include "../headers/Shader.h"

/* Clear OpenGLs internal errors */
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

/* Check OpenGLs internal errors */
bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
    /* Use our shader program */
    shader.Bind();
    
    /* Bind buffers to our shader program */
    va.Bind();
    ib.Bind();
    
    /* Draw our index buffer */
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
        
