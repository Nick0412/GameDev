#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Program.h"
#include "Shader.h"
#include "Uniform.h"
#include "VertexModel.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>


int main()
{
    std::cout << "Beginning Program\n";

    // Data 
	std::vector<GLfloat> positions = {
		-0.5, 0.5, 0,	// V0
		-0.5, -0.5, 0,	// V1
		0.5, -0.5, 0,	// V2
		0.5, 0.5, 0		// V3
	};

	// Indicies
	std::vector<GLint> indicies = {
		0,1,3,	// Traingle 1 {V0, V1, V3}
		3,1,2	// Triangle 2 {V3, V1, V2}
	};

    // TODO: Abstarct GLFW window handler logic out in an RAII manner.
    // TODO: Abstract running progam in application class.
    try
    {
        // Initalize GLFW and create a window that's 800x800 pixels
        if (!glfwInit()) { throw std::runtime_error("GLFW failed to init."); }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
        model.storeIndexData(indicies);
        model.storeDataInAttribute(0, 3, positions);
        
        CoreGL::Shader shader(GL_VERTEX_SHADER, "rotating-vert.glsl");
        CoreGL::Shader shader2(GL_FRAGMENT_SHADER, "simple-frag.glsl");
        CoreGL::Program prog;
        prog.attachShader(shader);
        prog.attachShader(shader2);
        prog.loadProgram();

        // Main loop that keeps the window open until it is closed by the user.
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            prog.useProgram();

            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
            prog["rotation"].setMatrix(transform);

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