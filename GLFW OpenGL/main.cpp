#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "SOIL2/SOIL2.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;


int main()
{
    //Initialize GLFW
    glfwInit();
    
    //Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    //Create a GLFWwindow object that we can use for GLFWs functions
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if(nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    if(GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        
        return EXIT_FAILURE;
    }
    //Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader ourShader("resources/shaders/core.vs", "resources/shaders/core.frag");
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    // use with Orthographic Projection
    /*
     GLfloat vertices[] = {
     -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,
     0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 0.0f,
     0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
     0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
     -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
     -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,
     
     -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
     0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
     0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
     0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,
     -0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 1.0f,
     -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
     
     -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
     -0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
     -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
     -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
     -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
     -0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
     
     0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
     0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
     0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
     0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
     0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
     0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
     
     -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
     0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
     0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
     0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
     -0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
     -0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
     
     -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f,
     0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,
     0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
     0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.0f,
     -0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f,
     -0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 1.0f
     };
     */
    
    // use with Perspective Projection
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
    //Position Attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), (GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    
    //Texture Coordinate Attribute
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), (GLvoid * ) (3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray( 2 );
    
    glBindVertexArray( 0 );
    
    GLuint texture;
    
    int width, height;
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    unsigned char* image = SOIL_load_image("resources/images/image2.png", &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glm::mat4 projection;
    projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 1000.0f);
    
    //Game Loop
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        glClearColor(0.5f, 0.3f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //draw OpenGL
        ourShader.Use();
       
        glm::mat4 transform(1);
        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, (GLfloat)glfwGetTime() * -2.0f, glm::vec3(0.0f,0.0f, 1.0f));
        
        GLint transformLocation = glGetUniformLocation(ourShader.Program, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture"), 0);
        
        glBindVertexArray( VAO );
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray( 0 );
        
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    
    glfwTerminate();
    
    return 0;
}
