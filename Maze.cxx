#include "Maze.h"

Maze::Maze(int r, int c) : rows(r), columns(c)
{
	//CreateGrid();
	CreateMaze();
}

Maze::~Maze()
{
	glDeleteBuffers(1, &ver_vbo);
	glDeleteBuffers(1, &hor_vbo);
	glDeleteVertexArrays(1, &hor_vao);
	glDeleteVertexArrays(1, &ver_vao);
}

void Maze::CreateGrid()
{
	float start_x = -0.5f;
	float start_y = -0.5f;

	std::vector<GLfloat> hor_verts;
	std::vector<GLfloat> ver_verts;

	for (int row = 0; row <= rows; row++)
	{
		for (int column = 0; column <= columns; column++)
		{

			float x = start_x + (1.0f / columns) * column;
			float y = start_y + (1.0f / rows) * row;
			float z = 0.0f;
			float x2 = start_x + (1.0f / columns) * (column + 1);
			float y2 = start_y + (1.0f / rows) * (row + 1);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * hor_vbo_size, hor_vert_data, GL_STATIC_DRAW);

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

/* For a start, a very horizontal maze.
	I could improve this further by repeating the number of times a vertical line and 2 horizontal lines
	are removed in a row, based on how long the rows are. As it is right now, very long rows tend to have
	very long hallways which are dead ends.
	You could creatively use these long hallways in the game or otherwise just make something that is more complex.
*/
void Maze::CreateMaze()
{
	float start_x = -0.5f;
	float start_y = -0.5f;

	std::vector<GLfloat> hor_verts;
	std::vector<GLfloat> ver_verts;

	srand((unsigned)time(NULL));

	for (int row = 0; row <= rows; row++)
	{
		int skip_hor = rand() % (columns-1) + 1;
		for (int column = 0; column <= columns; column++)
		{

			float x = start_x + (1.0f / columns) * column;
			float y = start_y + (1.0f / rows) * row;
			float z = 0.0f;
			float x2 = start_x + (1.0f / columns) * (column + 1);
			float y2 = start_y + (1.0f / rows) * (row + 1);

			float x0 = start_x + (1.0f / columns) * (column - 1);
			float y0 = start_y + (1.0f / rows) * (row - 1);

			if (column != columns)
			{
				
				if (row == 0 || row == rows)
				{
					hor_verts.push_back(x);
					hor_verts.push_back(y);
					hor_verts.push_back(z);

					hor_verts.push_back(x2);
					hor_verts.push_back(y);
					hor_verts.push_back(z);
				}
				else
				{
					if (column == skip_hor || column == skip_hor -1)
					{
						// Dont add the horizontal row and reset skip_hor
						if(column == skip_hor)
						{
							ver_verts.push_back(x);
							ver_verts.push_back(y);
							ver_verts.push_back(z);

							ver_verts.push_back(x);
							ver_verts.push_back(y2);
							ver_verts.push_back(z);

							skip_hor = -1;
						}
						
					}
					else 
					{
						hor_verts.push_back(x);
						hor_verts.push_back(y);
						hor_verts.push_back(z);

						hor_verts.push_back(x2);
						hor_verts.push_back(y);
						hor_verts.push_back(z);
					}
				}
			}

			if (row != rows)
			{
				if (column == 0 || column == columns)
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
	}

	GLfloat* hor_vert_data = hor_verts.data();
	hor_vbo_size = hor_verts.size();

	// Setup horizontal vao
	glGenVertexArrays(1, &hor_vao);
	glBindVertexArray(hor_vao);

	glGenBuffers(1, &hor_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, hor_vbo);

	//Pass the vertex data to the GPU VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * hor_vbo_size, hor_vert_data, GL_STATIC_DRAW);

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
