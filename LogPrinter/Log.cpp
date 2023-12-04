#include "Log.h"

std::ostream& operator<<(std::ostream& output, const glm::vec3& D)
{
    output << "X=" << D.x << " Y=" << D.y << " Z=" << D.z;
    return output;
}

std::ostream& operator<<(std::ostream& output, const std::chrono::microseconds& D)
{
    const auto end = D.count();
    output << end;
    return output;
}
