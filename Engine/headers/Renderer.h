//
//  Renderer.h
//  Engine
//
//  Created by Callum Cooper Work on 15/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//

#ifndef Renderer_h
#define Renderer_h

#include <iostream>
#include <GL/glew.h>

#include "VertexArray.h"

#define ASSERT(x) if (!(x)) __asm__("int $3");
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))


    /* Clear OpenGLs internal errors */
    void GLClearError();
    
    /* Check OpenGLs internal errors */
    bool GLLogCall(const char* function, const char* file, int line);

/* Forward declare classes to prevent ambiguity on multiple includes */
class IndexBuffer;
class Shader;

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
private:
};

#endif /* Renderer_h */
