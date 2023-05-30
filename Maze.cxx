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
		}
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

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Pass the vertex data to the GPU VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex_count*3, vertices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Setup the Element Buffer Object

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);



	std::vector<GLuint> ind;


	// Generate indices for lines from the center of the cells
	for (int row = 0; row < rows; ++row) {
		for (int column = 0; column < columns; ++column) {
			int topLeft = row * (columns + 1) + column;
			int topRight = topLeft + 1;
			int bottomLeft = (row + 1) * (columns + 1) + column;
			int bottomRight = bottomLeft + 1;

			// Add indices to draw horizontal line
			ind.push_back(topLeft);
			ind.push_back(topRight);
			ind.push_back(topRight);
			ind.push_back(bottomRight);
		}
	}

	for (int column = 0; column < columns; ++column) {
		for (int row = 0; row < rows; ++row) {
			int topLeft = row * (columns + 1) + column;
			int topRight = topLeft + 1;
			int bottomLeft = (row + 1) * (columns + 1) + column;
			int bottomRight = bottomLeft + 1;

			// Add indices to draw vertical line
			ind.push_back(topLeft);
			ind.push_back(bottomLeft);
			ind.push_back(bottomLeft);
			ind.push_back(bottomRight);
		}
	}

	GLuint* indata = ind.data();

	ebo_size = ind.size();


	/*
		For a maze, an algorithm is required to delete cell walls, which
		means to remove a pair from the indices array.
	*/
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo_size*sizeof(GLuint), indata, GL_STATIC_DRAW);

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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_LINES, ebo_size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
