//
//  Camera.hpp
//
//  Created by CGIS on 28/10/2016.
//  Copyright © 2016 CGIS. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace gps {
    
    enum MOVE_DIRECTION {MOVE_FORWARD, MOVE_BACKWARD, MOVE_RIGHT, MOVE_LEFT};
    
    class Camera
    {
    public:
        //Camera constructor
        Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget);
        //return the view matrix, using glm::lookAt
        glm::mat4 getViewMatrix();
        //update the camera parameters
        void move(MOVE_DIRECTION direction, float speed);
        //yaw - rotate around y axis
        //pitch - rotate around x axis
        void rotate(float pitch, float yaw);
        
    private:
        glm::vec3 cameraPosition;
        glm::vec3 cameraTarget;
        glm::vec3 cameraDirection;
        glm::vec3 cameraRightDirection;
    };
    
}

#endif /* Camera_hpp */
