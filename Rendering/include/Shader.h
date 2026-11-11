#pragma once
#include <cstdint>

namespace rendering {
    class Shader
    {
    public:
        Shader(const char* vertFilePath, const char* fragFilePath);
        void Bind();
        void Unbind();

    private:
        uint32_t m_id;
    };
}