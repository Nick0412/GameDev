#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Program.h"
// #include "VertexModel.h"

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

        GLuint m_vao_id;
        glCreateVertexArrays(1, &m_vao_id);
        GLuint vbo_id_1;
        glCreateBuffers(1, &vbo_id_1);
        glNamedBufferData(vbo_id_1, sizeof(GLfloat)*12, positions.data(), GL_STATIC_DRAW);
        GLuint vbo_id_2;
        glCreateBuffers(1, &vbo_id_2);
        glNamedBufferStorage(vbo_id_2, sizeof(GLfloat)*12, indicies.data(), GL_DYNAMIC_STORAGE_BIT);
        glVertexArrayVertexBuffer(m_vao_id, 0, vbo_id_1, 0, 0);
        glVertexArrayElementBuffer(m_vao_id, vbo_id_2);
        glEnableVertexArrayAttrib(m_vao_id, 0);
        glVertexArrayAttribFormat(m_vao_id, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(m_vao_id, 0, 0);

        // glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(vertex_t));
        // glVertexArrayElementBuffer(vao, ibo);

        // glEnableVertexArrayAttrib(vao, 0);
        // glEnableVertexArrayAttrib(vao, 1);
        // glEnableVertexArrayAttrib(vao, 2);

        // glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, pos));
        // glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, nrm));
        // glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(vertex_t, tex));

        // glVertexArrayAttribBinding(vao, 0, 0);

        CoreGL::Program program;
        program.attachShader(GL_VERTEX_SHADER, "simple-vert.glsl");
        program.attachShader(GL_FRAGMENT_SHADER, "simple-frag.glsl");
        program.linkProgram();

        // Main loop that keeps the window open until it is closed by the user.
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glBindVertexArray(m_vao_id);
            program.useProgram();
            
            glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
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