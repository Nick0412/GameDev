#include "glad/glad.h"
#include "glfw/glfw3.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    std::cout << "Beginning Program\n";

    try
    {
        // Initalize GLFW and create a window that's 800x800 pixels
        if (!glfwInit()) { throw std::runtime_error("GLFW failed to init."); }
        GLFWwindow* window = glfwCreateWindow(800, 800, "Window Title", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Window creation failed.");
        }
        
        // Set the current window we want to draw to and inform glad where to draw
        // OpenGL functions.
        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        glfwSwapInterval(1);

        // Main loop that keeps the window open until it is closed by the user.
        while (!glfwWindowShouldClose(window))
        {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::exit(EXIT_FAILURE);
    }

    return 0;
}