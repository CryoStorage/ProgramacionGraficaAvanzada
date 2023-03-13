#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include <cmath>

int main()
{
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
        

        GLuint indices[] =
        {
        0, 3, 5, // Triangulo inferior izq
        3, 2, 4, // Triangulo inferior der
        5, 4, 1, // Triangulo superior
        6, 9, 11,
        9, 8, 10,
        11, 10, 7,
        };
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}