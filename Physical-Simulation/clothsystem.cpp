#include "clothsystem.h"
#include "camera.h"
#include "vertexrecorder.h"
#include <iostream>


 // your system should at least contain 8x8 particles.
const int W = 8;
const int H = 8;

ClothSystem::ClothSystem()
{
    // TODO 5. Initialize m_vVecState with cloth particles. 
    // You can again use rand_uniform(lo, hi) to make things a bit more interesting
    
    // init variables
    // width of the cloth n --> total num of particles n x n
    d = 0.5; // drag
    k = 8; // spring
    float restStr = 0.4; // resting length for structural springs
    float restShear = 0.5; // resting length for shear springs
    float restFlex = 0.8; // resting length for flex springs
    
    for (unsigned j = 0; j < H; j++){
        for (unsigned i = 0; i < W; i++){
            masses.push_back(0.8);
            
            Vector3f pos = Vector3f(-3+0.5*i, 3-0.5*j, 0);
            
            m_vVecState.push_back(pos);
            m_vVecState.push_back(Vector3f(0,0,0));
            
//            // TODO: clean up spring code to be more readable
//            // structural springs
//            std::vector<std::tuple<int, int>> offset;
//            offset.push_back(std::make_tuple(-1, 0));
//            offset.push_back(std::make_tuple(1, 0));
//            offset.push_back(std::make_tuple(0, -1));
//            offset.push_back(std::make_tuple(0, 1));
            std::vector<std::vector<float>> connected;
//
//            std::cout<< "node"<< "," << i << "," << j << std::endl;
//            for (unsigned k = 0; k < offset.size(); k++){
//                int dr = std::get<0>(offset[k]);
//                int dc = std::get<1>(offset[k]);
//

//                if ((dr+int(i) > -1 and dr+int(i) < H) and (dc+int(j) > -1 and dc+int(j) < W)){
////                    std::cout<< unsigned(dc+int(i))<< "," << unsigned(dr+int(j)) << std::endl;
//
//                    unsigned index = indexOf(unsigned(dr+int(i)), unsigned(dc+int(j)), W);
//                    std::cout<< index << std::endl;
//                    connected.push_back(std::make_tuple(index, rest, k));
//                }
//            }
            // structural springs
            if (i > 0){
                unsigned index = indexOf(i-1, j, W);
                connected.push_back({float(index), restStr, k});
            }
            if (i+1 < W) {
                unsigned index = indexOf(i+1, j, W);
                connected.push_back({float(index), restStr, k});
            }
            if (j > 0) {
                unsigned index = indexOf(i, j-1, W);
                connected.push_back({float(index), restStr, k});
            }
            if (j+1 < H) {
                unsigned index = indexOf(i, j+1, W);
                connected.push_back({float(index), restStr, k});
            }
            
            // shear springs
            if (i > 0 and j > 0){
                unsigned index = indexOf(i-1, j-1, W);
                connected.push_back({float(index), restShear, k});
            }
            if (i+1 < W and j > 0) {
                unsigned index = indexOf(i+1, j-1, W);
                connected.push_back({float(index), restShear, k});
            }
            if (i > 0 and j+1 < H) {
                unsigned index = indexOf(i-1, j+1, W);
                connected.push_back({float(index), restShear, k});
            }
            
            if (i+1 < W and j+1 < H) {
                unsigned index = indexOf(i+1, j+1, W);
                connected.push_back({float(index), restShear, k});
            }
            
            // flex springs
            if (i > 1){
                unsigned index = indexOf(i-2, j, W);
                connected.push_back({float(index), restFlex, k});
            }
            if (i+2 < W) {
                unsigned index = indexOf(i+2, j, W);
                connected.push_back({float(index), restFlex, k});
            }
            if (j > 1) {
                unsigned index = indexOf(i, j-2, W);
                connected.push_back({float(index), restFlex, k});
            }
            if (j+2 < H) {
                unsigned index = indexOf(i, j+2, W);
                connected.push_back({float(index), restFlex, k});
            }
            springRep.push_back(connected);
        }
    }
    
}

unsigned ClothSystem::indexOf(unsigned i, unsigned j, int W)
{
    return int(j)*W+int(i);
}

std::vector<Vector3f> ClothSystem::evalF(std::vector<Vector3f> state)
{
    std::vector<Vector3f> f;
    std::vector<Vector3f> pos = getPos(state);
    std::vector<Vector3f> velocity = getVelocity(state);
    
    for (unsigned i=0; i<pos.size(); i++){
        // derivative of pos is velocity
        f.push_back(velocity[i]);
        
        // derivative of velocity is sum of all forces (gravity + drag + springs)
        // - gravity
        Vector3f gravity = masses[i]*g;
        // - viscous drag
        Vector3f drag = -d * velocity[i];
        Vector3f spring = Vector3f(0);
        // - structural springs
        for (unsigned j=0; j<springRep[i].size(); j++){
            unsigned k = unsigned(springRep[i][j][0]);
            float restLength = springRep[i][j][1];
            float springConstant = springRep[i][j][2];
            Vector3f diff = pos[i]-pos[k];
            spring += -springConstant * (diff.abs()-restLength) * diff.normalized();
        }
        Vector3f forces = gravity + drag + spring;
        f.push_back(forces/masses[i]);
    }
    
    // - shear springs
    // - flexion springs
    
    // fix top left and top right particles
    f[0] *= 0;
    f[1] *= 0;
    unsigned index = indexOf(W-1, 0, W);
    f[index*2] *= 0;
    f[index*2+1] *= 0;
    
    return f;
}

