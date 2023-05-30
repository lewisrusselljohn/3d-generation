#include "Maze.h"

Maze::Maze(int r, int c) : rows(r), columns(c)
{
	/*
		There are r by c cells but 1 is added to count all of
		the corners for each cell
	*/
	points = new v2* [rows+1];
	for (int i = 0; i < rows+1; i++)
	{
		points[i] = new v2[columns+1];
	}

	for (int row = 0; row < rows + 1; row++)
	{
		for (int column = 0; column < columns + 1; column++)
		{
			points[row][column].x = -0.5f + column*(1.0f/columns);
			points[row][column].y = -0.5f + row*(1.0f/rows);
			printf("{ %f, %f }", points[row][column].x, points[row][column].y);
		}
		printf("\n");
	}

	// flatten the points into vertex data to be passed to GPU
	vertices = new float[(rows + 1) * (columns + 1) * 3];
	vertex_count = (rows + 1) * (columns + 1);
	int index = 0;
	for (int i = 0; i < rows+1; ++i) {
		for (int j = 0; j < columns+1; ++j) {
			vertices[index] = points[i][j].x;
			vertices[index + 1] = points[i][j].y;
			vertices[index + 2] = 0.0f;
			index+=3;
		}
	}

	for (int i = 0; i < (rows + 1) * (columns + 1) * 3; i++)
		printf(" %f \n", vertices[i]);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex_count*3, vertices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

Maze::~Maze()
{
	// Deallocate 2d array points memory
	for (int i = 0; i < rows; i++)
		delete[] points[i];
	delete[] points;
	delete[] vertices;
}

void Maze::Draw()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, vertex_count);
	glBindVertexArray(0);
}
