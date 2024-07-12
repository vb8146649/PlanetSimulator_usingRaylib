#include "planetmesh.h"

PlanetMesh::PlanetMesh()
{
    rotatex = rotatey = rotatez = 0;
    xOffset = 0;
}

Mesh PlanetMesh::GenerateDisplacedSphere(float radius, int rings, int slices, const std::vector<float> &heightMap, int mapWidth , int mapHeight , float heightScale, float initialHeight)
{
    sphere = GenMeshSphere(radius, rings, slices);

    if (heightMap.size() != 0)
    {
        for (int i = 0; i < sphere.vertexCount; i++)
        {
            Vector3 vertex = ((Vector3 *)sphere.vertices)[i];
            float u = ((float *)sphere.texcoords)[i * 2];
            float v = ((float *)sphere.texcoords)[i * 2 + 1];

            int texX = (int)(u * (mapWidth - 1));
            int texY = (int)(v * (mapHeight - 1));
            float heightValue = heightMap[texY * mapWidth + texX];

            // Displace the vertex along its normal
            Vector3 normal = Vector3Normalize(vertex);
            ((Vector3 *)sphere.vertices)[i] = Vector3Add(vertex, Vector3Scale(normal, heightValue * heightScale + (heightValue == 0 ? 0 : initialHeight)));
        }
    }

    // ExportMesh(sphere, "src/displaced_sphere.obj");
    UpdateMeshBuffer(sphere, 0,sphere.vertices,sphere.vertexCount * sizeof(Vector3), 0); 
    return sphere;
}
