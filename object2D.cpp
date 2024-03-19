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

Mesh* object2D::CreateRectangular(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float height,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(height, 0, 0), color),
        VertexFormat(corner + glm::vec3(height, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateRomb(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length1,
    float length2,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length1, 0, 1), color),
        VertexFormat(corner + glm::vec3(length1/2, length2, 1), color),
        VertexFormat(corner + glm::vec3(length1/2, -length2, 1), color),
        VertexFormat(corner + glm::vec3(length1/2 - 10, length2/2 - 5, 1), color),
        VertexFormat(corner + glm::vec3(length1/2 - 10, -length2/2 + 5, 1), color),
        VertexFormat(corner + glm::vec3(length1 + 30, length2/2 - 5, 1), color),
        VertexFormat(corner + glm::vec3(length1 + 30, -length2/2 + 5, 1), color),
    };

    Mesh* romb = new Mesh(name);
    std::vector<unsigned int> indices = 
    { 
        0, 1, 2, 
        0, 3, 1,
        4, 5, 6,
        5, 7, 6
   
    };

    if (!fill) {
        romb->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    romb->InitFromData(vertices, indices);
    return romb;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(-5, 0, 7), color),//0
        VertexFormat(corner + glm::vec3(length + 5, 0, 7), color),//1
        VertexFormat(corner + glm::vec3(length/3, 0, 7), color),//2
        VertexFormat(corner + glm::vec3(2*length/3, 0, 7), color),//3
        VertexFormat(corner + glm::vec3(length/2, length/2, 7), color),//4

        VertexFormat(corner + glm::vec3(length/3, -length/3, 7), color),//5
        VertexFormat(corner + glm::vec3(2*length/3, -length/3, 7), color),//6

        VertexFormat(corner + glm::vec3(length/3 -10, -length +5, 7), color),//7
        VertexFormat(corner + glm::vec3(2*length/3 + 10, -length +5, 7), color),//8

        VertexFormat(corner + glm::vec3(length/2, -length/2, 7), color),//9
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        2, 3, 4,
        0, 2, 5,
        3, 1, 6,
        5, 7, 9,
        6, 8, 9,
        3, 0, 8,
        7, 1, 2
    };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    star->InitFromData(vertices, indices);

    return star;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    float length2 = length - 10;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 3), color1),//0
        VertexFormat(corner + glm::vec3(2 * length, 0, 3), color1),//1
        VertexFormat(corner + glm::vec3(length/2, length * 0.86, 3), color1),//2
        VertexFormat(corner + glm::vec3(length/2 + length, length * 0.86, 3), color1),//3
        VertexFormat(corner + glm::vec3(length, 0, 3), color1),//4
        VertexFormat(corner + glm::vec3(length/2, -length * 0.86, 3), color1),//5
        VertexFormat(corner + glm::vec3(length + length / 2, -length * 0.86, 3), color1),//6
        VertexFormat(corner + glm::vec3(length - length2, 0, 4), color2),//7
        VertexFormat(corner + glm::vec3(length+length2, 0, 4), color2),//8
        VertexFormat(corner + glm::vec3(length2 / 2 + length - length2, length2 * 0.86, 4), color2),//9
        VertexFormat(corner + glm::vec3(length, 0, 4), color2),//10
        VertexFormat(corner + glm::vec3(length + length2/2, length2 * 0.86, 4), color2),//11    
        VertexFormat(corner + glm::vec3(length2 / 2 + length - length2, -length2 * 0.86, 4), color2),//12
        VertexFormat(corner + glm::vec3(length + length2 / 2, -length2 * 0.86, 4), color2),//13


    };

    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices =
    {
       0,2,4,
       2,4,3,
       4,3,1,
       0,5,4,
       5,4,6,
       6,4,1,
       7,10,9,
   	   10,9,11,
       8,10,11,
       12,7,10,
       12,13,10,
       13,10,8
    };

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}
