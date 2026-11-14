#pragma once
#include <cstdint>

namespace rendering {
    class Shader
    {
    public:
        Shader(const char* vertFilePath, const char* fragFilePath);
        void Bind();
        void Unbind();

        template <typename T>
        void setUniform(const char*, T value) const;

    private:
        uint32_t m_id;
    };
}