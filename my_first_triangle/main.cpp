#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Callback for everytime a user resizes a window
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Check inputs (for experimentation purpose)
void processInput(GLFWwindow* window);

// My settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// Will compile dynamically at runtime
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

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
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MyFirstOpenGLWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Set the function to call on resizes
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initializes glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// NEW CODE FROM HERE TO BUILD OUR SHADER PROGRAM----------------------------------
	// In x y and z
	// 3 vertices for a triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// Creates our buffer
	unsigned int VBO, VAO;
	// We generate our VAO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Binds the VAO first, then bind and set vertex buffers, then configure vertex attributes.
	glBindVertexArray(VAO);

	// Binds the new buffer to the bugger array with the bindBuffer function
	// GL_ARRAY_BUFFER is the type of an array of buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 1. Our buffer array, 2. Size of what we want to add on the buffer, 3. what we want to write
	// 4. How we want the graphics card to manage the data. Could be:
	// GL_STREAM (set only once and used at most a few times)
	// GL_STATIC_DRAW (set only once and used many times)
	// GL_DYNAMIC_DRAW (data is changed a lot and used many times)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// create an object to use the shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach the shader code to the object and compile the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check if compiling was successful
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// If no errors were detected, our shader is now compiled

	// Now the fragment shader to be able to render a triangle.
	// Fragment shader -> calculating the color output of our pixels. (RGBA of 0.0 to 1.0)
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Now we link both shader objects into a shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// We can also check if linking failed
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// We activate the program object
	glUseProgram(shaderProgram);
	// We delete the shader objects once they've been linked into the program object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Tell OpenGL how it should interpret the vertex data
	// p1: which vertex attribute we want to configure. Sets the location to 0
	// p2: size of the vertex attribute (vec3 so 3 values)
	// p5: The type of data (vec* in GLSL is a bunch of floating points)
	// p4: if we want the data to be normalized (irrelevant for us right now)
	// p5: called the stride and specifies the space between consecutive vertex attributes.
	//	   Our array is tightly packed so 0, but there exist variants for later. So we just do 3 * float size.
	// p6: Weird cast to define the offset of where the position data begins in the buffer. To explore later.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	// Our render loop
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Specify the color to clear the screen with
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Clears the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Put the shader program and VAO in focus in OpenGL's state machine
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// Draw points 0-3 from the currently bound VAO with current in-use shader.
		glDrawArrays(GL_TRIANGLES, 0, 3);


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
