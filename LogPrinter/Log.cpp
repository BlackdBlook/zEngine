#include "Log.h"
#include "ToolKit/QuaternionUtils/QuaternionUtils.h"
std::ostream& operator<<(std::ostream& output, const glm::vec3& D)
{
    output << "X=" << D.x << " Y=" << D.y << " Z=" << D.z;
    return output;
}

std::ostream& operator<<(std::ostream& output, const glm::vec4& D)
{
    output << "X=" << D.x << " Y=" << D.y << " Z=" << D.z << " W=" << D.w ;
    return output;
}

std::ostream& operator<<(std::ostream& output, const glm::mat4& D)
{
    output << '\n' << D[0] << '\n' << D[1] << '\n' << D[2] << '\n' << D[3] << '\n';
    return output;
}

std::ostream& operator<<(std::ostream& output, const std::chrono::microseconds& D)
{
    const auto end = D.count();
    output << end;
    return output;
}

std::ostream& operator<<(std::ostream& output, const glm::quat& D)
{
    const glm::vec3 v = glm::degrees(QuaternionUtils::eulerAnglesFromQuat(D));
    output << v;
    return output;
}

std::ostream& operator<<(std::ostream& output, const std::vector<std::string>& D)
{
    for(auto& s : D)
    {
        output << s << " ";
    }
    return output;
}
