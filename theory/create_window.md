# Create Widnow with GLFW. 
The window documentation is available at https://www.glfw.org/docs/latest/window.html#window_hints . A quick guide is available at https://www.glfw.org/docs/latest/quick_guide.html . 

The GLFW has the objective to create the OpenGL context (the OpenGL state). So, first of all we need to initialize the GLFW library through glfwInit() function.

This function return GLFW_TRUE or GLFW_FALSE based on the result (success or failure).
This constants (GLFW_TRUE and GLFW_FALSE) are one and zero.

Then we can configure some Hints. The most important are referred to the minimim and maximum OpenGL versions and its type (core or legacy).

After that, we can create the window using the glfwCreateWidnow