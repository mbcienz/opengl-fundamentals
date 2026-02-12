# How to build GLFW
Download the GLFW source code from https://www.glfw.org/download.html (source package button). 

We want to compile the library ourselves to have a better performance, tailored for our PC.

To biuld the library we'll use CMake: 
1. Select the source folder (the one we installed and extracted)
2. Select the build folder. This folder will contains the binaries. It can be any folder you want.
3. Press the "configure" button. Here you can select the generator. If you use Visual Studio, than select the proper version of Visual Studio and it will generate the right solution. Otherwise select the right generator, like MinGW Makefiles if you use MinGW and Make. If necessary specify the path to the compilers.
4. Check if do you wanna change something in the configuration, change (optionally) the install folder from the CMAKE_INSTALL_PREFIX option, and then press again the "Configure" button. 
5. Press the "generate" button.

Now, in the build folder you should find the build. At this point we want to compile the library. If you are using the Visual Studio IDE, follow the steps in the https://learnopengl.com/Getting-started/Creating-a-window guide. If you are gonna compile it manually, then open the folder in the terminal and run the command "make" and then "make install". 

You will find the include files andd the library in the folder specified in the CMAKE_INSTALL_PREFIX option.