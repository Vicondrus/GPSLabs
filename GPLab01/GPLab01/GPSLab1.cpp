//
//  GPSLab1.cpp
//
//  Copyright © 2017 CGIS. All rights reserved.
//

#include "GPSLab1.hpp"

namespace gps {
    glm::vec4 TransformPoint(const glm::vec4 &point)
	{

		glm::vec4 newVector(point.x + 2.0f, point.y, point.z + 1.0f, point.w);
		glm::mat4 matrix(1.0f);
		matrix = glm::rotate(matrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        return matrix*newVector;
    }
    
    float ComputeAngle(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return glm::degrees(glm::acos(glm::dot(v1,v2)/(glm::length(v1)*glm::length(v2))));
    }
    
    bool IsConvex(const std::vector<glm::vec2> &vertices)
    {
		glm::vec3 normal = glm::cross(glm::vec3(vertices.at(1) - vertices.at(0), 0.0f), glm::vec3(vertices.at(2) - vertices.at(1), 0.0f));
		for (int i = 0; i < vertices.size(); i++) {
			glm::vec3 edge1(vertices.at((i + 1)% vertices.size()) - vertices.at(i), 0.0f);
			glm::vec3 edge2(vertices.at((i + 2)% vertices.size()) - vertices.at((i + 1)% vertices.size()), 0.0f);
			if (glm::dot(glm::cross(edge1, edge2),normal) < 0.0f)
				return false;
		}
        return true;
    }
    
    std::vector<glm::vec2> ComputeNormals(const std::vector<glm::vec2> &vertices)
    {
        std::vector<glm::vec2> normalsList;
		glm::vec3 normal(0.0f,0.0f,1.0f);
		for (int i = 0; i < vertices.size(); i++) {
			glm::vec3 edge1(vertices.at((i + 1) % vertices.size()) - vertices.at(i), 0.0f);
			normalsList.push_back(glm::normalize(glm::vec2(glm::cross(edge1,normal))));
		}
        return normalsList;
    }
}
