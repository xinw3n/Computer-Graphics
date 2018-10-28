#include "skeletalmodel.h"
#include <cassert>

#include "starter2_util.h"
#include "vertexrecorder.h"
#include <fstream>

using namespace std;

SkeletalModel::SkeletalModel() {
    program = compileProgram(c_vertexshader, c_fragmentshader_light);
    if (!program) {
        printf("Cannot compile program\n");
        assert(false);
    }
}

SkeletalModel::~SkeletalModel() {
    // destructor will release memory when SkeletalModel is deleted
    while (m_joints.size()) {
        delete m_joints.back();
        m_joints.pop_back();
    }

    glDeleteProgram(program);
}

void SkeletalModel::load(const char *skeletonFile, const char *meshFile, const char *attachmentsFile)
{
    loadSkeleton(skeletonFile);

    m_mesh.load(meshFile);
    m_mesh.loadAttachments(attachmentsFile, (int)m_joints.size());

    computeBindWorldToJointTransforms();
    updateCurrentJointToWorldTransforms();
}

void SkeletalModel::draw(const Camera& camera, bool skeletonVisible)
{
    // draw() gets called whenever a redraw is required
    // (after an update() occurs, when the camera moves, the window is resized, etc)

    m_matrixStack.clear();

    glUseProgram(program);
    updateShadingUniforms();
    if (skeletonVisible)
    {
        drawJoints(camera);
        drawSkeleton(camera);
    }
    else
    {
        // Tell the mesh to draw itself.
        // Since we transform mesh vertices on the CPU,
        // There is no need to set a Model matrix as uniform
        camera.SetUniforms(program, Matrix4f::identity());
        m_mesh.draw();
    }
    glUseProgram(0);
}

void SkeletalModel::updateShadingUniforms() {
    // UPDATE MATERIAL UNIFORMS
    GLfloat diffColor[] = { 0.4f, 0.4f, 0.4f, 1 };
    GLfloat specColor[] = { 0.9f, 0.9f, 0.9f, 1 };
    GLfloat shininess[] = { 50.0f };
    int loc = glGetUniformLocation(program, "diffColor");
    glUniform4fv(loc, 1, diffColor);
    loc = glGetUniformLocation(program, "specColor");
    glUniform4fv(loc, 1, specColor);
    loc = glGetUniformLocation(program, "shininess");
    glUniform1f(loc, shininess[0]);

    // UPDATE LIGHT UNIFORMS
    GLfloat lightPos[] = { 3.0f, 3.0f, 5.0f, 1.0f };
    loc = glGetUniformLocation(program, "lightPos");
    glUniform4fv(loc, 1, lightPos);

    GLfloat lightDiff[] = { 120.0f, 120.0f, 120.0f, 1.0f };
    loc = glGetUniformLocation(program, "lightDiff");
    glUniform4fv(loc, 1, lightDiff);
}

void SkeletalModel::loadSkeleton(const char* filename)
{
    // Load the skeleton from file here.
    ifstream file(filename);
    float x, y, z;
    int p;
    while(file >> x >> y >> z >> p){
        Matrix4f T = Matrix4f::translation(x,y,z);
        Joint * joint = new Joint;
        joint->transform = T;
        m_joints.push_back(joint);
        if (p == -1){ // root
            m_rootJoint = joint;
            //joint->bindWorldToJointTransform = T;
            //joint->currentJointToWorldTransform = T.inverse();
        } else { // children
            //joint->bindWorldToJointTransform = (m_joints[p]->bindWorldToJointTransform*T);
            //joint->currentJointToWorldTransform = joint->bindWorldToJointTransform.inverse();
            m_joints[p]->children.push_back(joint);
        }
    }
    
    
}

void SkeletalModel::drawJoints(const Camera& camera)
{
    // Draw a sphere at each joint. You will need to add a recursive
    // helper function to traverse the joint hierarchy.
    //
    // We recommend using drawSphere( 0.025f, 12, 12 )
    // to draw a sphere of reasonable size.
    //
    // You should use your MatrixStack class. A function
    // should push it's changes onto the stack, and
    // use stack.pop() to revert the stack to the original
    // state.

    // this is just for illustration:

    // translate from top of stack, but doesn't push, since that's not
    // implemented yet.
    //Matrix4f M = m_matrixStack.top();
//
//    // update transformation uniforms
//    camera.SetUniforms(program, M);
//    // draw
//    drawSphere(0.025f, 12, 12);
//    // pop
    traverseJoints(m_rootJoint, m_matrixStack, camera);
    
}

void SkeletalModel::traverseJoints(Joint* root, MatrixStack& stack, const Camera& camera)
{
    if (root == NULL){
        printf("null");
        return;
    }
    stack.push(root->transform);
    camera.SetUniforms(program, stack.top());
    drawSphere(0.025f, 12, 12);
    
    vector<Joint*> children = root->children;
    for(unsigned i=0; i<children.size(); i++){
        traverseJoints(children[i], stack, camera);
    }
    stack.pop();
}

