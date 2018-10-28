#include "timestepper.h"

#include <cstdio>
#include <vector>
#include <vecmath.h>

void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
   //TODO: See handout 3.1
    std::vector<Vector3f> current = particleSystem->getState();
    std::vector<Vector3f> derivative = particleSystem->evalF(current);
    std::vector<Vector3f> result;
    for (unsigned i=0; i<current.size(); i++){
        Vector3f v = current[i] + stepSize*derivative[i];
        result.push_back(v);
    }
    particleSystem->setState(result);
}

void Trapezoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
   //TODO: See handout 3.1
    std::vector<Vector3f> current = particleSystem->getState();
    std::vector<Vector3f> f0 = particleSystem->evalF(current);
    std::vector<Vector3f> newState;
    for (unsigned i=0; i<current.size(); i++){
        Vector3f v = current[i] + stepSize*f0[i];
        newState.push_back(v);
    }
    std::vector<Vector3f> f1 = particleSystem->evalF(newState);
    std::vector<Vector3f> result;
    for (unsigned i=0; i<current.size(); i++){
        Vector3f v = current[i] + (stepSize/2.0)*(f0[i]+f1[i]);
        result.push_back(v);
    }
    particleSystem->setState(result);
}


void RK4::takeStep(ParticleSystem* particleSystem, float stepSize)
{
    std::vector<Vector3f> current = particleSystem->getState();
    std::vector<Vector3f> k1 = particleSystem->evalF(current);
    
    std::vector<Vector3f> newState1;
    for (unsigned i=0; i<current.size(); i++){
        Vector3f v = current[i] + stepSize/2.0*k1[i];
        newState1.push_back(v);}
    std::vector<Vector3f> k2 = particleSystem->evalF(newState1);
    
    std::vector<Vector3f> newState2;
    for (unsigned i=0; i<current.size(); i++){
        Vector3f v = current[i] + stepSize/2.0*k2[i];
        newState2.push_back(v);}
    std::vector<Vector3f> k3 = particleSystem->evalF(newState2);
    
    std::vector<Vector3f> newState3;
    for (unsigned i=0; i<current.size(); i++){
        Vector3f v = current[i] + stepSize*k3[i];
        newState3.push_back(v);}
    std::vector<Vector3f> k4 = particleSystem->evalF(newState3);
    
    std::vector<Vector3f> result;
    for (unsigned i=0; i<current.size(); i++){
        Vector3f v = current[i] + (k1[i]+k2[i]*2.0+k3[i]*2.0+k4[i])*(stepSize/6.0);
        result.push_back(v);}
    particleSystem->setState(result);
    
}

