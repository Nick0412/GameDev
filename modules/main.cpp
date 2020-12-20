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
        if (!glfwInit()) { throw std::runtime_error("GLFW failed to init."); }
        GLFWwindow* window = glfwCreateWindow(800, 800, "Window Title", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Window creation failed.");
        }
        
        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        glfwSwapInterval(1);

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