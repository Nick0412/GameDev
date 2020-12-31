#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Program.h"
// #include "VertexModel.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	auto const src_str = [source]() {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		}
	}();

	auto const type_str = [type]() {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		}
	}();

	std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}

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

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(message_callback, nullptr);

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
        std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";

    
        // GLuint vao;
        // glGenVertexArrays(1, &vao);
        // glBindVertexArray(vao);
        
        // GLuint ibo;
        // glGenBuffers(1, &ibo);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size()*sizeof(GLint), indicies.data(), GL_STATIC_DRAW);

        // GLuint vbo;
        // glGenBuffers(1, &vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // glBufferData(GL_ARRAY_BUFFER, positions.size()*sizeof(GLfloat), positions.data(), GL_STATIC_DRAW);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        // glEnableVertexAttribArray(0);
    
        GLuint vao;
        glCreateVertexArrays(1, &vao);

        GLuint vbo;
        glCreateBuffers(1, &vbo);
        glNamedBufferStorage(vbo, positions.size()*sizeof(GLfloat), positions.data(), GL_DYNAMIC_STORAGE_BIT);
        glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3*sizeof(GLfloat));
        glEnableVertexArrayAttrib(vao, 0);
        glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vao, 0, 0);

        GLuint ibo;
        glCreateBuffers(1, &ibo);
        glNamedBufferStorage(ibo, sizeof(GLint)*indicies.size(), indicies.data(), GL_DYNAMIC_STORAGE_BIT);
        glVertexArrayElementBuffer(vao, ibo);

        glBindVertexArray(vao);
        
        CoreGL::Program program;
        program.attachShader(GL_VERTEX_SHADER, "simple-vert.glsl");
        program.attachShader(GL_FRAGMENT_SHADER, "simple-frag.glsl");
        program.linkProgram();

        // Main loop that keeps the window open until it is closed by the user.
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
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