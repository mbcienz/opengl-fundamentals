#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
// vertex shader. It is responsible for the vertex information. For now we will declare it using a string instead of coding it in an external file
// shaders are dinamically compiled. 
const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"; 


// fragment shader. It is responsible for the color output of the pixels. For now we will declare it using a string instead of coding it in an external file
// shaders are dinamically compiled. 
const char *fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "\n}";

void check_shader_compilation(unsigned int shader);
void framebuffer_size_callback(GLFWwindow* window, int widht, int height);
void processInput(GLFWwindow* window);

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

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwTerminate();
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);



    // define the array of vertex we want to display. These range between -1.0 and 1.0
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f, 
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    
    
    
    /*
    ================ VERTEX SHADER ================
    */
    // create the vertex shader
    unsigned int vertexShader; 
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // load the source code for the fragment shade in the ogject, and compile the shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check the result of the compilation; 
    check_shader_compilation(vertexShader);
    
    
    /*
    ================ FRAGMENT SHADER ================
    */
    unsigned int fragmentShader; 
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    check_shader_compilation(fragmentShader);

    /*
    ================ SHADER PROGRAM ================
    */
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // tha shader program combines the shaders and allow us to use it. We need to attach them first and 
    // then link them together. 
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //check the result of the linking (it's different from the other, so for now we don't resuse the function)
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);    
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        
        std::cout << "PROGRAM_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    
    //delete shader object, we have it in the program shader now.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    

    
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // every shader adn rendering call, after the glUseProgram function, will use this program object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
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