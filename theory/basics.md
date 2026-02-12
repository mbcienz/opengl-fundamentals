# What is OpenGL
OpenGL is a specification developed by Khronos Group, even if is mainly considered an API. 

The specification specifies what is the result of each function. The developers (mainly, GPU developers) have to implement the specification.

IMPORTANT: OpenGL is a large state machine. There are many variables that define how OpenGL should operate.

The OpenGL state is referred as OpenGL context. 

OpenGL libraries are written in C. To allow a higher abstraction, object are used. Object are structs which contain informations.

# Before starting
We need a window in which display the graphics. There already existing library to setup windows for OpenGL. The most popular libraries are GLUT, SDL, SFML and GLFW. We will use GLFW.

## GLFW
GLFW is a library, written in C, which allow us to create a OpenGL contex, define window parameters and handle user inputs.