#pragma once

namespace engine {
    class TimeManager {
    public:
        double getDeltaTime() { return m_deltaTime; }
        void setDeltaTime(double deltaTime) { m_deltaTime = deltaTime; }
    private:
        double m_deltaTime;
    };

}