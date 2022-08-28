#pragma once
#include <gl/glew.h>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_VertexArrayID;
};
