#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include <cmath>
#include <stb/stb_image.h>

int main()
{
    // texture variables
    int w, h, numCol;
    // loading texture info
    unsigned char* bytes = stbi_load("jbTex.jpg", &w, &h, &numCol, 0);
    
    // creating texture variable
    GLuint texture;

    // creating texture object
    glGenTextures(1, &texture);

    // adding texture to Unit Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // setting texture parameteres
    // filter type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // tiling type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // transform into str space
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    // generating mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
    // free memory
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apuntador de refrencia a la ventana que se usara en la gpu
    GLFWwindow* window = glfwCreateWindow(800, 800, "test", NULL, NULL);
    
    glfwSetTime(0);
        GLfloat vertices[] =
        {
            -0.5f, 0.5f * float(sqrt(3)) / 3 , 0.0f, 0.4902, 0.1294f, 0.5059f, //esquina inferior izquierda
            0.5f, 0.5f * float(sqrt(3)) / 3 , 0.0f, 0.18431f,  0.18039f,  0.30980f, //esquina inferior derecha
            0.0f, -0.5f * float(sqrt(3)) * 2 / 3 , 0.0f, 0.21176f, 0.94510f, 0.80392f, //punta de la trifuerza
            -0.5f / 2, -0.5f * float(sqrt(3)) / 6 , 0.0f, 0.3412f, 0.1373f, 0.3922f, //esquina superior izquierda
            0.5f / 2, -0.5f * float(sqrt(3)) / 6 , 0.0f,0.18431f,  0.18039f,  0.30980f, //esquina superior derecha
            0.0f, 0.5f * float(sqrt(3)) / 3 , 0.0f, 0.21176f, 0.94510f, 0.80392f, //Base
        };

        GLfloat squareVertices[] =
        {
         -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f
        };

        GLuint indices[] =
        {
        0, 3, 5, // Triangulo inferior izq
        3, 2, 4, // Triangulo inferior der
        5, 4, 1, // Triangulo superior
        6, 9, 11,
        9, 8, 10,
        11, 10, 7,
        };

        GLuint squareIndices[] =
        {
         0, 2, 1,
         0, 3, 2
        };

        glfwMakeContextCurrent(window);
        gladLoadGL();

        //se crean shaders
        //Shader shaderProgram("default.vert", "default.frag");
        //Shader shaderInside("inner.vert", "inner.frag");
        Shader defaultShader("default.vert", "default.frag");



        VAO VAO1;
        VAO1.Bind();
        
        VBO VBO1(squareVertices, sizeof(squareVertices));

        EBO EBO1(squareIndices, sizeof(squareIndices));

        VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
        VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));


        VAO1.Unbind();
        VBO1.Unbind();
        EBO1.Unbind();

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.16863,  0.18824,  0.22745, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            //shaderProgram.Activate();
            defaultShader.Activate();

            //std::cout << sinScale << std::endl;

            VAO1.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
        VAO1.Delete();
        VBO1.Delete();
        EBO1.Delete();

        defaultShader.Delete();
   


        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
}