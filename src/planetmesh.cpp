#include "planetmesh.h"

PlanetMesh::PlanetMesh(){
    rotatex=rotatey=rotatez=false;
}

void PlanetMesh::GenerateDisplacedSphere(float radius, int rings, int slices, const std::vector<float>& heightMap, int mapWidth, int mapHeight, float heightScale) {
    Mesh sphere = GenMeshSphere(radius, rings, slices);

    if (sphere.vertexCount == 0) {
        std::cout<< "Failed to generate base sphere mesh" << std::endl;
    }

    std::cout << "Base sphere mesh generated successfully with vertex count: " << sphere.vertexCount << std::endl;

    float* vertices = (float*)sphere.vertices;

    for (int i = 0; i < sphere.vertexCount; i++) {
        Vector3 position = { vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2] };

        position = Vector3Normalize(position);

        // Calculate texture coordinates
        float u = 0.5f + atan2(position.x, position.z) / (2.0f * PI);
        float v = 0.5f - asin(position.y) / PI;

        // Get height from height map
        int x = static_cast<int>(u * (mapWidth - 1));
        int y = static_cast<int>(v * (mapHeight - 1));
        
        // Check height map indices
        if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
            // std::cout << "Height map indices out of bounds: (" << x << ", " << y << ")" << std::endl;
            float height = heightMap[y * mapWidth + x];
            position = Vector3Scale(position, height * heightScale);
        }


        // Displace vertex by height
        vertices[i * 3] += position.x;
        vertices[i * 3 + 1] += position.y;
        vertices[i * 3 + 2] += position.z;

        // Update vertex position
    }

    Mesh mesh=GenMeshSphere(radius, rings, slices);
    float* meshVertices = (float*)mesh.vertices;
    for(int i=0;i<mesh.vertexCount;i++){
        Vector3 position = { vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2] };
        if(rotatex) position = RotateY(position, 90*PI/180);
        if(rotatez) position = RotateZ(position, 90*PI/180);
        if(rotatey) position = RotateY(position, 90*PI/180);
        meshVertices[i*3]=position.x;
        meshVertices[i*3+1]=position.y;
        meshVertices[i*3+2]=position.z;
    }

    ExportMesh(mesh,"src/displaced_sphere.obj");
    std::cout << "Mesh uploaded successfully with displaced vertices" << std::endl;
    UploadMesh(&mesh, true);
    UploadMesh(&sphere, true);
    UnloadMesh(sphere);
}


Vector3 PlanetMesh::RotateX(Vector3 v, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return (Vector3){
        v.x,
        c * v.y - s * v.z,
        s * v.y + c * v.z
    };
}

// Function to rotate a vector around the y-axis
Vector3 PlanetMesh::RotateY(Vector3 v, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return (Vector3){
        c * v.x + s * v.z,
        v.y,
        -s * v.x + c * v.z
    };
}

// Function to rotate a vector around the z-axis
Vector3 PlanetMesh:: RotateZ(Vector3 v, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return (Vector3){
        c * v.x - s * v.y,
        s * v.x + c * v.y,
        v.z
    };
}