#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Program.h"
#include "VertexModel.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

int main()
{
    std::cout << "Beginning Program\n";

    // Data 
	std::vector<float> positions = {
		-0.5, 0.5, 0,	// V0
		-0.5, -0.5, 0,	// V1
		0.5, -0.5, 0,	// V2
		0.5, 0.5, 0		// V3
	};

	// Indicies
	std::vector<unsigned int> indicies = {
		0,1,3,	// Traingle 1 {V0, V1, V3}
		3,1,2	// Triangle 2 {V3, V1, V2}
	};

    // TODO: Abstarct GLFW window handler logic out in an RAII manner.
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

        CoreGL::VertexModel model;
        model.storeDataInAttribute(0, 3, positions);
        model.storeIndexData(indicies);

        CoreGL::Program program;
        program.attachShader(GL_VERTEX_SHADER, "simple-vert.glsl");
        program.attachShader(GL_FRAGMENT_SHADER, "simple-frag.glsl");
        program.linkProgram();

        // Main loop that keeps the window open until it is closed by the user.
        while (!glfwWindowShouldClose(window))
        {
            program.useProgram();
            model.bind();
            model.draw();
            model.unbind();

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