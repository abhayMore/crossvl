#include <Core/Graphics/Renderer.h>
#include <Core/Graphics/RHI/OpenGL/OPENGLRendererImpl.h>

namespace CGL::Graphics
{
    #ifdef CGL_RHI_OPENGL
    void Renderer::Constructor_OPENGL(SDL_Window* window)
    {
        this->m_impl = new OPENGLRendererImpl(window);

        CGL_LOG(Renderer, Info, "OpenGL Renderer Initialized");
    }

    void Renderer::Destructor_OPENGL()
    {
        delete static_cast<OPENGLRendererImpl*>(m_impl);
        m_impl = nullptr;

        CGL_LOG(Renderer, Info, "OPENGL Renderer Destroyed");
    }

    OPENGLRendererImpl* Renderer::GetImpl() const
    {
        assert(GetAPI() == RHIType::OpenGL);
        return static_cast<OPENGLRendererImpl*>(m_impl);
    }

    void Renderer::BeginFrame_OPENGL()
    {
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
    }
    
    void Renderer::EndFrame_OPENGL()
    { 
        GetImpl()->SwapWindow();
    }

    void Renderer::Resize_OPENGL(u32 width, u32 height)
	{
	    glViewport(0, 0, width, height);
	}

    void Renderer::SetPrimitiveTopology_OPENGL(PrimitiveType topology)
    {
        assert(GetImpl());
    }

    void Renderer::SetVertexShader_OPENGL(const VertexShader& shader)
    {
        assert(GetImpl());
    }

    void Renderer::SetPixelShader_OPENGL(const PixelShader& shader)
    {
        assert(GetImpl() );
    }

    void Renderer::SetVertexBuffer_OPENGL(const VertexBuffer& buffer)
    {
        assert(GetImpl());
        
    }

    void Renderer::SetIndexBuffer_OPENGL(const IndexBuffer& buffer)
    {
        assert(GetImpl());
    }

    ShaderCompileResult Renderer::CompileVertexShader_OPENGL(const ShaderSource& source, VertexShader* outShader)
    {
        assert(GetImpl() && outShader);

        CompileConfig cfg{};
        cfg.EntryPoint = "main";
#ifdef CGL_BUILD_DEBUG
        cfg.Debug = true;
        cfg.Optimize = false;
#endif

        ShaderCompileResult result = ShaderCompiler::Compile(source, cfg, outShader->vertexShader);
        if (result.Status != ShaderCompileStatus::Failure)
        {
            assert(outShader->vertexShader);
        }

        return result;
    }

    ShaderCompileResult Renderer::CompilePixelShader_OPENGL(const ShaderSource& source, PixelShader* outShader)
    {
        assert(GetImpl() && outShader);

        CompileConfig cfg{};
        cfg.EntryPoint = "main";
#ifdef CGL_BUILD_DEBUG
        cfg.Debug = true;
        cfg.Optimize = false;
#endif

        ShaderCompileResult result = ShaderCompiler::Compile(source, cfg, outShader->fragmentShader);
        if (result.Status != ShaderCompileStatus::Failure)
        {
            assert(outShader->fragmentShader);
        }

        return result;
    }

    void Renderer::LinkShaders_OPENGL(Material* material)
    {
        material->m_id = glCreateProgram();
        glAttachShader(material->m_id, material->GetVertexShader()->Shader.vertexShader);
        glAttachShader(material->m_id, material->GetPixelShader()->Shader.fragmentShader);
        glLinkProgram(material->m_id);

        GLint success;
        char infoLog[512];
        glGetProgramiv(material->m_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(material->m_id, 512, NULL, infoLog);
            CGL_LOG(Renderer, Error, "Failed to link shaders");
        }
        else
        {
            glDeleteShader(material->GetVertexShader()->Shader.vertexShader);
            glDeleteShader(material->GetPixelShader()->Shader.fragmentShader);
        }

    }

    VertexBuffer Renderer::CreateVertexBuffer_OPENGL(const BufferSource& source)
    {
        assert(source.Type == BufferType::Vertex);
        assert(GetImpl());

        VertexBuffer vb;
        glGenVertexArrays(1, &vb.VAO);
        glGenBuffers(1, &vb.VBO);
        glBindVertexArray(vb.VAO);

        glBindBuffer(GL_ARRAY_BUFFER, vb.VBO);
        glBufferData(GL_ARRAY_BUFFER, source.TypeSize, source.Data, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return vb;
    }

    IndexBuffer Renderer::CreateIndexBuffer_OPENGL(const BufferSource& source)
    {

    }

    void Renderer::Draw_OPENGL(u32 vertexCount, u32 startVertex)
    {
        assert(GetImpl());
        
    }

    void Renderer::DrawIndexed_OPENGL(u32 indexCount, u32 startIndex, u32 baseVertex)
    {
        assert(GetImpl());
    }


    #endif // CGL_RHI_OPENGL
}