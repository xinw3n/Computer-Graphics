#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include <vector>

#include "particlesystem.h"

class ClothSystem : public ParticleSystem
{
    ///ADD MORE FUNCTION AND FIELDS HERE
public:
    ClothSystem();

    // evalF is called by the integrator at least once per time step
    std::vector<Vector3f> evalF(std::vector<Vector3f> state) override;

    // given a particle's position (i, j) in the grid, finds a particle's index in the linear vector
    unsigned indexOf(unsigned i, unsigned j, int sideLength);
    
    // get position and velocity from state 
    std::vector<Vector3f> getPos(std::vector<Vector3f> state);
    std::vector<Vector3f> getVelocity(std::vector<Vector3f> state);
    
    // draw is called once per frame
    void draw(GLProgram& ctx);
    void drawNodes(GLProgram& gl, std::vector<Vector3f> pos);
    void drawSprings(GLProgram& gl, std::vector<Vector3f> pos, Vector3f CLOTH_COLOR);

    // inherits
    // std::vector<Vector3f> m_vVecState;
    
private:
    // springRep[i] stores the vector of particles that are connected to particle i
    std::vector<std::vector<std::vector<float>>> springRep;
    std::vector<float> masses;
    const Vector3f g = Vector3f(0, -0.5, 0);
    float d; // drag constant
    float k; // spring constant
};


#endif
