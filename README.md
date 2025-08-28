# learning-opengl
For other projects, I decided to learn OpenGL by going along with this: https://learnopengl.com/

## 2. OpenGL

### Tips:
- Update video card drivers

### Warnings:
- Newer versions of OpenGL targets most modern graphics cards so most target lower versions

## 3. Prepping to create a window

### GLFW:
Library in C giving us bare necessities required for rendering goodies to the screen. Allows us to create an OpenGL context, define window parameters, and handle user input.

- Downloaded the GLFW binary
- Installed CMake
- Built the GLFW binary with CMake
- Opened the generated GLFW solution in VS and built the solution
- Extracted the desired include and libs for a specific opengl header content ressource
- Added the references to the inlcude and library to a project + the dependencies to glfw3.lib and opengl32.lib

### GLAD:
Library that saves us time and headaches with functions declarations.

Just followed 3.5 similarly to the GLFW section.

## 4. Creating a window

Including glad goes before glfw3 as the second requires the first.