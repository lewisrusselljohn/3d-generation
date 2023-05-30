#include "Maze.h"

Maze::Maze(int r, int c) : rows(r), columns(c)
{
	float start_x = -0.5f;
	float start_y = -0.5f;

	std::vector<GLfloat> hor_verts;
	std::vector<GLfloat> ver_verts;

	for (int row = 0; row <= rows; row++)
	{
		for (int column = 0; column <= columns; column++)
		{


			float x = start_x + (1.0f / columns)*column;
			float y = start_y + (1.0f / rows)*row;
			float z = 0.0f;
			float x2 = start_x + (1.0f / columns) * (column+1);
			float y2 = start_y + (1.0f / rows) * (row+1);

			if (column != columns)
			{
				hor_verts.push_back(x);
				hor_verts.push_back(y);
				hor_verts.push_back(z);

				hor_verts.push_back(x2);
				hor_verts.push_back(y);
				hor_verts.push_back(z);
			}

			if (row != rows)
			{
				ver_verts.push_back(x);
				ver_verts.push_back(y);
				ver_verts.push_back(z);

				ver_verts.push_back(x);
				ver_verts.push_back(y2);
				ver_verts.push_back(z);
			}
		}
	}

	GLfloat* hor_vert_data = hor_verts.data();
	hor_vbo_size = hor_verts.size();

	// Setup horizontal vao
	glGenVertexArrays(1, &hor_vao);
	glBindVertexArray(hor_vao);

	glGenBuffers(1, &hor_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, hor_vbo);
	
	//Pass the vertex data to the GPU VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*hor_vbo_size, hor_vert_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Setup vertical vao
	glGenVertexArrays(1, &ver_vao);
	glBindVertexArray(ver_vao);

	GLfloat* ver_vert_data = ver_verts.data();
	ver_vbo_size = ver_verts.size();

	glGenBuffers(1, &ver_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ver_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * ver_vbo_size, ver_vert_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
}


Maze::~Maze()
{

}

void Maze::DrawArrays()
{

	// Bind and draw vertical VAO
	glBindVertexArray(ver_vao);
	glDrawArrays(GL_LINES, 0, ver_vbo_size);

	// Bind and draw horizontal VAO
	glBindVertexArray(hor_vao);
	glDrawArrays(GL_LINES, 0, hor_vbo_size);

	glBindVertexArray(0);
}