void SkeletalModel::drawSkeleton(const Camera& camera)
{
    // Draw cylinders between the joints. You will need to add a recursive 
    // helper function to traverse the joint hierarchy.
    //
    // We recommend using drawCylinder(6, 0.02f, <height>);
    // to draw a cylinder of reasonable diameter.

    // you can use the stack with push/pop like this
    // m_matrixStack.push(Matrix4f::translation(+0.6f, +0.5f, -0.5f))
    // camera.SetUniforms(program, m_matrixStack.top());
    // drawCylinder(6, 0.02f, 0.2f);
    // callChildFunction();
    // m_matrixStack.pop();
    traverseSkeleton(m_rootJoint, m_matrixStack, camera);
}

void SkeletalModel::traverseSkeleton(Joint* root, MatrixStack& stack, const Camera& camera)
{
    
    if (root == NULL){
        return;
    }
    
    stack.push(root->transform);
    
    vector<Joint*> children = root->children;
    for(unsigned i=0; i<children.size(); i++){
        Vector3f t = children[i]->transform.getCol(3).xyz(); // translation vector between child and parent
        float length = t.abs();
        
        Vector3f y = t.normalized();
        Vector3f rotatingAxis = Vector3f::cross(Vector3f(0,1,0), y);
        Matrix4f R = Matrix4f::rotation(rotatingAxis,acos(y.y()));
        
        camera.SetUniforms(program, stack.top()*R);
        drawCylinder(6, 0.02f, length);
        traverseSkeleton(children[i], stack, camera);
    }
    stack.pop();
}

void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{
    // Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.
    Joint * joint = m_joints[jointIndex];
    Matrix4f Rx = Matrix4f::rotateX(rX);
    Matrix4f Ry = Matrix4f::rotateY(rY);
    Matrix4f Rz = Matrix4f::rotateZ(rZ);
    Matrix4f Rotation = Rx*Ry*Rz;
    
    Matrix4f current = joint->transform;
    current.setSubmatrix3x3(0,0,Rotation.getSubmatrix3x3(0,0));
    joint->transform = current;
}

void SkeletalModel::computeBindWorldToJointTransforms()
{
    // 2.3.1. Implement this method to compute a per-joint transform from
    // world-space to joint space in the BIND POSE.
    //
    // Note that this needs to be computed only once since there is only
    // a single bind pose.
    //
    // This method should update each joint's bindWorldToJointTransform.
    // You will need to add a recursive helper function to traverse the joint hierarchy.
    traverseBindWorldToJoint(m_rootJoint, m_matrixStack);
}

void SkeletalModel::traverseBindWorldToJoint(Joint* root, MatrixStack& stack)
{
    if (root == NULL){
        return;
    }
    stack.push(root->transform.inverse());
    root->bindWorldToJointTransform = stack.top();
    vector<Joint*> children = root->children;
    for (unsigned i=0; i<children.size(); i++){
        traverseBindWorldToJoint(children[i], stack);
    }
    stack.pop();
}

void SkeletalModel::updateCurrentJointToWorldTransforms()
{
    // 2.3.2. Implement this method to compute a per-joint transform from
    // joint space to world space in the CURRENT POSE.
    //
    // The current pose is defined by the rotations you've applied to the
    // joints and hence needs to be *updated* every time the joint angles change.
    //
    // This method should update each joint's currentJointToWorldTransform.
    // You will need to add a recursive helper function to traverse the joint hierarchy.
    traverseCurrentJointToWorld(m_rootJoint, m_matrixStack);
}

void SkeletalModel::traverseCurrentJointToWorld(Joint* root, MatrixStack& stack){
    if (root == NULL){
        return;
    }
    stack.push(root->transform);
    root->currentJointToWorldTransform = stack.top();
    vector<Joint*> children = root->children;
    for (unsigned i=0; i<children.size(); i++){
        traverseCurrentJointToWorld(children[i], stack);
    }
    stack.pop();
}

void SkeletalModel::updateMesh()
{
    // 2.3.2. This is the core of SSD.
    // Implement this method to update the vertices of the mesh
    // given the current state of the skeleton.
    // You will need both the bind pose world --> joint transforms.
    // and the current joint --> world transforms.
    for (unsigned i = 0; i < m_mesh.currentVertices.size(); i++){
        Vector3f v = m_mesh.bindVertices[i];
        vector<float> w = m_mesh.attachments[i];
        Vector4f updated = Vector4f(0,0,0,0);
        for (unsigned j = 0; j < m_joints.size(); j++){
            Matrix4f bind  = m_joints[j]->bindWorldToJointTransform;
            Matrix4f transform = m_joints[j]->currentJointToWorldTransform;
            updated = updated + w[j] * transform*bind*Vector4f(v,1);
        }
        m_mesh.currentVertices[i] = Vector3f(updated[0], updated[1], updated[2]);
    }
}

