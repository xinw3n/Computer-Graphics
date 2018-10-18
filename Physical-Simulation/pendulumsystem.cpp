#include "pendulumsystem.h"
#include <iostream>
#include <cassert>
#include "camera.h"
#include "vertexrecorder.h"

// TODO adjust to number of particles.
const int NUM_PARTICLES = 4;

PendulumSystem::PendulumSystem()
{

    // 4.2 Add particles for simple pendulum
    d = 0.5;
    
    // even index position, odd index velocity
    m_vVecState.push_back(Vector3f(1,3,0));
    m_vVecState.push_back(Vector3f(0,0,0));
//    m_vVecState.push_back(Vector3f(1,0,0));
//    m_vVecState.push_back(Vector3f(0,0,0));
    
    // masses
    masses.push_back(1);
    // spring
    std::vector<std::tuple<unsigned, float, float>> connectedToFirst;
    connectedToFirst.push_back(std::make_tuple(1, 0.1, 1.3));
    springRep.push_back(connectedToFirst);
    
    // TODO 4.3 Extend to multiple particles
    for (unsigned i=1; i<4; i++){
        float random = rand_uniform(-0.5f, 0.5f);
        Vector3f pos = Vector3f(1,0,0);
        pos[1] = random;
        m_vVecState.push_back(pos);
        m_vVecState.push_back(Vector3f(0,0,0));
        masses.push_back(1);
        
        std::vector<std::tuple<unsigned, float, float>> connected;
        connected.push_back(std::make_tuple(i-1, 0.1, 1.3));
        if(i+1 < 4){
            connected.push_back(std::make_tuple(i+1, 0.1, 1.3));
        }
        springRep.push_back(connected);
    }
    
    
    
    
    // To add a bit of randomness, use e.g.
    // float f = rand_uniform(-0.5f, 0.5f);
    // in your initial conditions.
}


std::vector<Vector3f> PendulumSystem::evalF(std::vector<Vector3f> state)
{
    // TODO 4.1: implement evalF
    //  - gravity
    //  - viscous drag
    //  - springs
    std::vector<Vector3f> f;
    std::vector<Vector3f> pos = getPos(state);
    std::vector<Vector3f> velocity = getVelocity(state);
    
    for (unsigned i=0; i<pos.size(); i++){
        // derivative of pos is velocity
        f.push_back(velocity[i]);
        // derivative of velocity is sum of all forces (gravity + drag + springs)
        Vector3f gravity = masses[i]*g;
        Vector3f drag = -d * velocity[i];
        Vector3f spring = Vector3f(0);
        for (unsigned j=0; j<springRep[i].size(); j++){
            unsigned k = std::get<0>(springRep[i][j]);
            float restLength = std::get<1>(springRep[i][j]);
            float springConstant = std::get<2>(springRep[i][j]);
            Vector3f diff = pos[i]-pos[k];
            spring += -springConstant * (diff.abs()-restLength) * diff.normalized();
        }
        Vector3f forces = (gravity + drag + spring);
        f.push_back(forces/masses[i]);
    }
    for (unsigned i=0; i<f.size(); i++){
        std::cout<< f[i][0]<< "," << f[i][1] << "," << f[i][2] << std::endl;
    }
    
    // reset the fixed particle
    f[0] *= 0;
    f[1] *= 0;
    
    
    return f;
}

std::vector<Vector3f> PendulumSystem::getPos(std::vector<Vector3f> state)
{
    std::vector<Vector3f> pos;
    for (unsigned i=0; i<state.size(); i+=2){
        pos.push_back(state[i]);
//        std::cout<< state[i][0]<< "," << state[i][1] << "," << state[i][2] << std::endl;
    }
    return pos;
}

std::vector<Vector3f> PendulumSystem::getVelocity(std::vector<Vector3f> state)
{
    std::vector<Vector3f> velocity;
    for (unsigned i=1; i<state.size(); i+=2){
        velocity.push_back(state[i]);
    }
    return velocity;
}

// render the system (ie draw the particles)
void PendulumSystem::draw(GLProgram& gl)
{
    const Vector3f PENDULUM_COLOR(0.73f, 0.0f, 0.83f);
    gl.updateMaterial(PENDULUM_COLOR);

    // TODO 4.2, 4.3
    std::vector<Vector3f> pos = getPos(m_vVecState);
    for (unsigned i=0; i<pos.size(); i++){
        Vector3f p = pos[i];
        gl.updateModelMatrix(Matrix4f::translation(p));
        drawSphere(0.075f, 10, 10);
    }
    
}
