#pragma once
#include "core.h"
#include <iostream>
using namespace std;

class Particle
{
public:
    bool onGround = false;
    float mass = 10.0;
    glm::vec3 position = glm::vec3(0,-1.95,0); 
    glm::vec3 normal = glm::vec3(0);
    glm::vec3 velocity = glm::vec3(0);
    glm::vec3 force = glm::vec3(0,0,0);
    float radius = 7.0;
    float lifespan = 12.0;


    void applyForce(glm::vec3 &f) {
        force += f;

        
         
    }
    void integrate(float deltaTime) {

        glm::vec3 accel = (1/mass) * force;
        velocity += accel * deltaTime;
        position += velocity * deltaTime;
        force = glm::vec3(0,0,0);
    }

    void ApplyImpulse(const glm::vec3& imp) {velocity+=(imp * (1/mass));}
    
};

