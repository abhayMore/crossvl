#pragma once
#include <GL/glew.h>

namespace CGL::Graphics
{
	class OPENGLIndexBuffer
	{
		friend class Renderer;

	public:
		OPENGLIndexBuffer(GLuint* buffer)
			: m_buffer(nullptr)
		{
			m_buffer = buffer;
		}
		~OPENGLIndexBuffer() = default;

	private:
		GLuint* m_buffer;
	};
}