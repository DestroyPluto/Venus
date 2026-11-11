#pragma once
#include <cstdint>
#include <vector>

namespace rendering {
    class Geometry {
    public:
        Geometry(uint32_t globalID);
        void addAttribute(uint32_t index, std::vector<float> attribData, uint32_t components);
        void drawGeometry();
    private:
        uint32_t m_globalID;
        uint32_t m_vaoID;
        uint32_t m_vertexCount;
    };
}