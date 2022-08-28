#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int size, const void* data)
{
	glGenBuffers(1, &m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(0, &m_VertexBufferID);
}

void VertexBuffer::Bind () const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
}

void VertexBuffer::UnBind () const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}