#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float length, float hight, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangle(const std::string& name,glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string& name, float x, float y, float radius, glm::vec3 color, bool fill = false);
}
