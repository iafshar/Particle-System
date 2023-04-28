#include "System.h"
#include <iostream>
#define GL_POINT_SMOOTH 0x0B10

#define GL_POINT_SMOOTH_HINT			0x0C51

// AntTweakBar
// see demo

System::~System() {
    for (size_t i = 0; i < particles.size(); i++)
    {
        delete particles[i];
    }
    
}

void System::shootParticle(bool on, int& count) {
     if (on)
    {
        if (count % creationRate == 0)
        {
            Particle* p = new Particle;
            float l = (float)(rand() % (int)(100 * lifespanVariance))/(float)100;
            p->lifespan = pLifespan + l;
            p->radius = pRadius;

            float x = (float)(rand() % (int)(100 * velocityVarianceX))/(float)100;
            float y = (float)(rand() % (int)(100 * velocityVarianceY))/(float)100;
            float z = (float)(rand() % (int)(100 * velocityVarianceZ))/(float)100;
                
            p->velocity = glm::vec3(initialV.x - x,initialV.y + y,initialV.z + z);

            x = (float)(rand() % (int)(100 * positionVarianceX))/(float)100;
            y = (float)(rand() % (int)(100 * positionVarianceY))/(float)100;
            z = (float)(rand() % (int)(100 * positionVarianceZ))/(float)100;

            p->position = glm::vec3(position.x + x,position.y + y,position.z + z);
            particles.push_back(p);
        }
        count++;
    }
}

void System::update() {
    for (size_t i = 0; i < particles.size(); i++)
    {
        //particles[i]->applyForce(pushForce);
        glm::vec3 gravity = glm::vec3(0,g,0) * particles[i]->mass;
        particles[i]->applyForce(gravity);

        glm::vec3 V = particles[i]->velocity - vAir;
        glm::vec3 e = -glm::normalize(V);
        float a = M_PI * particles[i]->radius * particles[i]->radius;

        glm::vec3 drag = 0.5f * airDensity * (glm::length(V) * glm::length(V)) * dragC * a * e;
        particles[i]->applyForce(drag);
        
    }

    for (size_t i = 0; i < particles.size(); i++)
    {

        if (particles[i]->lifespan > 0)
        {
            for (int k = 0; k < 10; k++) 
            {
                particles[i]->integrate(0.0005);
                particles[i]->lifespan -= 0.0005;
            }
            if (particles[i]->position.y <= -2)
            {
                glm::vec3 n = glm::vec3(0,1,0);
                float vclose = glm::dot(particles[i]->velocity, n);
                glm::vec3 imp = -(1 + restitutionC) * particles[i]->mass * vclose * n;

                particles[i]->ApplyImpulse(imp);

                glm::vec3 vnorm = (glm::dot(particles[i]->velocity,n)) * n;
                glm::vec3 vtan = particles[i]->velocity - vnorm;

                glm::vec3 impFric = -vtan * fdynC * glm::length(imp);
                // put a cap so vtan doesnt change direction
                if (glm::length(impFric) > glm::length(vtan))
                {
                    impFric = -vtan;
                }
                

                particles[i]->ApplyImpulse(impFric);

            }
            
        }
        else
        {
            particles.erase(particles.begin() + i);
            i--;
        } 
        
    }

    positions.clear();
    indices.clear();

    for (size_t i = 0; i < particles.size(); i++)
    {
        positions.push_back(particles[i]->position);
        indices.push_back(i);
    }
    

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_positions);
    // glGenBuffers(1, &VBO_normals);

    // Bind to the VAO.
    glBindVertexArray(VAO);

    // Bind to the first VBO - We will use it to store the vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), positions.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Generate EBO, bind the EBO to the bound VAO and send the data
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    // Unbind the VBOs.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

void System::draw(const glm::mat4& viewProjMtx, GLuint shader) {
    glm::mat4 model = glm::mat4(1.0f);
    glUseProgram(shader);

    // get the locations and send the uniforms to the shader
    glUniformMatrix4fv(glGetUniformLocation(shader, "viewProj"), 1, false, (float*)&viewProjMtx);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float*)&model);
    glUniform3fv(glGetUniformLocation(shader, "DiffuseColor"), 1, &color[0]);

    // Bind the VAO
    glBindVertexArray(VAO);
    
    // glEnable( GL_POINT_SPRITE ); // GL_POINT_SPRITE_ARB if you're
                                 // using the functionality as an extension.


    

    // glEnable(GL_PROGRAM_POINT_SIZE);
   // glColorMask(1.0, 1.0, 1.0, 0.9);
    // glColor4f(1.0, 1.0, 1.0, 0.9); // white points with alpha < 1.0
    // glEnable(GL_POINT_SMOOTH);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);

    glPointSize(pRadius * 2);
    // draw the points using points, indexed with the EBO
    glDrawArrays(GL_POINTS,0,indices.size());

    // glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
    
}