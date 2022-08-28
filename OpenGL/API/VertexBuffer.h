#pragma once
#include <gl\glew.h>
//#include <GLFW/glfw3.h>

class VertexBuffer
{
public:
	VertexBuffer(unsigned int size, const void* data);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_VertexBufferID;
};
