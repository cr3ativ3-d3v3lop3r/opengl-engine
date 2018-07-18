//
//  main.cpp
//  Engine
//
//  Created by Callum Cooper Work on 11/02/2018.
//  Copyright © 2018 Callum Cooper. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../headers/Renderer.h"
#include "../headers/IndexBuffer.h"
#include "../headers/VertexBuffer.h"
#include "../headers/VertexBufferLayout.h"
#include "../headers/VertexArray.h"
#include "../headers/Shader.h"
#include "../headers/Texture.h"

/* Define an error callback function to help debug */
void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

/* Application entry point */
int main(void)
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
    {
        glfwSetErrorCallback(error_callback);
        return -1;
    }
    
    /* As we are running on Mac we will tell the OS to switch from OpenGLs legacy profile
     * to it's core profile - https://stackoverflow.com/questions/19865463/opengl-4-1-under-mavericks
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Engine", NULL, NULL);
    if (!window)
    {
        glfwSetErrorCallback(error_callback);
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Ensure monitor refresh rate is smooth */
    glfwSwapInterval(1);
    
    /* Error checking glewInit() */
    if (glewInit() != GLEW_OK)
        std::cout << "Error: glewInit() was not equal to GLEW_OK!" << std::endl;
    
    /* Print to the console the OpenGL version that is running */
    std::cout << "GL_VERSION running is " << glGetString(GL_VERSION) << std::endl;
    
    /* Print the supported GLSL version in this GPU chipset is */
    std::cout << "Supported GLSL version on this GPU chipset is " << (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    /* Define our vertex buffer with our texture coords to send over to the GPUs VRAM */
    float positions[] = {
       -0.5f, -0.5f, 0.0f, 0.0f, // 0 (x, y) vertex(left) && texture(right) coords
        0.5f, -0.5f, 1.0f, 0.0f, // 1
        0.5f,  0.5f, 1.0f, 1.0f, // 2
       -0.5f,  0.5f, 0.0f, 1.0f // 3
    };
    
    /* Create an index buffer */
    unsigned int indices[] = {
        0, 1, 2, // triangle 01 (vertex 0, vertex 1, vertex 2) ^^
        2, 3, 0  // triangle 02 (vertex 2, vertex 3, vertex 0) ^^
    };
    
    /* Setup blending to correctly draw transparency on textures */
     GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    /* VAO - Vertex array && vertex buffer  */
    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    
    /* Define our vertex buffer layout */
    VertexBufferLayout layout;
    layout.push(2, VALUETYPE::FLOAT);
    layout.push(2, VALUETYPE::FLOAT);
    
    /* Add our vertex buffer to our vertex array with a specified layout */
    va.AddBuffer(vb, layout);
    
    /* Setup the index buffer which is bound automatically in constructor */
    IndexBuffer ib(indices, 6);
    
    /* Create and setup our shader program NOTE: needs to be changed to relative path */
    Shader shader("/Users/callumcooper/Desktop/gameDev/Engine/Engine/res/shaders/Basic.shader");
    shader.Bind();
    
    /* Pass colour data to our shader via a uniform */
    shader.SetUniform4f("u_Colour", 0.2f, 0.3f, 0.8f, 1.0f);
    
    /* Setup our texture */
    Texture texture("/Users/callumcooper/Desktop/gameDev/Engine/Engine/res/textures/mario.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    
    /* Unbind every buffer from our shader program as a test */
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    
    /* Initialise our new uniform colour values */
    float r = 0.0f;
    float g = 0.3f;
    float b = 0.8f;
    float a = 1.0f;
    
    /* Increment our uniform colour values in render loop to simulate animation */
    float increment = 0.05f;
    
    /* Create a new instance of our renderer class */
    Renderer renderer;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        
        shader.Bind();
        shader.SetUniform4f("u_Colour", r, g, b, a);
 
        /* Draw vertices && indices && shader to screen */
        renderer.Draw(va, ib, shader);
        
        /* Increment red to simulate animation */
        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;
        
        r += increment;
        
        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));
        
        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }
    
    /* Clean up vertex array memory */
    va.Unbind();
    
    /* Clean up index buffer memory */
    ib.Unbind();
    
    /* Clean up shader */
    shader.Unbind();
    
    GLCall(glfwTerminate());
    
    return 0;
}
