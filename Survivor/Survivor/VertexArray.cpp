#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices) :
	mNumVerts(numVerts),
	mNumIndices(numIndices)
{
	// vertex array
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);

	// vertex buffer
	unsigned int bufferSize = numVerts * 5 * sizeof(float);
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, verts, GL_STATIC_DRAW);

	// index buffer
	bufferSize = numIndices * sizeof(unsigned int);
	glGenBuffers(1, &mIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, indices, GL_STATIC_DRAW);

	// attrib
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteBuffers(1, &mIndexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArrayID);
}
