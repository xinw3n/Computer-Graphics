#include "mesh.h"

#include "vertexrecorder.h"

using namespace std;

void Mesh::load( const char* filename )
{
	// 4.1. load() should populate bindVertices, currentVertices, and faces

    ifstream file(filename);
    string line;
    while (getline(file, line)){
        stringstream ss(line);
        Vector3f v;
        string s;
        Tuple3u f;
        ss >> s;
        if (s=="v"){ //vertices
            ss >> v[0] >> v[1] >> v[2];
            bindVertices.push_back(v);
        }
        if (s=="f"){ // faces
            ss >> f[0] >> f[1] >> f[2];
            faces.push_back(f);
        }
    }
	// make a copy of the bind vertices as the current vertices
	currentVertices = bindVertices;
}

void Mesh::draw()
{
	// 4.2 Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".
    VertexRecorder rec = VertexRecorder();
    for (unsigned i=0; i<faces.size(); i++){
        Tuple3u f =  faces[i];
        Vector3f v1 = currentVertices[f[0]-1]; // face indexes from 1
        Vector3f v2 = currentVertices[f[1]-1];
        Vector3f v3 = currentVertices[f[2]-1];
        Vector3f n1 = Vector3f::cross(v2-v1, v3-v1);
        Vector3f n2 = Vector3f::cross(v3-v2, v1-v2);
        Vector3f n3 = Vector3f::cross(v1-v3, v2-v3);
        n1.normalize();
        n2.normalize();
        n3.normalize();
        rec.record(v1, n1);
        rec.record(v2, n2);
        rec.record(v3, n3);
    }
    rec.draw();
}

void Mesh::loadAttachments( const char* filename, int numJoints )
{
	// 4.3. Implement this method to load the per-vertex attachment weights
	// this method should update m_mesh.attachments
    ifstream attachfile(filename);
    string line;
    while(getline(attachfile, line)){
        stringstream ss(line);
        vector<float> perVertex;
        perVertex.push_back(0);
        float w;
        while(ss >> w){
            perVertex.push_back(w);
        }
        attachments.push_back(perVertex);
    }
}
