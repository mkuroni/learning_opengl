//// Exercice 2: 
//// Now create the same 2 triangles using two different VAOs and VBOs for their data.
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//
//// Callback for everytime a user resizes a window
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//// Check inputs (for experimentation purpose)
//void processInput(GLFWwindow* window);
//
//// My settings
//const unsigned int SCREEN_WIDTH = 800;
//const unsigned int SCREEN_HEIGHT = 600;
//
//// Will compile dynamically at runtime
//const char* vertexShaderSource = "#version 330 core\n"
//"layout(location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\n";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n";
//
//int main()
//{
//	// Initializes GLFW
//	glfwInit();
//	// Specifies that 3.3 is the version we want to use for this tutorial
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	// Creates a window
//	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MyFirstOpenGLWindow", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	// Set the function to call on resizes
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// Initializes glad
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// create an object to use the shader
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	// attach the shader code to the object and compile the shader
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	// check if compiling was successful
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// The shaders
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//
//	glUseProgram(shaderProgram);
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	// The triangles
//	// In x y and z
//	float triangle1[] = {
//		0.25f, 0.25f, 0.0f, // top
//		0.5f, -0.25f, 0.0f, // bottom right
//		0.0f, -0.25f, 0.0f, // bottom left
//	};
//	float triangle2[] = {
//			0.0f, -0.25f, 0.0f, // bottom right
//			-0.25f, 0.25f, 0.0f, // top
//			-0.5f, -0.25f, 0.0f, // bottom left
//	};
//
//	// Creates our buffer
//	unsigned int VBO_T1, VBO_T2, VAO_T1, VAO_T2;
//	// We generate our VAO
//	glGenVertexArrays(1, &VAO_T1);
//	glGenVertexArrays(1, &VAO_T2);
//	glGenBuffers(1, &VBO_T1);
//	glGenBuffers(1, &VBO_T2);
//
//	// Binds the VAO first, then bind and set vertex buffers, then configure vertex attributes.
//	glBindVertexArray(VAO_T1);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO_T1);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindVertexArray(VAO_T2);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO_T2);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// Our render loop
//	while (!glfwWindowShouldClose(window))
//	{
//		// Input
//		processInput(window);
//
//		// Specify the color to clear the screen with
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		// Clears the color buffer
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// Put the shader program and VAO in focus in OpenGL's state machine
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO_T1);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		glBindVertexArray(VAO_T2);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
