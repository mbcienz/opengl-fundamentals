// import always glad before glfw. Tipically it goes before every call to an OpenGL function.
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// settings
const unsigned  int WIDTH = 800;
const unsigned  int HEIGHT = 600;

// callback for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(){
    // initialize GLFW library
    glfwInit();

    // setup the information about the OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    // create the window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hellow Window!", NULL, NULL); 
    
    // check if the window has been created with success
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW Window " << std::endl;
        // deallocate all the resources and terminate the GLFW library
        glfwTerminate();
        return -1;
    }

    // if the window has been successfully created we tell  to GLFW that the context specified if 
    // this window must to be the main. This means that if will be on the current thread.
    glfwMakeContextCurrent(window);
    // set the resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    
    // load GLAD: load all OpenGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //we need to tell OpenGL the sisze of the rendering window.
    // It doesn't need to match the GLFW size. It can be, for example, smaller, and 
    // we can insert other elements outside. 
    glViewport(0, 0, WIDTH, HEIGHT);

    

    // render loop. This allow the window to exist untile the program is closed
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        // rendering commands: 
        // just to say: if you want to create a transparent window (alpha=0.0f) you need
        // to call GLFWwindowHint(GLFW_TRANPARENT_FRAMEBUFFER, GLFW_TRUE) at beginning
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //check for inputs (keyboard, mouse, ...)
        glfwPollEvents();
        // swap the 2D buffer (contains color values for each pixel in the GLFW's window)
        glfwSwapBuffers(window);
    }

    // clean the allocated GLFW's resources
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