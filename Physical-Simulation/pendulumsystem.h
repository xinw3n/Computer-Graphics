#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H

#include <vector>

#include "particlesystem.h"

class PendulumSystem : public ParticleSystem
{
public:
    PendulumSystem();

    std::vector<Vector3f> evalF(std::vector<Vector3f> state) override;
    void draw(GLProgram&);
    
    std::vector<Vector3f> getPos(std::vector<Vector3f> state);
    std::vector<Vector3f> getVelocity(std::vector<Vector3f> state);
    

    // inherits 
    // std::vector<Vector3f> m_vVecState;
private:
    // springRep[i] stores the vector of particles that are connected to particle i
    std::vector<std::vector<std::tuple<unsigned, float, float>>> springRep;
    std::vector<float> masses;
    const Vector3f g = Vector3f(0, -1, 0);
    float d; // drag constant
};

#endif
