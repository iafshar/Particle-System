#pragma once

#include "Particle.h"
#include "Cube.h"
#include <vector>
using namespace std;

class System
{
private:
    GLuint VAO;
    GLuint VBO_positions, EBO;

    std::vector<glm::vec3> positions; // How?
    std::vector<unsigned int> indices;

    glm::vec3 color = glm::vec3(1.0,0,0); //red
    
public:
    float pLifespan = 8.0;
    float pRadius = 7.0;
    float airDensity = 1.225;
    float dragC = 0.6;
    float restitutionC = 0.8;
    float fdynC = 0.3;
    float g = -9.8;
    int creationRate = 10; // higher means less particles

    float lifespanVariance = 2.0;

    float positionVarianceX = 0.1;
    float positionVarianceY = 0.1;
    float positionVarianceZ = 0.1;

    float velocityVarianceX = 2.0;
    float velocityVarianceY = 2.0;
    float velocityVarianceZ = 2.0;

    
    std::vector<Particle*> particles;
    glm::vec3 vAir = glm::vec3(0,0,0.1);
    glm::vec3 initialV = glm::vec3(5,10,0);
    glm::vec3 position = glm::vec3(0,-2,0);

    void shootParticle(bool on, int& count);
    void update(); // apply rest of forces
    void draw(const glm::mat4& viewProjMtx, GLuint shader);
    ~System();
};

