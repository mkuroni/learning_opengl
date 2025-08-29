// Exercice 3: 
// Create two shader programs where the second program uses a different fragment shader
// that outputs the color yellow; draw both triangles again where one outputs the color yellow.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Callback for everytime a user resizes a window
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Check inputs (for experimentation purpose)
void processInput(GLFWwindow* window);

void validateShader(unsigned int element, int success);

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

const char* fragmentShaderSourceYellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
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

	// create an object to use the shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach the shader code to the object and compile the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check if compiling was successful
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	validateShader(vertexShader, success);

	// The shaders
	unsigned int fragmentShader, fragmentShaderYellow;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
	glCompileShader(fragmentShaderYellow);
	unsigned int shaderProgram, shaderProgramYellow;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	validateShader(shaderProgram, success);

	glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
	validateShader(shaderProgramYellow, success);

	glUseProgram(shaderProgram);
	glUseProgram(shaderProgramYellow);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShaderYellow);

	// The triangles
	// In x y and z
	float triangle1[] = {
		0.25f, 0.25f, 0.0f, // top
		0.5f, -0.25f, 0.0f, // bottom right
		0.0f, -0.25f, 0.0f, // bottom left
	};
	float triangle2[] = {
			0.0f, -0.25f, 0.0f, // bottom right
			-0.25f, 0.25f, 0.0f, // top
			-0.5f, -0.25f, 0.0f, // bottom left
	};

	// Creates our buffer
	unsigned int VBO_T1, VBO_T2, VAO_T1, VAO_T2;
	// We generate our VAO
	glGenVertexArrays(1, &VAO_T1);
	glGenVertexArrays(1, &VAO_T2);
	glGenBuffers(1, &VBO_T1);
	glGenBuffers(1, &VBO_T2);

	// Binds the VAO first, then bind and set vertex buffers, then configure vertex attributes.
	glBindVertexArray(VAO_T1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_T1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO_T2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_T2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
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
		glBindVertexArray(VAO_T1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAO_T2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void validateShader(unsigned int element, int success)
{
	char infoLog[512];
	if (!success)
	{
		glGetProgramInfoLog(element, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}