std::vector<Vector3f> ClothSystem::getPos(std::vector<Vector3f> state)
{
    std::vector<Vector3f> pos;
    for (unsigned i=0; i<state.size(); i+=2){
        pos.push_back(state[i]);
        //        std::cout<< state[i][0]<< "," << state[i][1] << "," << state[i][2] << std::endl;
    }
    return pos;
}

std::vector<Vector3f> ClothSystem::getVelocity(std::vector<Vector3f> state)
{
    std::vector<Vector3f> velocity;
    for (unsigned i=1; i<state.size(); i+=2){
        velocity.push_back(state[i]);
    }
    return velocity;
}

void ClothSystem::drawSprings(GLProgram& gl, std::vector<Vector3f> pos, Vector3f CLOTH_COLOR)
{
    gl.disableLighting();
    gl.updateModelMatrix(Matrix4f::identity()); // update uniforms after mode change
    VertexRecorder rec;
    for (unsigned i=0; i<pos.size(); i++){
        Vector3f first = pos[i];
        std::vector<std::vector<float>> connected = springRep[i];
        for (unsigned j=0; j<connected.size(); j++){
            unsigned k = unsigned(connected[j][0]);
            Vector3f second = pos[k];
            rec.record(first, CLOTH_COLOR);
            rec.record(second, CLOTH_COLOR);
        }
    }
    glLineWidth(3.0f);
    rec.draw(GL_LINES);
    gl.enableLighting(); // reset to default lighting model
}

void ClothSystem::drawNodes(GLProgram& gl, std::vector<Vector3f> pos)
{
    
    for (unsigned i=0; i<pos.size(); i++){
        Vector3f p = pos[i];
        gl.updateModelMatrix(Matrix4f::translation(p));
        drawSphere(0.04f, 8, 8);
    }
}


void ClothSystem::draw(GLProgram& gl)
{
    //TODO 5: render the system 
    //         - ie draw the particles as little spheres
    //         - or draw the springs as little lines or cylinders
    //         - or draw wireframe mesh
    std::vector<Vector3f> pos = getPos(m_vVecState);
    
    const Vector3f CLOTH_COLOR(0.9f, 0.9f, 0.9f);
    gl.updateMaterial(CLOTH_COLOR);
    // draw nodes
    drawNodes(gl, pos);
    // draw springs
    drawSprings(gl, pos, CLOTH_COLOR);
    
    
    
    // EXAMPLE for how to render cloth particles.
    //  - you should replace this code.
    float w = 0.2f;
    Vector3f O(0.4f, 1, 0);
    gl.updateModelMatrix(Matrix4f::translation(O));
    drawSphere(0.04f, 8, 8);
    gl.updateModelMatrix(Matrix4f::translation(O + Vector3f(w, 0, 0)));
    drawSphere(0.04f, 8, 8);
    gl.updateModelMatrix(Matrix4f::translation(O + Vector3f(w, -w, 0)));
    drawSphere(0.04f, 8, 8);
    gl.updateModelMatrix(Matrix4f::translation(O + Vector3f(0, -w, 0)));
    drawSphere(0.04f, 8, 8);

    // EXAMPLE: This shows you how to render lines to debug the spring system.
    //
    //          You should replace this code.
    //
    //          Since lines don't have a clearly defined normal, we can't use
    //          a regular lighting model.
    //          GLprogram has a "color only" mode, where illumination
    //          is disabled, and you specify color directly as vertex attribute.
    //          Note: enableLighting/disableLighting invalidates uniforms,
    //          so you'll have to update the transformation/material parameters
    //          after a mode change.
    gl.disableLighting();
    gl.updateModelMatrix(Matrix4f::identity()); // update uniforms after mode change
    VertexRecorder rec;
    rec.record(O, CLOTH_COLOR);
    rec.record(O + Vector3f(w, 0, 0), CLOTH_COLOR);
    
    rec.record(O, CLOTH_COLOR);
    rec.record(O + Vector3f(0, -w, 0), CLOTH_COLOR);

    rec.record(O + Vector3f(w, 0, 0), CLOTH_COLOR);
    rec.record(O + Vector3f(w, -w, 0), CLOTH_COLOR);

    rec.record(O + Vector3f(0, -w, 0), CLOTH_COLOR);
    rec.record(O + Vector3f(w, -w, 0), CLOTH_COLOR);
    glLineWidth(3.0f);
    rec.draw(GL_LINES);

    gl.enableLighting(); // reset to default lighting model
    // EXAMPLE END
}

