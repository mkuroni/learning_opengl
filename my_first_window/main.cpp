#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Callback for everytime a user resizes a window
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Check inputs (for experimentation purpose)
void processInput(GLFWwindow* window);

// Code for Hello Triangle
void myFirstTriangle();

int main()
{
	// Initializes GLFW
	glfwInit();
	// Specifies that 3.3 is the version we want to use for this tutorial
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Creates a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "MyFirstOpenGLWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initializes glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Tells OpenGL the size of the window we want to generate (location x y, width and height)
	glViewport(0, 0, 800, 600);

	// Set the function to call on resizes
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Our render loop
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// More rendering commands here
		// ...
		// Specify the color to clear the screen with
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Clears the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Properly clean the resources
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	// If the escape key is pressed, we close the window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	/*
	Behind the scenes OpenGL uses the data specified via glViewport to transform the 2D coordinates it processed to coordinates on your screen.
	For example, a processed point of location (-0.5,0.5) would (as its final transformation) be mapped to (200,450) in screen coordinates.
	Note that processed coordinates in OpenGL are between -1 and 1 so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600).
	*/

	glViewport(0, 0, width, height);
}
