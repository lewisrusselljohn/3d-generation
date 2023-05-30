#pragma once

#include <glew.h>
#include <stdio.h>

class Maze
{
private:
	struct v2 { float x; float y; };
	int rows;
	int columns;
	v2** points;
    GLfloat* vertices;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint vertex_count;

    // Vertex shader source code
    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    out vec3 fragmentColor;
    void main()
    {
        gl_Position = vec4(position, 1.0);
        fragmentColor = color;
    }
)";

    // Fragment shader source code
    const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 fragmentColor;
    out vec4 fragColor;
    void main()
    {
        fragColor = vec4(fragmentColor, 1.0);
    }
)";
public:
	Maze(int, int);
	~Maze();
    void Draw();
};