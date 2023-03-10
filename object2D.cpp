#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float hight,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, hight, 0), color),
        VertexFormat(corner + glm::vec3(length, hight, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 3, 2 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        rectangle->SetDrawMode(GL_TRIANGLE_FAN);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}


Mesh* object2D::CreateTriangle(const std::string& name,
    glm::vec3 a, 
    glm::vec3 b, 
    glm::vec3 c,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(a, color),
        VertexFormat(b, color),
        VertexFormat(c, color),
        
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2};

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(0);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateCircle(const std::string& name,
    float x,
    float y,
    float radius,
    glm::vec3 color,
    bool fill)
{
    Mesh* circle = new Mesh(name);
    std::vector<VertexFormat> vertices = {};
    std::vector<unsigned int> indices = {};
    int nrTriangles = 50;
    float PI = 3.14159265359;
    float twoPI = 2.0f * PI;

    for (int i = 0; i <= nrTriangles; i++) {
        indices.push_back(i);
        vertices.push_back(VertexFormat(glm::vec3(x + (radius * cos(i * twoPI / nrTriangles)), y + (radius * sin(i * twoPI / nrTriangles)), 0), color));
    }

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        circle->SetDrawMode(GL_TRIANGLE_FAN);
    }
    circle->InitFromData(vertices, indices);
    return circle;
}


