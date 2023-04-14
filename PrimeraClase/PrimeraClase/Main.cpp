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
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apuntador de refrencia a la ventana que se usara en la gpu
    GLFWwindow* window = glfwCreateWindow(800, 800, "test", NULL, NULL);
    
    glfwMakeContextCurrent(window);
    
    gladLoadGL();

    // texture variables
    int w, h, numCol;
    // flipping texture
    stbi_set_flip_vertically_on_load(true);
    // loading texture info
    unsigned char* bytes0 = stbi_load("jbTex.jpg", &w, &h, &numCol, 0);
    unsigned char* bytes1 = stbi_load("d2Tex.jpg", &w, &h, &numCol, 0);

    //std::cout<< << sdt::endl;
    std::cout<< numCol << std::endl;

    // creating texture variable
    GLuint texture0, texture1;
    // creating texture object by specifying memory location
    glGenTextures(1, &texture0);

    // creating texture object by specifying memory location
    glGenTextures(1, &texture1);
    
    // 1st texture params
    // adding texture to Unlit Texture
    glBindTexture(GL_TEXTURE_2D, texture0);
    // setting texture parameters
    // filter type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // tiling type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // transform into STR space
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes0);
    // generating mipmap
    glGenerateMipmap(GL_TEXTURE_2D);

    // 2nd texture params
    // adding texture to Unlit Texture
    glBindTexture(GL_TEXTURE_2D, texture1);
    // setting texture parameters
    // filter type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // tiling type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // transform into STR space
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes1);
    // generating mipmap
    glGenerateMipmap(GL_TEXTURE_2D);

    // free memory
    stbi_image_free(bytes0);
    stbi_image_free(bytes1);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glfwSetTime(0);
        GLfloat triVertices[] =
        {
            -0.5f, 0.5f * float(sqrt(3)) / 3 , 0.0f, 0.4902, 0.1294f, 0.5059f, //esquina inferior izquierda
            0.5f, 0.5f * float(sqrt(3)) / 3 , 0.0f, 0.18431f,  0.18039f,  0.30980f, //esquina inferior derecha
            0.0f, -0.5f * float(sqrt(3)) * 2 / 3 , 0.0f, 0.21176f, 0.94510f, 0.80392f, //punta de la trifuerza
            -0.5f / 2, -0.5f * float(sqrt(3)) / 6 , 0.0f, 0.3412f, 0.1373f, 0.3922f, //esquina superior izquierda
            0.5f / 2, -0.5f * float(sqrt(3)) / 6 , 0.0f,0.18431f,  0.18039f,  0.30980f, //esquina superior derecha
            0.0f, 0.5f * float(sqrt(3)) / 3 , 0.0f, 0.21176f, 0.94510f, 0.80392f, //Base
        };

        GLfloat squareVertices[] =
        {//  |     coords      |      colors      | texCoord |
             -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
             -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
        };

        GLuint triIndices[] =
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
        Shader defaultShader("transition.vert", "transition.frag");

        VAO VAO1;
        VAO1.Bind();
        
        VBO VBO1(squareVertices, sizeof(squareVertices));

        EBO EBO1(squareIndices, sizeof(squareIndices));

        VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
        VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        VAO1.Unbind();
        VBO1.Unbind();
        EBO1.Unbind();

        defaultShader.Activate();

        GLuint uniMix = glGetUniformLocation(defaultShader.ID, "mixFactor");
        GLuint uniScale = glGetUniformLocation(defaultShader.ID, "scale");
        GLuint tex0uni = glGetUniformLocation(defaultShader.ID, "tex0");
        GLuint tex1uni = glGetUniformLocation(defaultShader.ID, "tex1");

        
        glUniform1i(tex0uni, 0);
        glUniform1i(tex1uni, 1);
        glUniform1i(uniScale, .5f);
    
    

        while (!glfwWindowShouldClose(window))
        {
            double seconds = 1.0f;
            GLfloat time = glfwGetTime() * seconds;
            // dark grey
            // glClearColor(0.16863,0.18824,0.22745,1);
            // milkShadow
            glClearColor(0.32549,0.14510,0.24314,1);
            // milkRed
            //glClearColor(0.67059,0.19608,0.19608,1);
            glClear(GL_COLOR_BUFFER_BIT);

            // set as texture0 as active texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture0);
            
            uniMix = sin(time)* 0.2f + 1.0f; // scale sin value to range 0 to 1
            glUniform1i(uniMix, uniMix);
            std::cout << uniMix << std::endl;
            // set as texture1 as active texture
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture1);
            
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