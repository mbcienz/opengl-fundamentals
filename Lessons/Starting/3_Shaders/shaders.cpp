#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <Shaders/shader_3.h>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void check_shader_compilation(unsigned int shader);
void framebuffer_size_callback(GLFWwindow* window, int widht, int height);
void keyProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods);

// if true go in "solid" mode, if false go in "wireframe" mode
bool type = true;


int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Triangle!", NULL, NULL);

    if(window == NULL){
        std::cout << "Failed to create the window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, keyProcessInput);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwTerminate();
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);



    // define the array of vertex we want to display. These range between -1.0 and 1.0
    float vertices[] = {
        // vertex coords    //vertex color
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    };
    
    unsigned int indices[] = {
        //0, 1, 2,
        //0, 2, 3
        0, 1, 2,
    };
    // create the VAO. This is responsible to store a pointer to the elements in the VBO.
    unsigned int VAO; 
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // now we want to cerate a buffer (an object wich contains the data) to send all the informations 
    // to the GPU for processing
    unsigned int VBO;
    // generate the ID for the buffer. In this phase the buffers doesn't exists yes. We are creating only
    // the ID
    glGenBuffers(1, &VBO);
    // now we create the array buffer, It's a buffer which will contains the vertex information
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // now we copy the vertices data into the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO; 
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    

    // now we need to tell to OpenGL how it should interpret the vertex data. In out case they are 
    // 3 vertices, each of them contains 3 float values (x,y,z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    
    Shader ourShader("./shader.vs", "./shader.fs");

    
    while(!glfwWindowShouldClose(window)){
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void keyProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    if(key == GLFW_KEY_Z && action == GLFW_PRESS){
        type = !type;
        if(type == true){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }
}

void check_shader_compilation(unsigned int shader){
    int success;
    char infoLog[512];
    int shaderType; 
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);
    
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        if(shaderType == GL_VERTEX_SHADER)
        {
            std::cout<< "VERTEX_SHADER";
        }
        else if(shaderType == GL_FRAGMENT_SHADER)
        {
            std::cout<< "FRAGMENT_SHADER";
        }

        std::cout << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
};