#pragma once
#include <glew.h>
#include <vector>

class Cage
{
private:
	GLuint vao, vbo, vbo_size;
public:
	Cage(double size, int increment);
	~Cage();

	void DrawLines();
};
