#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include <cmath>


GLfloat smoothFloat(GLfloat time) 
{
    float value = sin(time) * 0.2f + 1.0f; // scale sin value to range 0.8 to 1.2
    return value;
}

//GL_FLOAT_VEC4 normalizeColor(GL_INT_VEC4 inputColor)
//{
//    GL_FLOAT_VEC4 value = inputcolor * 255f;
//    return value;
//}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //apuntador de refrencia a la ventana que se usara en la gpu
    GLFWwindow* window = glfwCreateWindow(800, 800, "test", NULL, NULL);

    double seconds = 0.0f;
    float anim = 0.1f;

    glfwSetTime(0);

    
        /*
        GLfloat vertices[] =
        {
            -0.5f + (anim/1000), 0.0f, 0.0f, 1.0f, 0.8431f , 0.0f,
            0.5f - (anim / 1000), 0.0f, 0.0f, 0.9922f, 0.9922f, 0.5882f,
            0.0f, 0.6f - (anim / 750), 0.0f, 0.9922f, 0.9922f, 0.5882f,
            -0.5f / 2 + (anim / 10000), 0.3f - (anim / 1000), 0.0f, 1.0f, 0.8431f , 0.0f,
            0.5f / 2 - (anim / 10000), 0.3f - (anim / 1000), 0.0f, 1.0f, 1.0f , 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.8431f , 0.0f,

            -0.5f + (anim / 1000), 0.0f, 0.0f, 0.3412f, 0.1373f, 0.3922f, //esquina inferior izquierda
            0.5f - (anim / 1000), 0.0f, 0.0f, 0.4902, 0.1294f, 0.5059f, //esquina inferior derecha
            0.0f, -0.6f + (anim / 750), 0.0f, 0.3412f, 0.1373f, 0.3922f, //punta de la trifuerza
            -0.5f / 2 + (anim / 10000), -0.3f + (anim / 1000), 0.0f, 0.0f, 0.0f , 0.0f, //esquina superior izquierda
            0.5f / 2 - (anim / 10000), -0.3f + (anim / 1000), 0.0f, 0.3412f, 0.1373f, 0.3922f, //esquina superior derecha
            0.0f, 0.0f, 0.0f, 0.3412f, 0.1373f, 0.3922f, //Base
        };

        */
        GLfloat vertices[] =
        {
            -0.5f, 0.5f * float(sqrt(3)) / 3 , 0.0f, 0.4902, 0.1294f, 0.5059f, //esquina inferior izquierda
            0.5f, 0.5f * float(sqrt(3)) / 3 , 0.0f, 0.3412f, 0.1373f, 0.3922f, //esquina inferior derecha
            0.0f, -0.5f * float(sqrt(3)) * 2 / 3 , 0.0f, 0.3412f, 0.1373f, 0.3922f, //punta de la trifuerza
            -0.5f / 2, -0.5f * float(sqrt(3)) / 6 , 0.0f, 0.3412f, 0.1373f, 0.3922f, //esquina superior izquierda
            0.5f / 2, -0.5f * float(sqrt(3)) / 6 , 0.0f, 0.0f, 0.0f , 0.0f, //esquina superior derecha
            0.0f, 0.5f * float(sqrt(3)) / 3 , 0.0f, 0.3412f, 0.1373f, 0.3922f, //Base
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

        glfwMakeContextCurrent(window);
        gladLoadGL();

        //se crean shaders
        //Shader shaderProgram("default.vert", "default.frag");
        //Shader shaderInside("inner.vert", "inner.frag");
        Shader ExamOuter("ExamOuter.vert", "ExamOuter.frag");
        //Shader ExamInner("ExamInner.vert", "ExamInner.frag");

        VAO VAO1;
        VAO1.Bind();

        //VAO VAO2;
        //VAO2.Bind();

        VBO VBO1(vertices, sizeof(vertices));
        //VBO VBO2(vertices, sizeof(vertices));

        EBO EBO1(indices, sizeof(indices));

        VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
        VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

       // VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
        //VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        VAO1.Unbind();
        //VAO2.Unbind();
        
        VBO1.Unbind();
        //VBO2.Unbind();
        EBO1.Unbind();

        //GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); 
        //GLuint uniID = glGetUniformLocation(ExamOuter.ID, "scale");
        
        
        

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //shaderProgram.Activate();
        ExamOuter.Activate();
        GLfloat sinScale = glGetUniformLocation(ExamOuter.ID, "sinScale");
        GLfloat currentSinScale = smoothFloat(glfwGetTime());
        std::cout << currentSinScale << std::endl;

        glUniform1f(sinScale, currentSinScale);

        //std::cout << sinScale << std::endl;

        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

        VAO1.Delete();
        VBO1.Delete();
        EBO1.Delete();

        //shaderProgram.Delete();
        //shaderInside.Delete();
        //ExamInner.Delete();
        ExamOuter.Delete();

        glViewport(0, 0, 800, 800);
        glfwSwapBuffers(window);
    

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}