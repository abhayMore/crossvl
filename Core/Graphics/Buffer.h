#pragma once

#include <Core/Graphics/Types.h>
#include <Core/Types.h>
#include <typeindex>

#if defined(CGL_RHI_DX11)
#include <Core/Graphics/RHI/D3D11/D3D11VertexBuffer.h>
#include <Core/Graphics/RHI/D3D11/D3D11IndexBuffer.h>
#include <Core/Graphics/RHI/D3D11/D3D11ConstantBuffer.h>
#endif

#if defined(CGL_RHI_DX12)
#include <Core/Graphics/RHI/D3D12/D3D12VertexBuffer.h>
#include <Core/Graphics/RHI/D3D12/D3D12IndexBuffer.h>
#endif

#if defined(CGL_RHI_OPENGL)
#include <Core/Graphics/RHI/OpenGL/OPENGLVertexBuffer.h>
#include <Core/Graphics/RHI/OpenGL/OPENGLIndexBuffer.h>
#include <Core/Graphics/RHI/OpenGL/OPENGLConstantBuffer.h>
#endif

#if defined(CGL_RHI_METAL)
#include <Core/Graphics/RHI/Metal/METALVertexBuffer.h>
#include <Core/Graphics/RHI/Metal/METALIndexBuffer.h>
#include <Core/Graphics/RHI/Metal/METALConstantBuffer.h>
#endif

#if defined(CGL_RHI_VULKAN)
#include <Core/Graphics/RHI/Vulkan/VULKANVertexBuffer.h>
#include <Core/Graphics/RHI/Vulkan/VULKANIndexBuffer.h>
#endif

namespace CGL::Graphics
{
	struct BufferSource
	{
		BufferType Type   = BufferType::None;
		BufferUsage Usage = BufferUsage::Default;
		u32 TypeSize      = 0;
		u32 Count         = 0;
		void* Data        = nullptr;
		std::type_index VertexType = typeid(void);
	};

#if defined(CGL_RHI_DX11)
	using VertexBuffer = D3D11VertexBuffer;
	using IndexBuffer  = D3D11IndexBuffer;
	template <typename T> using ConstantBuffer = D3D11ConstantBuffer<T>;
#elif defined(CGL_RHI_DX12)
	using VertexBuffer = D3D12VertexBuffer;
	using IndexBuffer  = D3D12IndexBuffer;
#elif defined(CGL_RHI_OPENGL)
	using VertexBuffer = OPENGLVertexBuffer;
	using IndexBuffer  = OPENGLIndexBuffer;
	template <typename T> using ConstantBuffer = OPENGLConstantBuffer<T>;
#elif defined(CGL_RHI_METAL)
	using VertexBuffer = METALVertexBuffer;
	using IndexBuffer  = METALIndexBuffer;
	template <typename T> using ConstantBuffer = METALConstantBuffer<T>;
#elif defined(CGL_RHI_VULKAN)
	using VertexBuffer = VULKANVertexBuffer;
	using IndexBuffer  = VULKANIndexBuffer;
#else
	#error Unsupported buffer types for RHI
#endif
}
